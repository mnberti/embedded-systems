#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>

// Total number of cards in a deck
#define NCARDS 52
// Number of properties for each card
#define NPROPS 2

// Number of suits in a deck
#define NSUITS 4
// Number of face values per suit
#define NFACES 13

// Number of players
#define NPLAYERS 2
// Number of cards per hand
#define NCARDS_PER_HAND 5

// Define the suits as arrays of strings
char *suit[NSUITS] = {"hearts", "spades", "clubs", "diamonds"};

// Define the face values as arrays of strings
char *face[NFACES] = {"ace", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                      "ten", "jack", "queen", "king"};

// Define function prototypes that will be defined later
// and used to manipulate the deck of cards
void DealCards(int deck[NCARDS][NPROPS], int hands[NPLAYERS][NCARDS_PER_HAND]);
int GetPlayValue(int deck[NCARDS][NPROPS], int i);
int GetTotalPlayValue(int deck[NCARDS][NPROPS], int hand[NCARDS_PER_HAND]);
int GetWinner(int deck[NCARDS][NPROPS], int hands[NPLAYERS][NCARDS_PER_HAND]);
void InitDeck(int deck[NCARDS][NPROPS]);
void PrintCard(int deck[NCARDS][NPROPS], int i);
void PrintHand(int deck[NCARDS][NPROPS], int hand[NCARDS_PER_HAND], int player);
void ShuffleDeck(int deck[NCARDS][NPROPS]);
void SwapCards(int deck[NCARDS][NPROPS], int src, int dest);

int main()
{
    // Define the deck of cards as a 2D array of integers
    // Each card is represented by an array of 2 integers:
    // 1st integer is the suit of the card
    // 2nd integer is the face value of the card
    int deck[NCARDS][NPROPS];
    // Define the two hands of cards
    // Each hand is an array of 5 integers that represent
    // the index of the card in the deck
    int hands[NPLAYERS][NCARDS_PER_HAND];
    // Define a variable to hold the winner of the game
    int winner;

    // Get the current time for the homework submission
    time_t rawtime = time(NULL);

    // Define a counter variable
    int i;

    // Seed the random number generator
    srand(time(NULL));

    // Initialize the deck of cards
    InitDeck(deck);

    // Shuffle the deck of cards
    ShuffleDeck(deck);

    // Print the shuffled deck of cards
    puts("The shuffled deck is:");
    for (i = 0; i < 20; i++)
    {
        PrintCard(deck, i);
    }
    puts("-----------------------");

    // Deal the cards to the players
    DealCards(deck, hands);

    // Get the winner of the game
    winner = GetWinner(deck, hands);

    // Print the result of the game and each player's hand
    // Print the winner's hand
    printf("The winner is Player %d\n\n", winner + 1);
    PrintHand(deck, hands[winner], winner);
    // Print the loser's hand
    for (i = 0; i < NPLAYERS; i++)
    {
        if (i != winner)
        {
            PrintHand(deck, hands[i], i);
        }
    }

    printf("Printed on %s", ctime(&rawtime));
    system("PAUSE");

    return 0;
}

/**
 * Deal cards to the players
 * @param deck The deck of cards
 * @param hands The hands of cards
 * @return void
 */
void DealCards(int deck[NCARDS][NPROPS], int hands[NPLAYERS][NCARDS_PER_HAND])
{
    // Define counter variables
    int card, player;

    // Each player will be dealt 5 cards. Deal one to the first
    // player, then one to second player. Repeat until both players
    // have 5 cards in their hand.
    for (card = 0; card < NCARDS_PER_HAND; card++)
    {
        for (player = 0; player < NPLAYERS; player++)
        {
            // Assign the card index to the player's hand
            hands[player][card] = card * NPLAYERS + player;
        }
    }
}

/**
 * Get the play value of a card in the deck
 * @param deck The deck of cards
 * @param i The index of the card
 * @return The play value of the card
 */
int GetPlayValue(int deck[NCARDS][NPROPS], int i)
{
    // Create local variables: facevalue, playvalue
    int facevalue, playvalue;

    // Assign facevalue from card at index i in deck
    facevalue = deck[i][1];

    // Assign the pay value of the card
    // When the face value is 0, the play value is 11
    if (facevalue == 0)
    {
        playvalue = 11;
    }
    // When the face value is greater than 10, the play value is 10
    else if (facevalue > 10)
    {
        playvalue = 10;
    }
    // Otherwise, the play value is the face value
    else
    {
        playvalue = facevalue;
    }

    return playvalue;
}

/**
 * Get the total play value of a hand of cards
 * @param deck The deck of cards
 * @param hand The hand of cards
 * @return The total play value of the hand
 */
int GetTotalPlayValue(int deck[NCARDS][NPROPS], int hand[NCARDS_PER_HAND])
{
    // Define counter variables
    int card, playvalue;
    // Initialize the total play value to 0
    int totalplayvalue = 0;

    // Loop through each card in the hand
    for (card = 0; card < NCARDS_PER_HAND; card++)
    {
        // Add the play value of the card to the total play value
        totalplayvalue += GetPlayValue(deck, hand[card]);
    }

    return totalplayvalue;
}

/**
 * Get the winner of the game
 * @param deck The deck of cards
 * @param hands The hands of cards
 * @return The index of the winner
 */
int GetWinner(int deck[NCARDS][NPROPS], int hands[NPLAYERS][NCARDS_PER_HAND])
{
    // Define counter variables
    int player, card, playvalue;
    // Initialize the winner to the first player
    int winner = 0;
    // Initialize the winning score to 0;
    int winningscore = 0;

    // Loop through each player
    for (player = 0; player < NPLAYERS; player++)
    {
        // Get the hand's total play value
        playvalue = GetTotalPlayValue(deck, hands[player]);

        // If the current player's play value is greater than the winner's play value
        // then the current player is assigned the winner
        if (playvalue > winningscore)
        {
            winningscore = playvalue;
            winner = player;
        }
    }

    return winner;
}

/**
 * Initialize the deck of cards by setting the suit and face value
 * in the 2D array of integers
 * @param deck The deck of cards
 * @return void
 */
void InitDeck(int deck[NCARDS][NPROPS])
{
    // Define a counter variable
    int i, j;

    // Loop through suits
    for (i = 0; i < NSUITS; i++)
    {
        // Loop through faces
        for (j = 0; j < NFACES; j++)
        {
            // Calculate the index of the card
            int idx = i * NFACES + j;
            // Set the suit value
            deck[idx][0] = i;
            // Set the face value
            deck[idx][1] = j;
        }
    }
}

/**
 * Print the face value, suit and play value of the card
 * @param deck The deck of cards
 * @param i The index of the card
 * @return void
 */
void PrintCard(int deck[NCARDS][NPROPS], int i)
{
    // Create local variables: suitvalue, facevalue, playval
    int suitvalue, facevalue, playvalue;
    // Assign suitvalue & facevalue from card at index i in deck
    suitvalue = deck[i][0];
    facevalue = deck[i][1];

    // Get the play value of the card
    playvalue = GetPlayValue(deck, i);

    // Print the string value of the card
    printf("%s of %s - %d \n", face[facevalue], suit[suitvalue], playvalue);
}

/**
 * Print the hand of cards
 * @param deck The deck of cards
 * @param hand The hand of cards
 * @return void
 */
void PrintHand(int deck[NCARDS][NPROPS], int hand[NCARDS_PER_HAND], int player)
{
    // Define a counter variable
    int i;

    // Print the player header
    printf("Player %d\n", player + 1);
    // Print the player's total score
    printf("Score is: %d\n", GetTotalPlayValue(deck, hand));
    // Print the player's hand
    puts("Hand:");
    // Loop through each card in the hand
    for (i = 0; i < NCARDS_PER_HAND; i++)
    {
        // Print the card
        PrintCard(deck, hand[i]);
    }
    // Adding a new line for readability
    puts("");
}

/**
 * Loop through each card of the deck and swap it with a random card
 * @param deck The deck of cards
 * @return void
 */
void ShuffleDeck(int deck[NCARDS][NPROPS])
{
    // Create local variables (src, dest)
    int src, dest;
    // Loop through each card in the deck and set
    // the destination index
    for (dest = 0; dest < NCARDS; dest++)
    {
        // Get a random index for the source card
        src = rand() % NCARDS;
        // Swap the cards
        SwapCards(deck, src, dest);
    }
}

/**
 * Swap the properties of two cards
 * @param deck The deck of cards
 * @param src The source card
 * @param dest The destination card
 * @return void
 */
void SwapCards(int deck[NCARDS][NPROPS], int src, int dest)
{
    // Define a temporary local variable
    int temp;
    // Define a counter variable
    int i;

    // Loop through the properties of the card
    // and swap them
    for (i = 0; i < NPROPS; i++)
    {
        // Copy the destination card's property to the temporary variable
        temp = deck[dest][i];
        // Copy the source card's property to the destination card's property
        deck[dest][i] = deck[src][i];
        // Copy the temporary variable to the source card's property
        deck[src][i] = temp;
    }
}
