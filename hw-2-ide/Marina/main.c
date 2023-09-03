/* Program to calculate the product of two numbers. */
#include <stdio.h>
#include <time.h>

int a, b, c;
int product(int x, int y);

int main()
{
    time_t rawtime = time(NULL);
    /* Input the first number */
    printf("Enter a number between 1 and 100: ");
    scanf("%d", &a);

    /* Input the second number */
    printf("Enter another number between 1 and 100: ");
    scanf("%d", &b);

    /* Calculate and display the product */
    c = product(a, b);
    printf("\n%d times %d = %d\n", a, b, c);
    printf("Marina Berti\n");
    printf("First program %s\n", ctime(&rawtime));
    return 0;
}

/* Function returns the product of its two arguments */
int product(int x, int y)
{
    return (x * y);
}