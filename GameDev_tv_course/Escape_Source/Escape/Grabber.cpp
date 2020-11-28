// Dips&Chips

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	
	FindPhysicsHandle();
	SetupInputComponent();

}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Protect code to nullptr in case there is nothing in reach
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		// Move the object we are holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}	 
	
	
}

void UGrabber::Grab() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed!"));

	// Raycast when grabber is pressed
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	// Get component for physics handle
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	// If we hit something
	 if(HitResult.GetActor())
	{
			 PhysicsHandle->GrabComponentAtLocation
			 (
				 ComponentToGrab,
				 NAME_None,
				 GetReachLineEnd()
			 );
	}
	
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released!"));
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandle()  
{
	// Get physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// If the pointer is null log 
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}

}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{

	// Declare a hit result
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	// Ray-cast out to the distance of Reach
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{	 
		UE_LOG(LogTemp, Warning, TEXT("Hitting: %s"), *ActorHit->GetName());
	}

	return Hit;
}

FVector UGrabber::GetReachLineEnd() const
{
	// Get player's view points
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	// Get player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( OUT PlayerViewPointLocation,
																OUT PlayerViewPointRotation);
	// Declare the end of the player's reach with the viewpoint reference
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::GetReachLineStart() const
{
	// Get player's view points
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	// Get player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation,
															   OUT PlayerViewPointRotation);
	return PlayerViewPointLocation;
	
}


/*
### Great piece of code to debug the point of view of a pawn or an actor

// Define line of reach for controller

FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;

// Draw line of reach
DrawDebugLine(GetWorld(),
	PlayerViewPointLocation,
	LineTraceEnd,
	FColor(0,255,0),
	false,
	0.f,
	0,
	5.f
);
*/