#include <stdio.h>
#include <string.h>

int main()
{
    char str1[50], str2[50], temp;
    int choice, i, j, len;

    printf("Name: Lavesh Kumar\n");
    printf("Roll No: 25/A03/059\n");

    printf("\n1. String Concatenation");
    printf("\n2. String Comparison");
    printf("\n3. String Reverse");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();   // clear buffer

    if (choice == 1)
    {
        printf("Enter first string: ");
        fgets(str1, 50, stdin);

        printf("Enter second string: ");
        fgets(str2, 50, stdin);

        str1[strcspn(str1, "\n")] = '\0';
        str2[strcspn(str2, "\n")] = '\0';

        strcat(str1, str2);
        printf("After concatenation: %s", str1);
    }
    else if (choice == 2)
    {
        printf("Enter first string: ");
        fgets(str1, 50, stdin);

        printf("Enter second string: ");
        fgets(str2, 50, stdin);

        str1[strcspn(str1, "\n")] = '\0';
        str2[strcspn(str2, "\n")] = '\0';

        if (strcmp(str1, str2) == 0)
            printf("Strings are equal");
        else
            printf("Strings are not equal");
    }
    else if (choice == 3)
    {
        printf("Enter a string: ");
        fgets(str1, 50, stdin);

        str1[strcspn(str1, "\n")] = '\0';

        len = strlen(str1);

        for (i = 0, j = len - 1; i < j; i++, j--)
        {
            temp = str1[i];
            str1[i] = str1[j];
            str1[j] = temp;
        }

        printf("Reversed string: %s", str1);
    }
    else
    {
        printf("Invalid choice");
    }

    return 0;
}
