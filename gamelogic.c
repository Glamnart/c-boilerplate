#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STARTING_POSITION 3
#define BLOCKS 5
#define MAX_ROUND 15

int decide_move(int player_pos, int coin_pos);
int drop_coin(void);
char* movement(int player_decision, char* movement);
int scoring(int coin_position, int player_position, int i, int score, char* move);

int main(void){
    srand((unsigned)time(NULL)); //  seeding the random number
    int score = 0, coin, player = STARTING_POSITION, decision = 0;
    char move[50] = "abc"; // Fake initialization in case of error
    for (int i = 1; i <= MAX_ROUND; i++) // Loop for rounds
    {
        coin = drop_coin(), decision = decide_move(player, coin); // First retrieves the coin and decision of player based off the coin position.
        strcpy(move, movement( decision, move)); // makes the print function print out the correct movement
        player += decision; // Changes the player according to the decision from the function
        score =  scoring(coin, player, i, score, move);             
    }
    printf("Total score: %i / %i.\n", score, MAX_ROUND); // Prints total score.
    return 0;
}

// Player strategy (Kenechukwu)
int decide_move(int player_pos, int coin_pos) 
{
    if (coin_pos < player_pos) {
        return -1; // move left
    } else if (coin_pos > player_pos) {
        return 1;  // move right
    } else {
        return 0;  // stay
    }
}

// Function to drop the coin (Peter)
int drop_coin(void)
{
    int coin = rand() % (BLOCKS + 1);
    while (coin == 0) // prevents it from calling position 0.
        coin = rand() % (BLOCKS + 1);
    return coin;
}

// Prints the movement decision in words (Favour)
char* movement(int player_decision, char* move)
{
    if (player_decision == 0)
    {
        strcpy(move,"stayed at"); // Changing the movement based on player position
    }
    else 
        strcpy(move,"moved to");
    return move;
}

// This funtion get's the coin position, the player position, the current round number, score (will be initialized as 0 in main)  and words of movement. (Favour)
int scoring(int coin_position, int player_position, int i, int score, char* move)
{
    if (i == 1)// At round 1
    { 
        if (player_position == STARTING_POSITION) // to 'stayed' when no movement is done 
            strcpy(move, "stayed at");
        else 
            strcpy(move, "moved to"); // moved if movement occured.
    }
    printf("Round %i: Coin at %i, Player %s %i\n", i, coin_position, move, player_position); // This is what displays the round and movements
    if (coin_position == player_position)
    {
        score++;
        printf("--> Coin caught! Score: %i\n", score); // Alert when the coin  and player match
    }
    return score;  
}
// It returns the score so that the main can print the final score after all the rounds.

