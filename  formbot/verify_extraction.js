const testExtraction = (text) => {
    const match = text.match(/ANSWER:\s*(.*)$/im);
    return match ? match[1].trim() : text.split('\n').pop().replace(/^ANSWER:\s*/i, '').trim();
};

const tests = [
    {
        name: "Standard response with reasoning",
        input: "The F1 score is calculated from Precision and Recall.\nPrecision = TP / (TP + FP) = 70 / (70 + 30) = 0.7\nRecall = TP / (TP + FN) = 70 / (70 + 10) = 0.875\nF1 = 0.777...\nANSWER: 0.778",
        expected: "0.778"
    },
    {
        name: "Response with trailing whitespace",
        input: "Reasoning...\nANSWER: 0.778  ",
        expected: "0.778"
    },
    {
        name: "Response without ANSWER: prefix (fallback logic)",
        input: "Reasoning...\n0.778",
        expected: "0.778"
    },
    {
        name: "Common case - ANSWER on last line",
        input: "ANSWER: Maximilien Robespierre",
        expected: "Maximilien Robespierre"
    }
];

tests.forEach(test => {
    const result = testExtraction(test.input);
    console.log(`Test: ${test.name}`);
    console.log(`Result: "${result}"`);
    console.log(`Success: ${result === test.expected}`);
    console.log('---');
});
