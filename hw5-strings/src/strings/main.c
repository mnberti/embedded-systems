#include <stdio.h>
#include <string.h>
#include <time.h>

// Define the FlipMySentent function prototype
// The function will be defined later in the file
void FlipMySentence(char *apples);

/**
 * @brief This is the main function for the program.
 * @return int - Returns 0 if successful
 */
int main()
{
    // Define the counter for the upcoming loop
    int i;
    // Define the string/array we will use to store our sentence.
    // This will reserve memory for 80 characters (79 + null terminator/binary zero)
    char Tires[80];
    // Define and initialize a variable to hold the current time
    time_t rawtime = time(NULL);

    // Copy the string into the `Tires` string
    strcpy(Tires, "Whitewalls go faster");

    // Print the address of the string `Tires`
    // %p is the format specifier for a pointer
    printf("Tires is located at %p\n", Tires);

    // Loop through the first 10 characters of the string
    for (i = 0; i < 10; i++)
    {
        // Print the character at the current index and its location
        printf("Tires[%d] = %c at %p\n", i, Tires[i], &Tires[i]);
        // printf ("Tires[%d] = %d at %p\n",i,Tires[i], &Tires[i]);
        // printf ("Tires[%d] = %c at %p\n",i,*(Tires+i), Tires+i);
    }

    // Call the FlipMySentence function and pass it the pointer to the
    // `Tires` string
    FlipMySentence(Tires);

    // Print the reversed string and the current time
    printf("The reversed string is: '%s' on %s\n", Tires, ctime(&rawtime));

    // Return 0 to tell the OS the program exited without errors
    return 0;
}

/**
 * @brief This function will reverse the string passed to it.
 * @param apples The pointer to the string to reverse
 * @return void
 */
void FlipMySentence(char *apples)
{
    // Define and initialize the variables we will use in the loop
    int i, j, length = 0;
    // Define a temporary variable to hold the character we are swapping
    char temp;

    // Get the length of the string
    length = strlen(apples);
    // Print the length of the string
    printf("Sentence length =%d\n", length);

    // Loop through half of the string, swapping the characters
    // i is the first element of the array
    // j is the last element of the array, and is set to length - 1
    // to avoid the null terminator
    // As the loop progresses, i is incremented and j is decremented
    // and the loop will only have to go halfway through the string
    // to swap all characters.
    for (i = 0, j = length - 1; i < j; i++, j--)
    {
        // Store the character at the current index in a temporary variable
        temp = apples[i];
        // Set the character at the current index to the character at the
        // opposite index
        apples[i] = apples[j];
        // Set the character at the opposite index to the character in the
        // temporary variable
        apples[j] = temp;
    }

    // Since the function modifies the string directly, there is no need to
    // return anything.
    return;
}