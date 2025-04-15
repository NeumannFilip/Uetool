// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PowerLineToolLibrary.generated.h"

class APowerLineActor;
/**
 * 
 */
UCLASS()
class ENERGY_API UPowerLineToolLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable, Category=PowerLineToll, meta = (WorldContext = WorldContextObject))
	static void CreatePowerLineFromSelectedActors(const UObject* WorldContextObject, TSubclassOf<APowerLineActor> PowerLineClass);
	
};
