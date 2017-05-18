// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_Plugin/Private/AI_PluginPrivatePCH.h"
#include "TypeClass.generated.h"


UENUM()
enum class EBotBehaviorType : uint8
{
	// passive patrolling mode
	Neutral,
	//hearing or seeing someone. 
	Suspicious,
	//Running towards the player and attacking
	Agression,
	//Flee.
	Flee,
};


/**
 * 
 */
class AI_PLUGIN_API TypeClass
{
public:
	TypeClass();
	~TypeClass();
};
