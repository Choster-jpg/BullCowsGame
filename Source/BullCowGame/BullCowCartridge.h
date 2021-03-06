// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:

	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void EndGame();
	void ProcessGuess(FString Guess);
	bool IsIsogram(FString Word) const;
	void GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const;
	
	
	// Your declarations go below!
	private:
		int32 Lives;
		FString HiddenWord;
		bool bGameOver;
};
