// Fill out your copyright notice in the Description page of Project Settings.

#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
}
void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }     
}

void UBullCowCartridge::SetupGame()
{
    ClearScreen();
    HiddenWord = Words[FMath::RandRange(0, Words.Num()-1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("The hidden word is: %s \nGuess the %i letter word!\nYou have %i lives."), *HiddenWord, HiddenWord.Len(), Lives);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press ENTER to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
        EndGame();
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, try again"));
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word has 4 characters.Try again\nYou have %i lives now"), Lives);
        return;
    }

    --Lives;

    if (Lives <= 0)
    {
        PrintLine(TEXT("You have lost!"));
        PrintLine(TEXT("\nThe hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }

    int32 Bulls, Cows;
    GetBullCows(Guess, Bulls, Cows);

    PrintLine(TEXT("You have %i bulls and %i cows."), Bulls, Cows);

    PrintLine(TEXT("Incorrect answer.\nYou have %i lives now"), Lives);                
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 Index = 0; Index < Word.Len()-1; Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
                return false;
        }
    }

    return true;
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount = 0;
    CowCount = 0;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            BullCount++;
            continue;
        }

        for  (int32 i = 0; i < Guess.Len(); i++)
        {
            if (Guess[GuessIndex] == HiddenWord[i])
            {
                CowCount++;
                break;
            }
        }
    }
}
