// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerLineActor.generated.h"

class USplineComponent;
class USplineMeshComponent;

UCLASS()
class ENERGY_API APowerLineActor : public AActor
{
	GENERATED_BODY()

public:
	APowerLineActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PowerLine)
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerLine)
	UStaticMesh* CableMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerLine, meta = (ClampMin = "0.1", UIMin = "0.1"))
	float CableThickness = 1.0f;
	
	void GenerateSplineMeshes();
	
protected:
	
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	private:
	UPROPERTY()
	TArray<TObjectPtr<USplineMeshComponent>> GeneratedSplineMeshes;

};