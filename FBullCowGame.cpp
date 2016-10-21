//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Aaron Silverman on 8/28/16.
//  Copyright © 2016 Aaron Silverman. All rights reserved.
//

#pragma once
#include "FBullCowGame.hpp"

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame(){
    reset();
}

void FBullCowGame::reset()
{
    myCurrentTry = 1;
    myHiddenWord = "planet";
    bGameIsWon = false;
    return;
}


int32 FBullCowGame::getMaxTries() const
{
    return 2 * getHiddenWordLength() + 2;
}


int32 FBullCowGame::getCurrentTry() const
{
    return myCurrentTry;
}

int32 FBullCowGame::getHiddenWordLength() const
{
    return (int32)myHiddenWord.length();
}


bool FBullCowGame::isGameWon() const
{
    return bGameIsWon;
}


EWordStatus FBullCowGame::checkGuessValidity(FString guess) const
{
    // if the guess isn't an isogram, return an error
    if (!isIsogram(guess))
    {
        return EWordStatus::Not_Isogram;
    }
    // if the guess isn't all lowercase, return an error
    else if (!isLowerCase(guess))
    {
        return EWordStatus::Not_Lowercase;
    }
    // if the guess isn't guess length is wrong, return an error
    else if (guess.length() != getHiddenWordLength()){
        return EWordStatus::Wrong_Length;
    }
    // otherwise, return ok
    return EWordStatus::OK;
}

FBullCowCount FBullCowGame::submitValidGuess(FString guess)
{
    myCurrentTry++;
    FBullCowCount bullCowCount;
    
    // loop through all the letters in the hidden word
    int32 wordLength = getHiddenWordLength(); // assuming same length as guess
    for (int32 MHWChar = 0; MHWChar < wordLength; MHWChar++)
    {
        // compare letters against the hidden word
        for (int32 GChar = 0; GChar < wordLength; GChar++)
        {
            // if they match then
            if (guess[MHWChar] == myHiddenWord[GChar])
            {
                // if they're in the same place
                if ( MHWChar == GChar )
                {
                    // increment bulls
                    bullCowCount.bulls++;
                }
                else
                {
                    // increment cows
                    bullCowCount.cows++;
                }
            }
        }
    }
    
    if (bullCowCount.bulls == wordLength){
        bGameIsWon = true;
    }
    else {
        bGameIsWon = false;
    }
    
    return bullCowCount;
}

bool FBullCowGame::isIsogram(FString word) const
{
    // return true for corner cases of zero and one letter strings
    if(word.length() <= 1) { return true; }
    // create hashtable
    TMap<char, bool> letterSeen;
    // loop through guess
    for (auto letter : word)
    {
        letter = tolower(letter); // handle mixed case
        // check each letter against hash table
        // if it has not been seen before
        if(letterSeen[letter] == false)
        {
            //set corresponding value for that letter to false
            letterSeen[letter] = true;
        } else {
            return false;
        }
    }
    // if loop exits it is an isogram (no letters have been seen twice), so return true
    return true;
}

bool FBullCowGame::isLowerCase(FString word) const
{
    for (auto letter : word)
    {
        if(!islower(letter)){
            return false;
        }
    }
    return true;
}
