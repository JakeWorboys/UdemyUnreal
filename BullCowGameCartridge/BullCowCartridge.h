// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullsCowsCount 
{
	int32 BullCount = 0;
	int32 CowCount = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void InitGame();
	void EndGame();
	void GuessCheck(const FString& Guess);
	bool IsoCheck(const FString& Guess, int32 Length);
	FBullsCowsCount BullCheck(const FString& Guess);
	FBullsCowsCount CowCheck(const FString& Guess);

	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 PlayerLives;
	int32 WrdLng;
	bool bGameOver;
};
