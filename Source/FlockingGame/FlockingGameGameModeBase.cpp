// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlockingGameGameModeBase.h"

AFlockingGameGameModeBase::AFlockingGameGameModeBase() {
    AgentMesh = CreateDefaultSubobject<UStaticMeshComponent>("AgentMesh");
    PrimaryActorTick.bCanEverTick = true;
}  

void AFlockingGameGameModeBase::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("GAMEMODE BEGINPLAY()"));
    Manager = NewObject<UFlockingManager>();
    Manager->Init( GetWorld(), AgentMesh );
}

void AFlockingGameGameModeBase::Tick( float DeltaTime ) {
    Super::Tick( DeltaTime );
    Manager->Flock();
};