// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_PluginPrivatePCH.h"
#include "AI_Plugin.h"
#include "MyPluginComponent.h"


// Sets default values
AMyPluginComponent::AMyPluginComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPluginComponent::BeginPlay()
{
	Super::BeginPlay();
	
	GLog->Log("BeginPlay inside plugin component");
}

// Called every frame
void AMyPluginComponent::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

