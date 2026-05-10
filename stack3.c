#include <stdio.h>
#include <string.h>

char stack[100];  // Our stack
int top = -1;     // Points to top element (-1 = empty)

// Add to stack
void push(char c) {
    top++;
    stack[top] = c;
    printf("Added '%c' to stack\n", c);
}

// Remove from stack
char pop() {
    char c = stack[top];
    top--;
    printf("Removed '%c' from stack\n", c);
    return c;
}

// Check if matches
int matches(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '{' && close == '}') return 1;
    if (open == '[' && close == ']') return 1;
    return 0;
}

// Main checking function
int isValid(char* s) {
    printf("\nChecking: %s\n\n", s);
    
    for (int i = 0; i < strlen(s); i++) {
        char c = s[i];
        printf("Character %d: '%c'\n", i+1, c);
        
        // If opening bracket
        if (c == '(' || c == '{' || c == '[') {
            push(c);
        }
        // If closing bracket
        else if (c == ')' || c == '}' || c == ']') {
            // Check if stack is empty
            if (top == -1) {
                printf("ERROR: Nothing to match with!\n");
                return 0;  // Invalid
            }
            
            // Get top and check
            char topChar = pop();
            if (!matches(topChar, c)) {
                printf("ERROR: '%c' doesn't match '%c'\n", topChar, c);
                return 0;  // Invalid
            }
            printf("✓ Matched!\n");
        }
        printf("\n");
    }
    
    // Check if empty
    if (top != -1) {
        printf("ERROR: Stack not empty!\n");
        return 0;  // Invalid
    }
    
    printf("SUCCESS! All matched!\n");
    return 1;  // Valid
}

int main() {
    isValid("[()]}");
    return 0;
}

 
 