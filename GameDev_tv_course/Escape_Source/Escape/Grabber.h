// Dips&Chips

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	float Reach = 100.f;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;

	void Grab();	 
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();
	
	// Return the first actor within reach with a physics body
	FHitResult GetFirstPhysicsBodyInReach() const;
	// Get the end point for the reach line
	FVector GetReachLineEnd() const;
	// Get the starting point of the reach line or the actor's origin
	FVector GetReachLineStart() const;
};
