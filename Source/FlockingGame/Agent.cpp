#include "Agent.h"
#include "FlockingGameGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AAgent::AAgent(){
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AgentMesh"));	
	RootComponent = Mesh;
	Velocity = FVector(0.f);
}

void AAgent::BeginPlay(){
	Super::BeginPlay();
}

void AAgent::Init( UStaticMeshComponent *mesh, int id ) {
	UE_LOG(LogTemp, Warning, TEXT("Agent initialized.") );
	Mesh->SetStaticMesh( mesh->GetStaticMesh() );
}

// void AAgent::Tick(float DeltaTime){
// 	Super::Tick(DeltaTime);

// 	FVector loc = GetActorLocation();
// 	SetActorLocation( loc + Velocity );
// }

void AAgent::Tick(float DeltaTime){
  Super::Tick(DeltaTime);
  AFlockingGameGameModeBase *gmb = Cast<AFlockingGameGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
  Velocity.Z = gmb->Speed;

  FVector loc = GetActorLocation();
  SetActorLocation( loc + Velocity );
}