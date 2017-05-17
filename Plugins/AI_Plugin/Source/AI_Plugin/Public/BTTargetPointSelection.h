// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI_Plugin/Private/AI_PluginPrivatePCH.h"
#include "BTTargetPointSelection.generated.h"


UCLASS()
class UBTTargetPointSelection : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
