// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        InitGame();
        return;
    }

    ClearScreen();
    PrintLine(TEXT("You guessed;"));
    PrintLine(Input);

    GuessCheck(Input);
}

void UBullCowCartridge::InitGame()
{
    HiddenWord = Words[FMath::RandRange(0, 19)];
    PlayerLives = 3;
    WrdLng = HiddenWord.Len();
    bGameOver = false;

    ClearScreen();

    PrintLine(TEXT("Welcome to Bulls & Cows!"));
    PrintLine(TEXT("Guess the %i letter word!\n"), WrdLng);
    PrintLine(TEXT("The word is %s"), *HiddenWord);
}

void UBullCowCartridge::GuessCheck(const FString& Guess)
{
    int32 InptLng = Guess.Len();

    if (WrdLng != InptLng)
    {
        PrintLine(TEXT("The word has %i letters in. Try again!"), WrdLng);
        return;
    }

    if (!IsoCheck(Guess, InptLng))
    {
        PrintLine(TEXT("The word is an isogram. Try again!"));
        return;
    }

    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("\nYou guessed correctly!"));
        EndGame();
    }
    else
    {
        FBullsCowsCount Bulls = BullCheck(Guess);
        FBullsCowsCount Cows = CowCheck(Guess);
        
        --PlayerLives;

        if (PlayerLives > 0)
        {
            PrintLine(TEXT("\nIncorrect! Try again!"));
            PrintLine(TEXT("You have %i lives left."), PlayerLives);
            PrintLine(TEXT("\nThere are %i Bulls and %i Cows."), Bulls.BullCount, Cows.CowCount);
        }
    }

    
    if (PlayerLives == 0)
    {
        PrintLine(TEXT("\nYou are out of lives!"));
        PrintLine(TEXT("\nThe hidden word was; %s"), *HiddenWord);
        EndGame();
    }
}

bool UBullCowCartridge::IsoCheck(const FString& Guess, int32 Length)
{
    for (int32 i = 0; i < Length-1; ++i)
    {
        for (int32 j = i+1; j < Length; ++j)
        {
            if (Guess[i] == Guess[j])
            {
                return false;
            }
        }
    }
    return true;
}

FBullsCowsCount UBullCowCartridge::BullCheck(const FString& Guess)
{
    FBullsCowsCount Count;

    for (int32 i = 0; i < WrdLng; ++i)
    {
        if (Guess.ToUpper()[i] == HiddenWord.ToUpper()[i])
        {
            ++Count.BullCount;
        }
    }
    return Count;
}

FBullsCowsCount UBullCowCartridge::CowCheck(const FString& Guess)
{
    FBullsCowsCount Count;

    for (int32 i = 0; i < WrdLng; ++i)
    {
        for (int32 j = 0; j < WrdLng; ++j)
        {
            if (j != i)
            {
                if (Guess.ToUpper()[i] == HiddenWord.ToUpper()[j])
                {
                    ++Count.CowCount;
                }
            }
        }
    }
    return Count;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again!"));
}

