#include <stdio.h>
#include <time.h>

int main()
{
    // Declare integers A and B.
    int A, B;
    // Declare a result integer Result
    int Result;

    // Get the current time for review
    time_t rawtime = time(NULL);

    // Prompt for and input values for A and B
    printf("Enter value for A: ");
    scanf("%d", &A);
    printf("Enter value for B: ");
    scanf("%d", &B);

    // Print the current time
    printf("\nOperators %s", ctime(&rawtime));

    // Create a series of statements with the expression result
    // for each of the following operations:
    // Addition
    Result = A + B;
    printf("Result of A + B = %d, original A=%d B=%d\n", Result, A, B);
    // Subtraction
    Result = A - B;
    printf("Result of A - B = %d, original A=%d B=%d\n", Result, A, B);
    // Multiplication
    Result = A * B;
    printf("Result of A * B = %d, original A=%d B=%d\n", Result, A, B);
    // Modulus
    Result = A % B;
    printf("Result of A %% B = %d, original A=%d B=%d\n", Result, A, B);
    // Equality
    Result = A == B;
    printf("Result of A == B = %d, original A=%d B=%d\n", Result, A, B);
    // Greater Than
    Result = A > B;
    printf("Result of A > B = %d, original A=%d B=%d\n", Result, A, B);
    // Less Than or Equal
    Result = A <= B;
    printf("Result of A <= B = %d, original A=%d B=%d\n", Result, A, B);
    // Logical And
    Result = A && B;
    printf("Result of A && B = %d, original A=%d B=%d\n", Result, A, B);
    // Pre-increment A
    Result = ++A;
    printf("Result of ++A = %d, original A=%d B=%d\n", Result, A, B);
    // Post-increment B
    Result = B++;
    printf("Result of B++ = %d, original A=%d B=%d\n", Result, A, B);
    // Bitwise And
    Result = A & B;
    printf("Result of A & B = %d, original A=%d B=%d\n", Result, A, B);
    // Bitwise Or
    Result = A | B;
    printf("Result of A | B = %d, original A=%d B=%d\n", Result, A, B);
    // Bitwise Shift Left A
    Result = A << 1;
    printf("Result of A << 1 = %d, original A=%d B=%d\n", Result, A, B);
    // Bitwise Shift Right B
    Result = B >> 1;
    printf("Result of B >> 1 = %d, original A=%d B=%d\n", Result, A, B);

    return 0;
}
