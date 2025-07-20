// This funtion get's the coin position, the player position, how the player has moved and the current round number.
int scoring(int coin_position, int player_position, char* player_change, int i )
{
    printf("Round %i: Coin at %i, Player %s\n", i, coin_position, player_change); // This is what displays the rounds
    int score = 0;
    if (coin_position == player_position)
    {
        score++;
        printf("--> Coin caught! Score: %i\n", score); // Alert when the coin  and player match
    }
    return score;
}
// It returns the score so that the main can print the final score after all the rounds
// Note: the string player_change is meant to be either:  player stayed / player moved to x 
// Another logic will dtermine wht string that would be depending on the player's last movement.