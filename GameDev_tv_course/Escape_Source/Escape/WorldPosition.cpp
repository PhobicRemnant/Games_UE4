// Dips&Chips


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	FString ObjName = GetOwner()->GetName();
	FString* PtrObjName = &ObjName;
	FVector ObjLoc = GetOwner()->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Object's name: %s"), **PtrObjName);
	UE_LOG(LogTemp, Log, TEXT("Object's coordinates: X:%f,Y:%f,Z:%f"), ObjLoc.X, ObjLoc.Y, ObjLoc.Z);

}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

