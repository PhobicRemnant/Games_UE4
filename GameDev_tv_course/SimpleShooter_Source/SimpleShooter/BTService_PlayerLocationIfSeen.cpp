// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"


void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

		
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	// Nullptr protect PlayerPawn ptr
	if (PlayerPawn == nullptr)
	{
		return;
	}

	// Nullptr protect Character ptr
	if(OwnerComp.GetAIOwner() == nullptr)
	{
		return;
	}

	
	// If the AI has LOS with Player
	if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
	{
		// Update the BKey
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn );
	
	}
	else
	{	
		// Clear BKey value
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	}


}	

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = "Player Location If Seen";
}
