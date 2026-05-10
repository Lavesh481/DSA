const isPersonalInfoQuestion = (question) => {
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
};

const tests = [
    { q: "Full Name:", expected: true },
    { q: "Email Address", expected: true },
    { q: "Phone Number*", expected: true },
    { q: "City", expected: true },
    { q: "What is the name of the first President?", expected: false },
    { q: "Which city is the capital of France?", expected: false },
    { q: "What is 2+2?", expected: false },
    { q: "f1 score", expected: false },
    { q: "Your email:", expected: false }, // Should it be true? "email" is in patterns.
    { q: "Last Name", expected: true },
    { q: "Address:", expected: true }
];

tests.forEach(test => {
    const result = isPersonalInfoQuestion(test.q);
    console.log(`Question: "${test.q}"`);
    console.log(`Result: ${result} (Expected: ${test.expected})`);
    console.log(`Success: ${result === test.expected}`);
    console.log('---');
});
