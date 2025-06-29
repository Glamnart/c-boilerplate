#include "include/input_utils.h"
#include <stdio.h>

#define max_question 5
#define correct 0
#define wrong 1
#define no_of_heart 3
#define maths_end 10
#define history_end 15

int greetings(void);
char willing(void);
void rules(int name);
int logic_theme(int score);
int history_theme(int score);
int math_theme(int score);
int heart_system(int heart, int score);
int checkpoint(int score);
int word_counter(string answer);
int word_checker(string answer, string player_answer);
int match(string player_answer, string answer1, string answer2, string answer3, string answer4,
          string answer5, string answer6, string answer7);

int main(void)
{
    // Welcoming the user
    int name = greetings();
    // Checking if they want to play or not
    char ready = willing();
    if (ready == 'y' || ready == 'Y')
    {
        int heart = no_of_heart, score = 0, marker;
        rules(name); // Saying the rules
        printf("Welcome to the first theme of this challenge: LOGIC \nLet's begin\n");
        while (true)
        {
            // Asking the logic theme questions
            marker = logic_theme(score);
            // When answer is correct
            if (marker == correct)
                score++;
            else
            {
                // When answer not correct(hearts reduce)
                heart = heart_system(heart, score);
                // The conditions that allow for the checkpoint system to function
                if (heart == 0)
                {
                    heart = no_of_heart; // Refills heart
                    score = 0;           // Goes back to the first question
                }
                // When the user wants to leave this serves as their leave
                else if (heart == history_end)
                    return 0;
            }
            // When the maximum possible score in logic (5) has been reached it breaks out of the
            // otherwise infinite loop
            if (score == max_question)
                break;
        }
        printf("Wow, awesome Player %i\nNow it's time for the MATHS theme\n(You can write the answers in "
               "words or in numbers)\n",
               name);
        while (true)
        {
            // Asking the math theme questions
            marker = math_theme(score);
            // When answer is correct
            if (marker == correct)
                score++;
            else
            {
                // When answer not correct(hearts reduce)
                heart = heart_system(heart, score);
                // The conditions that allow for the checkpoint system to function
                if (heart == 0)
                {
                    score = 0;           // Goes back to the first question if they want
                    heart = no_of_heart; // Refills heart
                }
                else if (heart == max_question)
                {
                    score = max_question; // Goes back to the beginning of maths if they want
                    heart = no_of_heart;
                }
                // Leaves when user asks to quit
                else if (heart == history_end)
                    return 0;
            }
            // When the maximum possible score in maths (10) has been reached it breaks out of the
            // otherwise infinite loop
            if (score == maths_end)
                break;
        }
        printf("Wow, You're good Player %i, but can you beat the HISTORY theme :)\nLet's see\n", name);
        while (true)
        {
            // Asking the math theme questions
            marker = history_theme(score);
            // When answer is correct
            if (marker == correct)
                score++;
            else
            {
                // When answer not correct(hearts reduce)
                heart = heart_system(heart, score);
                // The conditions that allow for the checkpoint system to function
                if (heart == 0)
                {
                    score = 0;           // Goes back to the first question if they want
                    heart = no_of_heart; // Refills heart
                }
                else if (heart == max_question)
                {
                    score = max_question; // Goes back to the beginning of maths if they want
                    heart = no_of_heart;
                }
                else if (heart == maths_end)
                {
                    score = maths_end; // Goes back to the beginning of history if they want
                    heart = no_of_heart;
                }
                // Leaves when user asks to quit
                else if (heart == history_end)
                    return 0;
            }
            // When the maximum possible score in history (15) has been reached it breaks out of the
            // otherwise infinite loop
            if (score == history_end)
                break;
        }
        // Ending messsage
        printf("....Congratssss Player %i!!!....\n"
               "You're officially the ..RIDDLE MASTER.. Good job\n"
               "Well, see you again Bye for now:)\n",
               name);
    }

    else
        // When player not ready to play
        printf("Ok byeeee :)\n");
    return 0;
}

// Function for Greetings message
int greetings(void)
{
    printf("...Welcome To Riddle Time...\n");
    int name = get_int("Choose a player number: ");
    printf("Hello, Player %i.\n", name);
    return name;
}

// Function for Checking if ready or not
char willing(void)
{
    char ready;
    do
    {
        ready = get_char("Are you ready for some riddles?(Y/N): ");
    }
    while (ready != 'n' && ready != 'N' && ready != 'y' && ready != 'Y');
    return ready;
}

// Function for displaying rules
void rules(int name)
{
    printf("Ok then :)\nThe rules are simple:\n*Answer 5 riddles under the themes: Logic, Math and "
           "History.\n*Example:\nI speak without a mouth and hear without ears. I have no body, "
           "but I come alive with wind. What am I?\nAnswer: Echo or ECHO or echo (These are the "
           "only acceptable formats of answer unless specified)\n*You have three (3) hearts if you "
           "lose all you start from the beginning ;)\nCan you get to the end and claim the title "
           "of riddle master?\nGoodluck Player %i!\n",
           name);
}

// Function for displaying the question and checking for correctness in the logic theme
int logic_theme(int score)
{
    if (score == 0)
    {
        string player_answer =
            get_string("Question 1:\nI have keys but no locks, I have space but no room, you can "
                       "enter but not go outside. What am I?\n"); // Question
        return match(player_answer, "Keyboard", "KEYBOARD", "keyboard", "", "", "",
                     ""); // Answer check
    }
    else if (score == 1)
    {
        string player_answer =
            get_string("Question 2:\nThe more you take from me, the bigger I get. What am I?\n");
        return match(player_answer, "HOLE", "hole", "Hole", "", "", "", "");
    }
    else if (score == 2)
    {
        string player_answer =
            get_string("Question 3:\nYou see a boat filled with people, yet there isn’t "
                       "a single person on board. How is that possible?\nThey are ");
        return match(player_answer, "married", "Married", "MARRIED", "", "", "", "");
    }
    else if (score == 3)
    {
        string player_answer =
            get_string("Question 4:\nForward I am heavy, but backward I am not. What am I?\n");
        return match(player_answer, "ton", "TON", "Ton", "", "", "", "");
    }
    else if (score == 4)
    {
        string player_answer =
            get_string("Question 5:\nI can be cracked, made, told, and played. What am I?\n");
        return match(player_answer, "JOKE", "joke", "Joke", "", "", "", "");
    }
    else
        return correct; // Just catching possibilities
}

// Function for displaying the question and checking for correctness in the math theme
int math_theme(int score)
{
    if (score == 5)
    {
        printf("Checkpoint!\n");
        string player_answer =
            get_string("Question 1:\nI am a three-digit number. My tens digit is five more than my "
                       "ones digit. "
                       "My hundreds digit is eight less than my tens digit. What number am I?\n");
        return match(player_answer, "194", "one hundred and ninety four",
                     "ONE HUNDRED AND NINETY FOUR", "One Hundred and Ninety Four", "1 9 4", "", "");
    }
    else if (score == 6)
    {
        string player_answer =
            get_string("Question 2:\nWhat number comes next in the sequence: 1, 4, 9, 16, 25, ?\n");
        return match(player_answer, "36", "Thirty-six", "Thirty six", "THIRTY SIX", "THIRTY-SIX",
                     "thirty-six", "thirty six");
    }
    else if (score == 7)
    {
        string player_answer = get_string(
            "Question 3:\nIf two’s company and three’s a crowd, what are four and five?\n");
        return match(player_answer, "9", "Nine", "NINE", "nine", "", "", "");
    }
    else if (score == 8)
    {
        string player_answer =
            get_string("Question 4:\nI’m an odd number. Take away a letter and I "
                       "become even. What number am I?\n");
        return match(player_answer, "7", "seven", "SEVEN", "Seven", "", "", "");
    }
    else if (score == 9)
    {
        string player_answer =
            get_string("Question 5:\nIf it takes 5 machines 5 minutes to make 5 gadgets, how many "
                       "minutes would 100 machines take to make 100 gadgets?\n");
        // This one has a hint so I couldn't treat it like the others
        string answer1 = "5";
        string answer2 = "FIVE";
        string answer3 = "five";
        string answer4 = "Five";
        if (word_checker(answer1, player_answer) == correct ||
            word_checker(answer2, player_answer) == correct ||
            word_checker(answer3, player_answer) == correct ||
            word_checker(answer4, player_answer) == correct)
            return correct;
        else
        {
            printf("Hint: Same Time\n");
            return wrong;
        }
    }
    else
        return correct;
}

// Function for displaying the question and checking for correctness in the history theme
int history_theme(int score)
{
    if (score == 10)
    {
        printf("Checkpoint!\n");
        string player_answer =
            get_string("Question 1:\nWhat event in 1960 changed Nigeria’s status as a colony?\n");
        return match(player_answer, "independence", "INDEPENDENCE", "Independence", "", "", "", "");
    }
    else if (score == 11)
    {
        string player_answer = get_string("Question 2:\nWho was Nigeria’s first president after "
                                          "becoming a republic?(First and Last Name)\n");
        return match(player_answer, "Nnamdi Azikiwe", "nnamdi azikiwe", "NNAMDI AZIKIWE", "", "",
                     "", "");
    }
    else if (score == 12)
    {
        string player_answer =
            get_string("Question 3:\nWhat was the name of the ship that famously "
                       "sank on its first voyage in 1912?\nThe ");
        return match(player_answer, "Titanic", "TITANIC", "titanic", "", "", "", "");
    }
    else if (score == 13)
    {
        string player_answer =
            get_string("Question 4:\nWho gave the famous “I Have a Dream” speech "
                       "in 1963(Full name(How it's popularly said))\n");
        return match(player_answer, "Martin Luther King Jr.", "MARTIN LUTHER KING JR.",
                     "martin luther king jr.", "", "", "", "");
    }
    else if (score == 14)
    {
        string player_answer =
            get_string("Question 5:\nWhat country is known as the 'Giant of Africa'?\n");
        return match(player_answer, "Nigeria", "NIGERIA", "nigeria", "", "", "", "");
    }
    else
        return correct;
}

// Function for dealing with matters of the heart
int heart_system(int heart, int score)
{
    heart--; // Reduces the heart by one
    if (heart > 0)
        printf("You have %i heart(s) remaining\nBe careful!\n",
               heart); // Continues after printing this if heart is 2 or 1
    else
    {
        // When hearts are used up
        printf("Oops! You've run out of hearts\n");
        heart = checkpoint(score); // Integrates the Checkpoint system
    }
    return heart;
}

// Function for the checkpoints
int checkpoint(int score)
{
    char Continue;
    // Checking for next step after using up all hearts
    do
    {
        Continue = get_char("Would you like to start over?(1)\n"
                            "Would you like to go to checkpoint and start from there(2)\n"
                            "Or end game(3): ");
    }
    while (Continue != '1' && Continue != '2' &&
           Continue != '3'); // Won't move on until a valid answer 1, 2 or 3 is in
    // If wants to go to a checkpoint
    if (Continue == '2')
    {
        printf("Going to checkpoint then...\n");
        // If user is still at logic theme
        if (score > 0 && score < max_question)
        {
            printf("Well the beginning is still your checkpoint\nSo, back to the beginning....\n");
            return 0;
        }
        // If user is still at math theme
        else if (score >= max_question && score < maths_end)
            return max_question;
        // If user is in History theme
        else
            return maths_end;
    }
    // If they want to start from the top
    else if (Continue == '1')
        return 0;
    // If they want to quit
    else
    {
        printf("Ok Byee :)\n");
        return history_end;
    }
}

// For counting number of characters in the answer string to use for a loop later
int word_counter(string answer)
{
    int i = 0;
    while (answer[i] != '\0')
    {
        i++;
    }
    return i;
}

// Checking if the players answer matches each answer
int word_checker(string answer, string player_answer)
{
    int i = 0, same = 0;
    while (i <= word_counter(answer))
    {
        if (answer[i] == (char) player_answer[i])
        {
            same++;
            i++;
        }
        else
            i++;
    }
    if (same == word_counter(answer) + 1)
        return correct;
    else
        return wrong;
}

// Checking if the players answer matches any of the answers
int match(string player_answer, string answer1, string answer2, string answer3, string answer4,
          string answer5, string answer6, string answer7)
{
    if (player_answer[0] != '\0' && (word_checker(answer1, player_answer) == correct ||
                                     word_checker(answer2, player_answer) == correct ||
                                     word_checker(answer3, player_answer) == correct ||
                                     word_checker(answer4, player_answer) == correct ||
                                     word_checker(answer5, player_answer) == correct ||
                                     word_checker(answer6, player_answer) == correct ||
                                     word_checker(answer7, player_answer) == correct))
        return correct;
    else
        return wrong;
}
