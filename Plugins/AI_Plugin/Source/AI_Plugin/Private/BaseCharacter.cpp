// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	NoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitterComp"));

	Health = 100;
	Stamina = 100;
	bIsAlive = true;
	ValToMakePawnUnDetected = 0.0;


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABaseCharacter::MakePawnNoise(float Loudness)
{
	/* Make noise to be picked up by PawnSensingComponent by the enemy pawns */
	MakeNoise(Loudness, this, GetActorLocation());

	//LastNoiseLoudness = Loudness;
	//LastMakeNoiseTime = GetWorld()->GetTimeSeconds();
}
