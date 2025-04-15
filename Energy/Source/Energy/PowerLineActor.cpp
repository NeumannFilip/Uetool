#include "PowerLineActor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

APowerLineActor::APowerLineActor()
{
    // PrimaryActorTick.bCanEverTick = true; // Only enable if you actually use Tick

    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
    RootComponent = SplineComponent;
    SplineComponent->SetMobility(EComponentMobility::Static); // Assume power lines are static

    // Optional: Provide default points, but the tool will overwrite them anyway
    // SplineComponent->AddSplinePoint(FVector(0, 0, 0), ESplineCoordinateSpace::Local);
    // SplineComponent->AddSplinePoint(FVector(500, 0, 0), ESplineCoordinateSpace::Local);
}

void APowerLineActor::GenerateSplineMeshes()
{
    if (!SplineComponent) return;

    // 1. Clear existing generated meshes
    // Use the stored array for efficient cleanup
    for (USplineMeshComponent* MeshComp : GeneratedSplineMeshes)
    {
        if (MeshComp)
        {
            MeshComp->DestroyComponent();
        }
    }
    GeneratedSplineMeshes.Empty(); // Clear the array

    // 2. Check prerequisites
    if (!CableMesh)
    {
        //UE_LOG(LogTemp, Warning, TEXT("APowerLineActor '%s': CableMesh is not set."), *GetName());
        return; 
    }

    const int32 NumPoints = SplineComponent->GetNumberOfSplinePoints();
    const int32 NumSegments = NumPoints - 1;

    if (NumSegments < 1)
    {
        //UE_LOG(LogTemp, Log, TEXT("APowerLineActor '%s': Not enough spline points to generate meshes."), *GetName());
        return; // Not enough points to make a line segment
    }

    // 3. Generate new meshes
    SplineComponent->UpdateSpline();

    for (int32 i = 0; i < NumSegments; ++i)
    {
        USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
        if (!SplineMesh) continue;

        SplineMesh->SetStaticMesh(CableMesh);
        SplineMesh->SetForwardAxis(ESplineMeshAxis::X); // Often X or Y is forward for cables, adjust as needed per mesh
        SplineMesh->SetMobility(EComponentMobility::Static); // Match root

        // --- Use CableThickness ---
        // Apply thickness uniformly. Assumes the cable mesh is modeled with a radius/diameter of 1 unit.
        // Adjust Z scale if your thickness represents diameter and mesh is aligned differently.
        const FVector2D CableScale(CableThickness, CableThickness);
        SplineMesh->SetStartScale(CableScale);
        SplineMesh->SetEndScale(CableScale);
        // ---

        SplineMesh->SetupAttachment(SplineComponent); // Attach to the spline itself
        SplineMesh->RegisterComponent(); // Make the component usable

        // Get spline data in LOCAL space since the mesh component is attached to the spline component
        FVector StartPos, StartTangent, EndPos, EndTangent;
        SplineComponent->GetLocationAndTangentAtSplinePoint(i, StartPos, StartTangent, ESplineCoordinateSpace::Local);
        SplineComponent->GetLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent, ESplineCoordinateSpace::Local);

        // Set spline parameters
        SplineMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent, true /*bUpdateMesh*/);

        // Optional: Set material (Uncomment and assign CableMaterial if you add that property)
        // if (CableMaterial)
        // {
        //    SplineMesh->SetMaterial(0, CableMaterial);
        // }

        // Add to our tracking array
        GeneratedSplineMeshes.Add(SplineMesh);
    }
}

void APowerLineActor::BeginPlay()
{
    Super::BeginPlay();
}

void APowerLineActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    GenerateSplineMeshes();
}