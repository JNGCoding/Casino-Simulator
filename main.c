/*
Program Briefing :
This is a simple casino simulator game written in C. The user inputs an amount of money and a percentage by which their result money will be increased. Based on the percentage, a difficulty level is assigned, and the user has 5 tries to guess a randomly generated number within a specified range. If they guess correctly, they win the prize; otherwise, they lose their money.

Program Flow :
1. The user is prompted to input an amount of money and an increase percentage.
2. The increase percentage is processed to determine the difficulty level.
3. A random number is generated within a range based on the difficulty level.
4. The user has 5 attempts to guess the number.
5. If the user guesses correctly, they win a prize; otherwise, they lose their money

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// Defining some macros
#define SUCCESS 0
#define FAILURE 1

// Structs with their functions
struct Range {  // This struct is defined in order to limit the range of random number generation.
    int min;
    int max;
};

// Variables
unsigned int input_money;  // Amount of money inputted by user will be stored here.
unsigned int increase_percentage;  // Percentage by which the result money will be increased.
struct Range difficulty_range = {0, 0};  // This will store the range of random number generation based on difficulty.
unsigned int difficulty_index = 0;  // 0 = Easy, 1 = Medium, 2 = Hard, 3 = Impossible
int user_input;  // User Guesses will be stored in this variable.

// Functions
void take_input(const char* question, const char* type, void* data) {  // This function is responsible to take input from user.
    printf(question);
    scanf(type, data);  // Take input
}

uint8_t in(unsigned int data, unsigned int min, unsigned int max) {  // Checks if a number is inside a certain range.
    if (data >= min && data <= max) return SUCCESS;
    return FAILURE;
}

int generate_random_number(const struct Range* range) {  // This function is responsible for generating a random number within the given range.
    return (rand() % (range->max - range->min + 1)) + range->min;
}

// Main
int main(int argv, char* argc[]) {
    srand(time(NULL));  // Setting a seed for random number generator.

    printf("Welcome to Casino Simulator.\n1) You will input some amount of money.\n2) You will input a percentage by which your result money will be increased.\n3) You will be assigned a difficulty level determined by the amount of increase percentage inputted by you.\n4) You will be given 5 tries, if you win you will be rewarded with the price else your money will not be returned.\n\n");
    take_input("Input your Amount : $", "%u", &input_money);  // Take input and store it into input_money
    take_input("Input your increase percentage : ", "%u", &increase_percentage);  // Take input and store it into increase percentage

    // Process Increase Percentage
    if (increase_percentage > 100) increase_percentage = 100;

    // Assigning difficulty according to increase percentage
    if (in(increase_percentage, 0, 25) == SUCCESS) {
        difficulty_range.min = -1;
        difficulty_range.max = 5;
        difficulty_index = 0;
    } else if (in(increase_percentage, 26, 50) == SUCCESS) {
        difficulty_range.min = -5;
        difficulty_range.max = 10;
        difficulty_index = 1;
    } else if (in(increase_percentage, 51, 75) == SUCCESS) {
        difficulty_range.min = -23;
        difficulty_range.max = 50;
        difficulty_index = 2;
    } else if (in(increase_percentage, 76, 100) == SUCCESS) {
        difficulty_range.min = -1000;
        difficulty_range.max = 1000;
        difficulty_index = 3;
    } else {
        difficulty_range.min = -10000;
        difficulty_range.max = 10000;   // If the program somehow breaks, We will make it impossible for the user to guess the number.
        difficulty_index = 4;
    }

    float prize = (float) input_money * (float) (100 + increase_percentage) / 100;  // Calculating the prize which we will give to the user.

    // Print the game information.
    printf("You have been assigned with the difficulty level : %u\n", difficulty_index);
    printf("Expected Result money : $%.02f\n", prize);

    // Generate a random number in the range.
    int random_number = generate_random_number(&difficulty_range);

    // Start the game.
    int win_flag = 0;
    for (int i = 0; i < 5; i++) {
        printf("Guess the number between %d and %d : ", difficulty_range.min, difficulty_range.max);  // Take User guess
        scanf("%d", &user_input);
        if (user_input == random_number) {
            win_flag = 1;
            break;
        } else if (user_input > random_number) {
            printf("Your guess, %d is higher than the random number.\n", user_input);
        } else {
            printf("Your guess, %d is lower than the random number.\n", user_input);
        }
    }

    if (win_flag) {
        printf("You won $%.02f\n", prize);
    } else {
        printf("You lost.\n");
    }

    return SUCCESS;
}