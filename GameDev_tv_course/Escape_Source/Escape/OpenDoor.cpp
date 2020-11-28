// Dips&Chips

#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;

	if(!PreassurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s has OpenDoor component but no PreassurePlate set"), *GetOwner()->GetName());
	}
	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	FindAudioComponent();
}

	
// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// If the player enters the trigger volume
	if (TotalOverlappingMass() > MassToOpenDoor	) 
	{
		// Open the door
		OpenDoor(DeltaTime, DoorOpenSpeed);
		
		// Get the timestamp of when the volume was entered
		DoorLastOpened = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Log, TEXT("TimeStamp is: %.2f"), DoorLastOpened);
	}
	// If the player exits the trigger volume 
	else
	{
		// If the difference between the current time and the time the door was opened is 
		// equal or greater then the door close delay
		if ((GetWorld()->GetTimeSeconds() - DoorLastOpened) >= DoorCloseDelay) {
			CloseDoor(DeltaTime, DoorCloseSpeed);
			OpenDoorSound = false;
		}
	}
	
}

void UOpenDoor::OpenDoor(float DeltaTime, float DoorSpeed) 
{
	// Current door rotation
	FRotator DoorRot = GetOwner()->GetActorRotation();
	// Interpolate position
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, DoorSpeed);
	// Set Yaw value to rotator
	DoorRot.Yaw = CurrentYaw;
	// Set Actor rotation
	GetOwner()->SetActorRotation(DoorRot);
	
	// Protect from nullptr
	if (!AudioComponent) { return; }
	// Play door sound once
	if(!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
		// Set CloseDoorSound to false
		CloseDoorSound = false;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime, float DoorSpeed) 
{
	// Current door rotation
	FRotator DoorRot = GetOwner()->GetActorRotation();
	// Interpolate position
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime , DoorSpeed);
	// Set Yaw value to rotator
	DoorRot.Yaw = CurrentYaw;
	// Set Actor rotation
	GetOwner()->SetActorRotation(DoorRot);
	
	// Protect from nullptr
	if (!AudioComponent) { return; }
	// Play door sound once
	if (!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
		// Set OpenDoorSound to false
		OpenDoorSound = false;
	}

}

float UOpenDoor::TotalOverlappingMass()
{
	float TotalOverlappingMass = 0.0f;

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;

	// Add the mass of the overlapping actors
	PreassurePlate->GetOverlappingActors(OverlappingActors);

	for( AActor* Actor : OverlappingActors)
	{
		TotalOverlappingMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return TotalOverlappingMass;
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if(!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing AudioComponent on Actor %s"), *GetOwner()->GetName());
	}
}