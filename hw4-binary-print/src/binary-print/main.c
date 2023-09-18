#include <time.h>
#include <stdio.h>

int main()
{
    // Create integers i, count, and mask.
    int count, i, mask;

    // Get the current time for review
    time_t rawtime = time(NULL);

    // Set 'i' to a hex value of 0x1b53.
    i = 0x1b53; // 0001 1011 0101 0011

    // Set 'mask' to a value of 0x8000.
    mask = 0x8000; // 1000 0000 0000 0000

    // Print a line to show the time
    printf("\nBinaryPrint %s", ctime(&rawtime));

    // Print a line to show the hex value of 'i' and then the leader for the binary
    // Hex value = 1b53 Binary=
    printf("Hex value = %x Binary =", i);

    // Use a for loop to loop 16 times and print 16 digits, using 'count' as the loop counter
    // The output should look like this:
    // Hex value = 1b53, Binary= 0001 1011 0101 0011
    for (count = 0; count < 16; count++)
    {
        // Use the modulus of count and print a space after every 4th digit to make the binary easier to read
        if (count % 4 == 0)
        {
            printf(" ");
        }

        // To test for each digit value, bitwise and 'i' with 'mask'
        if (i & mask)
        {
            // When the result for the bitwise and is true, print the number '1'
            printf("1");
        }
        else
        {
            // When the result for the bitwise and is false, print the number '0'
            printf("0");
        }

        // Then shift mask one place to the right
        mask >>= 1;
    }

    // Print a new line and then quit
    printf("\n");

    return 0;
}