// Fill out your copyright notice in the Description page of Project Settings.
#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "SoundBlockingActor.h"


// Sets default values
ASoundBlockingActor::ASoundBlockingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoundBlockingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoundBlockingActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

