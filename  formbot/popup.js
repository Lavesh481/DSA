// Initialize UI from storage
chrome.storage.local.get(['groqKey', 'useAI'], (result) => {
    const apiKeyInput = document.getElementById('apiKey');
    const useAICheckbox = document.getElementById('useAI');
    const status = document.getElementById('status');

    if (result.groqKey) {
        apiKeyInput.value = result.groqKey;
    }

    // Default useAI to true if not set
    useAICheckbox.checked = result.useAI !== false;
});

// Toggle settings panel
document.getElementById('settingsBtn').addEventListener('click', () => {
    const panel = document.getElementById('aiSettings');
    panel.classList.toggle('hidden');
});

// Auto-save toggle
document.getElementById('useAI').addEventListener('change', (e) => {
    chrome.storage.local.set({ useAI: e.target.checked });
});

// Save explicit key
document.getElementById('saveKey').addEventListener('click', () => {
    const key = document.getElementById('apiKey').value.trim();
    const status = document.getElementById('status');
    const panel = document.getElementById('aiSettings');

    if (!key) {
        status.textContent = 'Please enter a key';
        status.style.color = '#ef4444';
        return;
    }

    chrome.storage.local.set({ groqKey: key }, () => {
        status.textContent = `✅ Groq Key Saved`;
        status.style.color = 'var(--success)';
        panel.classList.add('hidden');
        setTimeout(() => {
            status.textContent = 'Ready';
            status.style.color = 'var(--text-dim)';
        }, 3000);
    });
});

document.getElementById('fillButton').addEventListener('click', async () => {
    const status = document.getElementById('status');
    status.textContent = 'Solving...';
    status.style.color = 'var(--text-dim)';

    try {
        const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });
        if (!tab) return;

        const settings = await chrome.storage.local.get(['groqKey', 'useAI']);
        const useAI = settings.useAI !== false;
        const hasKey = !!settings.groqKey;

        status.textContent = 'Filling form...';
        chrome.tabs.sendMessage(tab.id, {
            action: 'FILL_FORM',
            useAI: useAI,
            hasKey: hasKey
        }, (response) => {
            if (chrome.runtime.lastError) {
                status.textContent = 'Error: Refresh page.';
                status.style.color = '#ef4444';
                return;
            }

            if (response && response.success) {
                status.textContent = `Success! Filled ${response.count} fields.`;
                status.style.color = 'var(--success)';
            } else {
                status.textContent = response?.message || 'Nothing to fill.';
                status.style.color = '#f59e0b'; // Warning color (orange)
            }
        });
    } catch (error) {
        status.textContent = 'Error occurred.';
        status.style.color = '#ef4444';
    }
});
