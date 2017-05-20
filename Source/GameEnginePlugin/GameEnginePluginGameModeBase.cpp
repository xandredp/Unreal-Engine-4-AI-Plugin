// Fill out your copyright notice in the Description page of Project Settings.

#include "GameEnginePlugin.h"
#include "GameEnginePluginGameModeBase.h"
#include "PlayerCharacter.h"



AGameEnginePluginGameModeBase::AGameEnginePluginGameModeBase()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

