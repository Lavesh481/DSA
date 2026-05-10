chrome.runtime.onMessage.addListener((request, sender, sendResponse) => {
    if (request.action === 'SOLVE_QUESTION') {
        handleSolve(request.question, request.options, request.imageData)
            .then(answer => sendResponse({ success: true, answer }))
            .catch(error => sendResponse({ success: false, message: error.message }));
        return true;
    }
    if (request.action === 'CAPTURE_SCREEN') {
        chrome.tabs.captureVisibleTab(null, { format: 'jpeg', quality: 50 }, (dataUrl) => {
            if (chrome.runtime.lastError) {
                console.error("Capture failed:", chrome.runtime.lastError.message);
                sendResponse({ success: false, message: chrome.runtime.lastError.message });
            } else {
                sendResponse({ success: true, imageData: dataUrl.split(',')[1] });
            }
        });
        return true;
    }
});

async function handleSolve(question, options, imageData) {
    const settings = await chrome.storage.local.get(['groqKey']);

    if (!settings.groqKey) {
        throw new Error('Groq API Key missing. Please add it in the settings ⚙️.');
    }

    return solveWithGroq(question, options, settings.groqKey, imageData);
}

async function solveWithGroq(question, options, apiKey, imageData) {
    const prompt = `Solve this question for a form. 
Question: ${question}
Options: ${options.join(', ')}

First, reason through the problem step-by-step.
Finally, provide the exact text of the correct option as the last line of your response, prefixed with "ANSWER: ".
Example:
...reasoning...
ANSWER: 0.778`;

    const messages = [
        {
            role: "user",
            content: [
                { type: "text", text: prompt }
            ]
        }
    ];

    if (imageData) {
        messages[0].content.push({
            type: "image_url",
            image_url: {
                url: `data:image/jpeg;base64,${imageData}`
            }
        });
    }

    const response = await fetch('https://api.groq.com/openai/v1/chat/completions', {
        method: 'POST',
        headers: {
            'Authorization': `Bearer ${apiKey}`,
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            model: imageData ? "llama-3.2-11b-vision-preview" : "llama-3.3-70b-versatile",
            messages: messages,
            temperature: 0
        })
    });

    const data = await response.json();

    // Automatic fallback if Vision model is decommissioned
    if (data.error && data.error.message.includes("decommissioned") && imageData) {
        console.warn("Groq Vision model decommissioned. Falling back to text-only mode.");
        return solveWithGroq(question, options, apiKey, null);
    }

    if (data.error) {
        console.error("Groq API Error:", data.error);
        throw new Error(data.error.message);
    }

    if (!data.choices || !data.choices[0]) {
        console.error("Groq Unexpected Response:", data);
        throw new Error("No response from Groq.");
    }

    const text = data.choices[0].message.content.trim();
    const match = text.match(/ANSWER:\s*(.*)$/im);
    return match ? match[1].trim() : text.split('\n').pop().replace(/^ANSWER:\s*/i, '').trim();
}
