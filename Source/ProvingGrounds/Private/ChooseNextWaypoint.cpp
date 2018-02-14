// Fill out your copyright notice in the Description page of Project Settings.

//#include "ChooseNextWaypoint.h"
#include "../Public/ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Public/PatrollingGuard.h" //TODO remove coupling
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//Get the patrol points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	//Set next waypoint
	

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName); 
	
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle the index

	auto NextIndex = (Index+1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	//TODO protect against empty patrol rotes
	
	UE_LOG(LogTemp,Warning,TEXT("Waypoint index: %i"), Index)
	return EBTNodeResult::Succeeded;
}
