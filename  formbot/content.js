chrome.runtime.onMessage.addListener((request, sender, sendResponse) => {
    if (request.action === 'FILL_FORM') {
        console.log("FormBot: Received FILL_FORM request", request);
        fillForm(request.useAI, request.hasKey).then(sendResponse);
    }
    return true;
});

async function fillForm(useAI, hasKey) {
    const inputs = Array.from(document.querySelectorAll('input, textarea, select'));
    const customInputs = Array.from(document.querySelectorAll('[role="radio"], [role="checkbox"], [role="listbox"], [role="textbox"]'));

    const allInputs = [...inputs, ...customInputs];
    let count = 0;

    console.log(`FormBot: Found ${allInputs.length} potential inputs`);

    if (allInputs.length === 0) {
        return { success: false, message: 'No input fields found on this page.' };
    }

    const questionsMap = new Map();
    allInputs.forEach(input => {
        if (input.offsetParent === null && input.type !== 'hidden') return;
        if (input.type === 'hidden' && !input.closest('.geS5ne')) return;

        const qText = findQuestionForInput(input);
        if (qText || input.closest('.geS5ne, [role="listitem"]')) {
            const key = qText || `unnamed_question_${Math.random().toString(36).substr(2, 5)}`;
            if (!questionsMap.has(key)) questionsMap.set(key, []);
            questionsMap.get(key).push(input);
        }
    });

    console.log(`FormBot: Grouped into ${questionsMap.size} questions`);

    // Capture screen ONLY IF NEEDED (visual cues detected or text missing)
    let imageData = null;
    const visionNeeded = needsVision(questionsMap);
    console.log(`FormBot: Vision needed: ${visionNeeded}`);

    if (useAI && hasKey && visionNeeded) {
        console.log("FormBot: Visual cues detected, capturing screen...");
        try {
            const captureResponse = await new Promise(resolve => {
                chrome.runtime.sendMessage({ action: 'CAPTURE_SCREEN' }, resolve);
            });
            if (captureResponse && captureResponse.success) {
                imageData = captureResponse.imageData;
            }
        } catch (e) {
            console.error("Screen capture failed:", e);
        }
    }

    for (const [question, group] of questionsMap) {
        const firstInput = group[0];
        const type = firstInput.getAttribute('role') || firstInput.type || (firstInput.tagName === 'SELECT' ? 'select-one' : 'text');

        if (isPersonalInfoQuestion(question)) {
            console.log(`FormBot: Skipping personal information field: "${question}"`);
            continue;
        }

        let answer = generateLocalAnswer(question, type);

        // Enhance question with table context if available
        let enhancedQuestion = question;
        const tableContext = findTableContext(firstInput);
        if (tableContext) {
            enhancedQuestion = `[Table Context: ${tableContext}] Question: ${question}`;
            console.log(`FormBot: Enhanced question with table context: "${enhancedQuestion}"`);
        }

        if (answer === null && useAI && hasKey) {
            const options = group.map(input => {
                const label = input.innerText.trim() || input.getAttribute('aria-label') || '';
                // Try finding sibling text if it's a bare radio
                if (!label) {
                    const sibling = input.nextElementSibling;
                    if (sibling) return sibling.innerText.trim();
                }
                return label;
            }).filter(t => t);

            console.log(`FormBot: Requesting AI for "${enhancedQuestion}" with options:`, options);
            const aiResponse = await requestAISolve(enhancedQuestion, options, imageData);
            if (aiResponse) {
                console.log(`FormBot: AI answered "${aiResponse}"`);
                answer = aiResponse;
            }
        }

        if (answer !== null) {
            console.log(`FormBot: Filling "${answer}" for question "${question}"`);
            group.forEach(input => setInputValues(input, answer));
            count++;
        }
    }

    if (count === 0) {
        let msg = 'Could not solve any questions.';
        if (!useAI) msg = 'AI Solving is disabled. Please enable it in settings.';
        else if (!hasKey) msg = 'Missing API Key. Please add it in the settings ⚙️.';
        else if (questionsMap.size === 0) msg = 'No recognizable questions found.';
        return { success: false, message: msg };
    }

    return { success: true, count: count };
}

async function requestAISolve(question, options, imageData) {
    return new Promise(resolve => {
        chrome.runtime.sendMessage({
            action: 'SOLVE_QUESTION',
            question,
            options,
            imageData
        }, response => {
            if (response && response.success) resolve(response.answer);
            else {
                console.error("FormBot AI Error:", response?.message);
                resolve(null);
            }
        });
    });
}

function generateLocalAnswer(question, type) {
    const q = question.replace(/\*/g, '').trim().toLowerCase();

    // Improved math solver
    const mathRegex = /([\d\s\+\-\*\/\(\)\^]+)/;
    const match = q.match(mathRegex);
    if (match && match[0].trim().length > 2) {
        try {
            // Clean up: remove trailing operators like + - * /
            let expression = match[0].replace(/x/g, '*').trim().replace(/[\+\-\*\/]+$/, '');
            if (/[\+\-\*\/]/.test(expression) && /[\d]/.test(expression)) {
                const result = Function(`"use strict"; return (${expression})`)();
                if (!isNaN(result)) return String(result);
            }
        } catch (e) { }
    }

    if (type === 'checkbox') return true;
    return null;
}

function findQuestionForInput(input) {
    const isOption = input.getAttribute('role') === 'radio' || input.getAttribute('role') === 'checkbox' || input.type === 'radio' || input.type === 'checkbox';

    // Modern Google Forms (geS5ne is the question container)
    // We prioritize this for options to avoid using the option label as the question
    const container = input.closest('.geS5ne, [role="listitem"], .freebirdFormviewerComponentsQuestionBaseRoot');
    if (container) {
        const questionEl = container.querySelector('[role="heading"], .freebirdFormviewerComponentsQuestionBaseTitle, .M7e6Q');
        if (questionEl) return questionEl.innerText.trim();
    }

    // Check aria-labelledby or aria-label (but not for options)
    const ariaLabel = input.getAttribute('aria-label');
    if (ariaLabel && !isOption) return ariaLabel.trim();

    const labelledBy = input.getAttribute('aria-labelledby');
    if (labelledBy) {
        const label = document.getElementById(labelledBy);
        if (label) return label.innerText.trim();
    }

    // Check parent's preceding text
    let node = input;
    for (let i = 0; i < 3; i++) {
        const parent = node.parentElement;
        if (!parent) break;
        const text = Array.from(parent.childNodes)
            .filter(n => n.nodeType === 3)
            .map(n => n.textContent.trim())
            .join(' ');
        if (text.length > 5) return text;
        node = parent;
    }

    return input.placeholder || input.name || input.id || null;
}

function findTableContext(input) {
    const table = input.closest('table');
    if (!table) return null;

    const cell = input.closest('td, th');
    if (!cell) return null;

    const rowIndex = cell.parentElement.rowIndex;
    const cellIndex = cell.cellIndex;

    const headers = [];

    // Get column header (usually in the first row)
    const colHeader = table.rows[0]?.cells[cellIndex]?.innerText.trim();
    if (colHeader) headers.push(`Column: ${colHeader}`);

    // Get row header (usually in the first cell of the row)
    const rowHeader = cell.parentElement.cells[0]?.innerText.trim();
    if (rowHeader && cellIndex !== 0) headers.push(`Row: ${rowHeader}`);

    return headers.length > 0 ? headers.join(', ') : null;
}

function needsVision(questionsMap) {
    for (const [qText, group] of questionsMap) {
        // Condition 1: No text found for question or very short text
        if (qText.startsWith('unnamed_question_') || qText.length < 10) return true;

        const container = group[0].closest('.geS5ne, [role="listitem"], td, table');
        if (container) {
            // Condition 2: Images, Canvases, SVGs or common diagram classes present
            if (container.querySelector('img, canvas, svg, .diagram, [role="img"]')) return true;

            // Condition 3: Check for math-like background images (common in some LMS)
            const style = window.getComputedStyle(container);
            if (style.backgroundImage !== 'none') return true;
        }
    }
    return false;
}

function isPersonalInfoQuestion(question) {
    if (!question) return false;
    const q = question.toLowerCase().trim();

    // Exact list of personal info labels (case-insensitive, optional trailing colon)
    const exactMatches = ['name', 'full name', 'first name', 'last name', 'email', 'email address', 'phone', 'phone number', 'address', 'city', 'state', 'zip code', 'postal code', 'country'];

    const cleanedQ = q.replace(/[:*]$/, '').trim();
    if (exactMatches.includes(cleanedQ)) return true;

    // Pattern matches for common variants (must be short/specific to avoid filtering quiz questions)
    const personalPatterns = [
        /^(email|phone|mobile|contact|address|zip|postal|city|state|country)$/,
        /^(first|last|full|user)\s*name$/,
        /^(date\s*of\s*birth|dob|birth\s*date)$/
    ];

    return personalPatterns.some(pattern => pattern.test(cleanedQ));
}

function setInputValues(input, value) {
    const role = input.getAttribute('role');

    const isRadioOrCheckbox = role === 'radio' || role === 'checkbox' || input.type === 'radio' || input.type === 'checkbox';

    if (isRadioOrCheckbox) {
        const label = input.labels?.[0] || input.closest('label') || document.querySelector(`label[for="${input.id}"]`);
        const labelStr = (label ? label.innerText : (input.innerText || input.getAttribute('aria-label') || '')).trim().toLowerCase();
        const strVal = String(value).toLowerCase();
        const dataVal = input.getAttribute('data-value');

        console.log(`FormBot Debug: Matching "${labelStr}" (value: ${input.value}, data: ${dataVal}) against "${strVal}"`);

        if (value === true || input.value === value || dataVal === value || labelStr.includes(strVal) || strVal.includes(labelStr) && labelStr.length > 0) {
            console.log(`FormBot: Selecting matching input.`);
            input.checked = true;
            if (role) input.setAttribute('aria-checked', 'true');

            // Trigger UI updates via click and events
            input.click();
            input.dispatchEvent(new Event('input', { bubbles: true }));
            input.dispatchEvent(new Event('change', { bubbles: true }));
        }
    } else if (input.tagName === 'SELECT') {
        for (let i = 0; i < input.options.length; i++) {
            if (input.options[i].text === value || input.options[i].value === value) {
                input.selectedIndex = i;
                break;
            }
        }
    } else {
        input.value = value;
        input.dispatchEvent(new Event('input', { bubbles: true }));
        input.dispatchEvent(new Event('change', { bubbles: true }));
    }
}
