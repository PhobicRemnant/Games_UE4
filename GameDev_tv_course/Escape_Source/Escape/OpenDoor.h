// Dips&Chips

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime, float DoorSpeed);
	void CloseDoor(float DeltaTime, float DoorSpeed);
	float TotalOverlappingMass();
	void FindAudioComponent();

private:

	float InitialYaw;
	float CurrentYaw;
	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PreassurePlate = nullptr;

	UPROPERTY(EditAnywhere)	
	AActor* ActorThatOpens = nullptr;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.5f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 1.2f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 1.2f;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 25.f;
	
	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

	

};
