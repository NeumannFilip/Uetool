#include "PowerLineToolLibrary.h"
#include "PowerLineActor.h" // Include the actor header
#include "Components/SplineComponent.h" // Include for spline component access
#include "Engine/World.h" // Include for UWorld
#include "GameFramework/Actor.h" // Include for AActor

// Editor-specific includes
#if WITH_EDITOR
#include "Editor.h"
#include "Selection.h" 
#include "ScopedTransaction.h" 
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#endif

void UPowerLineToolLibrary::CreatePowerLineFromSelectedActors(const UObject* WorldContextObject, TSubclassOf<APowerLineActor> PowerLineClass)
{
#if WITH_EDITOR // Entire function is editor-only
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    if (!World || !GEditor) // Check GEditor
    {
        UE_LOG(LogTemp, Error, TEXT("PowerLineTool: Invalid World or Editor context."));
        return;
    }

    if (!PowerLineClass)
    {
         FNotificationInfo Info(FText::FromString("PowerLine Tool Error: No PowerLine Actor Class specified!"));
         Info.ExpireDuration = 5.0f;
         Info.bUseSuccessFailIcons = true;
        // notification error
         TSharedPtr<SNotificationItem> Notification = FSlateNotificationManager::Get().AddNotification(Info);
         if (Notification.IsValid()) { Notification->SetCompletionState(SNotificationItem::CS_Fail); }
         UE_LOG(LogTemp, Error, TEXT("PowerLineTool: PowerLineClass is null."));
         return;
    }


    TArray<AActor*> SelectedActors;
    GEditor->GetSelectedActors()->GetSelectedObjects(SelectedActors);

    //validation
    if (SelectedActors.Num() < 2)
    {
       FNotificationInfo Info(FText::FromString("PowerLine Tool: Select at least 2 actors to connect!"));
       Info.ExpireDuration = 5.0f;
       Info.bUseSuccessFailIcons = true;
       // Warning
       TSharedPtr<SNotificationItem> Notification = FSlateNotificationManager::Get().AddNotification(Info);
       if (Notification.IsValid()) { Notification->SetCompletionState(SNotificationItem::CS_Fail); }

       UE_LOG(LogTemp, Warning, TEXT("PowerLineTool: Select at least 2 actors!"));
       return;
    }

    //Undo/Redo Support
    //TODO: necessary?
    const FScopedTransaction Transaction(FText::FromString("Create Power Line Actor"));
    World->Modify();
    // If your PowerLineActor's OnConstruction modifies itself, it might need: NewPowerLine->Modify(); later

    //Spawn
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    SpawnParams.bCreateActorPackage = true;
    // SpawnParams.OverrideLevel = World->PersistentLevel; // Correct for WP

    APowerLineActor* NewPowerLine = World->SpawnActor<APowerLineActor>(
        PowerLineClass,
        SelectedActors[0]->GetActorLocation(),
        FRotator::ZeroRotator,
        SpawnParams
    );

    if (NewPowerLine && NewPowerLine->SplineComponent)
    {
        // Modify the new actor before changing its state for Undo
        NewPowerLine->Modify();
        NewPowerLine->SplineComponent->Modify(); // Modify the component too

        NewPowerLine->SplineComponent->ClearSplinePoints(false); // Don't update spline yet

        // Make sure actor label is useful
        FString ActorLabel = FString::Printf(TEXT("PowerLine_%s_to_%s"), *SelectedActors[0]->GetActorLabel(), *SelectedActors.Last()->GetActorLabel());
        NewPowerLine->SetActorLabel(ActorLabel);


        for (int32 i = 0; i < SelectedActors.Num(); ++i)
        {
            AActor* Actor = SelectedActors[i];
            if (Actor)
            {
                // Add point at the actor's location
                FVector Location = Actor->GetActorLocation();
                NewPowerLine->SplineComponent->AddSplinePoint(
                                                 Location,                   
                                                     ESplineCoordinateSpace::World, 
                                                        false                       
       );
                 // Tangents??
                 // Point.ArriveTangent = FVector::ZeroVector; 
                 // Point.LeaveTangent = FVector::ZeroVector; 
            }
        }

        // Update spline
        NewPowerLine->SplineComponent->UpdateSpline();

        // Trigger mesh generation (either by calling GenerateSplineMeshes or letting OnConstruction handle it if guaranteed)
        // If OnConstruction isn't reliable immediately after spawn/modify loop, call manually:
        NewPowerLine->GenerateSplineMeshes();


        // Optional: Select the newly created actor
        GEditor->SelectNone(false, true);
        GEditor->SelectActor(NewPowerLine, true, true);

        // Success notification
        FNotificationInfo Info(FText::Format(FText::FromString("Created Power Line: {0}"), FText::FromString(NewPowerLine->GetActorLabel())));
        Info.ExpireDuration = 5.0f;
        Info.bUseSuccessFailIcons = true;
        TSharedPtr<SNotificationItem> Notification = FSlateNotificationManager::Get().AddNotification(Info);
         if (Notification.IsValid()) { Notification->SetCompletionState(SNotificationItem::CS_Success); }

        UE_LOG(LogTemp, Log, TEXT("PowerLineTool: Successfully created %s"), *NewPowerLine->GetActorLabel());
    }
    else
    {
        //Log failure
        UE_LOG(LogTemp, Error, TEXT("PowerLineTool: Failed to spawn PowerLineActor!"));
        FNotificationInfo Info(FText::FromString("PowerLine Tool Error: Failed to spawn PowerLine Actor!"));
        Info.ExpireDuration = 5.0f;
        Info.bUseSuccessFailIcons = true;
        TSharedPtr<SNotificationItem> Notification = FSlateNotificationManager::Get().AddNotification(Info);
        if (Notification.IsValid()) { Notification->SetCompletionState(SNotificationItem::CS_Fail); }
         //Transaction.Cancel(); // Cancel undo transaction if spawn failed
    }

#else // !WITH_EDITOR
    UE_LOG(LogTemp, Error, TEXT("CreatePowerLineFromSelectedActors can only be called in the Editor."));
#endif // WITH_EDITOR
}