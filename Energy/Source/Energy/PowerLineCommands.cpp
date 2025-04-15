// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerLineCommands.h"
#include "Styling/AppStyle.h"

FPowerLineCommands::FPowerLineCommands()
	: TCommands<FPowerLineCommands>(
		TEXT("PowerLine"), 
		NSLOCTEXT("Contexts", "PowerLine", "Power Line Tool"), 
		NAME_None, 
		FAppStyle::GetAppStyleSetName()
	)
{}

void FPowerLineCommands::RegisterCommands()
{
}

