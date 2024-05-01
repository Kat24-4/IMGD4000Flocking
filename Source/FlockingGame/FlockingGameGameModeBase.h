// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// #include "CoreMinimal.h"
// #include "GameFramework/GameModeBase.h"
// #include "FlockingManager.h"
// #include "FlockingGameGameModeBase.generated.h"

// UCLASS()
// class FLOCKINGGAME_API AFlockingGameGameModeBase : public AGameModeBase
// {
// 	GENERATED_BODY()
// 	AFlockingGameGameModeBase();

// 	UPROPERTY(EditAnywhere)
// 	class UStaticMeshComponent * AgentMesh;

// 	UPROPERTY() UFlockingManager *Manager;

// 	virtual void BeginPlay() override;
// 	virtual void Tick(float DeltaTime) override;
// };

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlockingManager.h"
#include "FlockingGameGameModeBase.generated.h"

UCLASS()
class FLOCKINGGAME_API AFlockingGameGameModeBase : public AGameModeBase
{
  GENERATED_BODY()
  AFlockingGameGameModeBase();

  public:
    UPROPERTY(EditAnywhere, meta=(ClampMin="-10.0", ClampMax="10.0"))
    float Speed;

  private:
    UPROPERTY(EditAnywhere)
    class UStaticMeshComponent * AgentMesh;

    UPROPERTY() UFlockingManager *Manager;

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
};