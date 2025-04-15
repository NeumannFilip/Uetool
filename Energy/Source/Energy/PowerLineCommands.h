// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Framework/Commands/Commands.h"
/**
 * 
 */
class FPowerLineCommands : public TCommands<FPowerLineCommands>
{
public:
	FPowerLineCommands();

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> CreatePowerLineCommand;
	
};
