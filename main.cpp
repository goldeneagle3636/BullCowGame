//
//  main.cpp
//  BullCowGame
//
//  Created by Aaron Silverman on 8/27/16.
//  Copyright © 2016 Aaron Silverman. All rights reserved.
//

/* This is the console exacutable that makes use of the BullCow class.
 * This acts as the view in a MVC pattern, and is responsible for all
 * user interaction. For game logic see the FBullCowGame class.
 */

#pragma once
#include <iostream>
#include <string>
#include "fBullCowGame.hpp"

// to make syntax unreal friendly
using FString = std::string;
using int32 = int;

void print_intro();
FString getValidGuess();
void play_game();
void printGameSummary();
bool ask_to_play_again();


FBullCowGame BCGame;


// Entry point32 for application
int main(int32 arc, const char * argv[])
{
    do
    {
        print_intro();
        play_game();
    } while(ask_to_play_again());
    return 0; // exit the application
}

// play the main game
void play_game()
{
    BCGame.reset();
    int32 maxTries = BCGame.getMaxTries();
    
    // loop asking for guesses while the game is not won
    // and there are still tries remaining
    while(!BCGame.isGameWon() && BCGame.getCurrentTry() <= maxTries){
        
        FString guess = getValidGuess();
        
        
        // submit valid guess to the game, and recieve counts
        FBullCowCount bullCowCount = BCGame.submitValidGuess(guess);
        
        // repeat the guess back to them
        std::cout << "Bulls = " << bullCowCount.bulls << "\n";
        std::cout << "Cows = " << bullCowCount.cows << "\n\n";
    }
    
    printGameSummary();
    
    return;
}

// introduce the game
void print_intro()
{
    std::cout << "=========================================================\n";
    std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
    std::cout << "Can you guess the " << BCGame.getHiddenWordLength();
    std::cout << " letter isogram I am thinking of?" << std::endl;
    return;
}

// Get a guess from the player, loop until valid
FString getValidGuess()
{
    EWordStatus status = EWordStatus::Invalid_Status;
    FString guess = "";
    do{
        // get a guess from the player
        std::cout << "try " << BCGame.getCurrentTry() << " of " << BCGame.getMaxTries() << ". Enter your guess: ";
        getline(std::cin,guess);
        
        // check guess validity
        
        status = BCGame.checkGuessValidity(guess);
        
        switch(status)
        {
            case EWordStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word. \n\n";
                break;
            case EWordStatus::Not_Lowercase:
                std::cout << "Please enter a word in lower case. \n\n";
                break;
            case EWordStatus::Not_Isogram:
                std::cout << "Please enter a word with no repeating characters. \n\n";
                break;
            default:
                break;
        }
    } while(status != EWordStatus::OK);

    return guess;
}

void printGameSummary(){
    if(BCGame.isGameWon())
    {
        std::cout << "Good job! You won!\n";
    } else {
        std::cout << "Better luck next time!\n";
    }
}

bool ask_to_play_again()
{
    std::cout << "Do you want to play again with the same word? (y/n)";
    FString response = "";
    getline(std::cin, response);
    if(response[0] == 'y' || response[0] == 'Y') return true;
    else return false;
}
