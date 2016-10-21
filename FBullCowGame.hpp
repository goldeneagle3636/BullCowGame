//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Aaron Silverman on 8/28/16.
//  Copyright © 2016 Aaron Silverman. All rights reserved.
//

/* The game logic (direct user interaction)
 * for a simple word guessing game based on mastermind
 */

#pragma once
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <iostream>
#include <string>
#include <map>
#define TMap std::map

#endif /* FBullCowGame_hpp */

// make syntax unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 bulls = 0;
    int32 cows = 0;
};

enum class EWordStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    FBullCowGame();
    
    int32 getMaxTries() const;
    int32 getCurrentTry() const;
    int32 getHiddenWordLength() const;
    
    bool isGameWon() const;
    EWordStatus checkGuessValidity(FString) const;
    
    void reset();
    
    // counts bulls and cows, and increases try # assuming valid guess
    FBullCowCount submitValidGuess(FString);

private:
    // see constructor for initialization
    bool bGameIsWon;
    int32 myCurrentTry;
    FString myHiddenWord;
    
    bool isIsogram(FString) const;
    bool isLowerCase(FString) const;
};
