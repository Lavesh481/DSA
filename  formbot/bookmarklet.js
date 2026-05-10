(async function () {
    console.log("FormBot Bookmarklet: Starting...");

    // 1. Manage API Key
    let groqKey = localStorage.getItem('formbot_groq_key');
    if (!groqKey) {
        groqKey = prompt("Enter your Groq API Key:");
        if (groqKey) localStorage.setItem('formbot_groq_key', groqKey);
        else return;
    }

    // 2. Logic to find questions and inputs
    function findQuestionForInput(input) {
        const isOption = input.getAttribute('role') === 'radio' || input.getAttribute('role') === 'checkbox' || input.type === 'radio' || input.type === 'checkbox';
        const container = input.closest('.geS5ne, [role="listitem"], .freebirdFormviewerComponentsQuestionBaseRoot');
        if (container) {
            const questionEl = container.querySelector('[role="heading"], .freebirdFormviewerComponentsQuestionBaseTitle, .M7e6Q');
            if (questionEl) return questionEl.innerText.trim();
        }
        const ariaLabel = input.getAttribute('aria-label');
        if (ariaLabel && !isOption) return ariaLabel.trim();
        let node = input;
        for (let i = 0; i < 3; i++) {
            const parent = node.parentElement;
            if (!parent) break;
            const text = Array.from(parent.childNodes).filter(n => n.nodeType === 3).map(n => n.textContent.trim()).join(' ');
            if (text.length > 5) return text;
            node = parent;
        }
        return input.placeholder || input.name || input.id || null;
    }

    function isPersonalInfoQuestion(question) {
        if (!question) return false;
        const q = question.toLowerCase().trim();
        const exactMatches = ['name', 'full name', 'first name', 'last name', 'email', 'email address', 'phone', 'phone number', 'address', 'city', 'state', 'zip code', 'postal code', 'country'];
        const cleanedQ = q.replace(/[:*]$/, '').trim();
        if (exactMatches.includes(cleanedQ)) return true;
        const personalPatterns = [
            /^(email|phone|mobile|contact|address|zip|postal|city|state|country)$/,
            /^(first|last|full|user)\s*name$/,
            /^(date\s*of\s*birth|dob|birth\s*date)$/
        ];
        return personalPatterns.some(pattern => pattern.test(cleanedQ));
    }

    // 3. AI Solving Logic
    async function solveWithGroq(question, options, apiKey) {
        const promptText = `Solve this question for a form. 
Question: ${question}
Options: ${options.join(', ')}

First, reason through the problem step-by-step.
Finally, provide the exact text of the correct option as the last line of your response, prefixed with "ANSWER: ".`;

        try {
            const response = await fetch('https://api.groq.com/openai/v1/chat/completions', {
                method: 'POST',
                headers: {
                    'Authorization': `Bearer ${apiKey}`,
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    model: "llama-3.3-70b-versatile",
                    messages: [{ role: "user", content: promptText }],
                    temperature: 0
                })
            });

            const data = await response.json();
            if (data.error) throw new Error(data.error.message);
            const text = data.choices[0].message.content.trim();
            const match = text.match(/ANSWER:\s*(.*)$/im);
            return match ? match[1].trim() : text.split('\n').pop().replace(/^ANSWER:\s*/i, '').trim();
        } catch (e) {
            console.error("Groq Error:", e);
            return null;
        }
    }

    // 4. Fill Values
    function setInputValues(input, value) {
        const role = input.getAttribute('role');
        const isRadioOrCheck = role === 'radio' || role === 'checkbox' || input.type === 'radio' || input.type === 'checkbox';
        if (isRadioOrCheck) {
            const label = input.labels?.[0] || input.closest('label') || document.querySelector(`label[for="${input.id}"]`);
            const labelStr = (label ? label.innerText : (input.innerText || input.getAttribute('aria-label') || '')).trim().toLowerCase();
            const strVal = String(value).toLowerCase();
            if (value === true || labelStr.includes(strVal) || strVal.includes(labelStr) && labelStr.length > 0) {
                input.checked = true;
                if (role) input.setAttribute('aria-checked', 'true');
                input.click();
                input.dispatchEvent(new Event('change', { bubbles: true }));
            }
        } else {
            input.value = value;
            input.dispatchEvent(new Event('input', { bubbles: true }));
        }
    }

    // 5. Main Loop
    const inputs = [...document.querySelectorAll('input, textarea, select, [role="radio"], [role="checkbox"]')];
    const questionsMap = new Map();
    inputs.forEach(input => {
        if (input.offsetParent === null && input.type !== 'hidden') return;
        const qText = findQuestionForInput(input);
        if (qText) {
            if (!questionsMap.has(qText)) questionsMap.set(qText, []);
            questionsMap.get(qText).push(input);
        }
    });

    console.log(`FormBot: Found ${questionsMap.size} questions.`);

    for (const [question, group] of questionsMap) {
        if (isPersonalInfoQuestion(question)) continue;

        const options = group.map(i => i.innerText.trim() || i.getAttribute('aria-label') || i.nextElementSibling?.innerText.trim()).filter(t => t);
        const answer = await solveWithGroq(question, options, groqKey);

        if (answer) {
            console.log(`FormBot: Filled "${answer}" for "${question}"`);
            group.forEach(input => setInputValues(input, answer));
        }
    }
    alert("FormBot: Done!");
})();
