// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockingManager.h"

#define AGENT_COUNT 100

void UFlockingManager::Init( UWorld *world, UStaticMeshComponent *mesh ) {
    UE_LOG(LogTemp, Warning, TEXT("Manager initialized"));
    
    World = world;
    float incr = (PI * 2.f) / AGENT_COUNT;
    for( int i = 0; i < AGENT_COUNT; i++ ) {
        if( World != nullptr ) {
            FRotator rotation = FRotator();

            FVector location = FVector();
            location.X = FMath::Sin( incr * i ) * 150.f;
            location.Z = FMath::Cos( incr * i ) * 150.f;

            AAgent * agent = World->SpawnActor<AAgent>( location, rotation );
            agent->Init( mesh, i );
            Agents.Add( agent );
        }
    }

    initialized = true;
}

void UFlockingManager::Flock() {
	FVector v1;
	FVector v2;
	FVector v3; 
	//FVector v4;

	for(AAgent * agent: Agents) {
		v1 = rule1(agent);
		v2 = rule2(agent);
		v3 = rule3(agent); 
		//v4 = tend_to_place(agent); 

		agent -> Velocity = agent -> Velocity + v1 + v2 + v3; //+ v4; 
		//FVector loc = agent -> GetActorLocation(); 
		limit_vel(agent); 
		//agent -> SetActorLocation(loc + agent -> Velocity); 
	}
}

FVector UFlockingManager::rule1(AAgent * a) {
	FVector pcj = FVector(0.f);

	for(AAgent * agent: Agents) {
		if(agent != a) {
			pcj = pcj + agent -> GetActorLocation(); 
		}
	}

	pcj = pcj / (AGENT_COUNT - 1);

	return (pcj - a -> GetActorLocation()) / 100; 
}

FVector UFlockingManager::rule2(AAgent * a) {
	FVector c = FVector(0.f);

	for(AAgent * agent: Agents) {
		if(agent != a) {
			if(abs(FVector::Dist(agent -> GetActorLocation(), a -> GetActorLocation())) < 100) {
				c = c - (agent -> GetActorLocation() - a -> GetActorLocation());
			}
		}
	}

	return c; 
}

FVector UFlockingManager::rule3(AAgent * a) {
	FVector pvj; 

	for(AAgent * agent: Agents) {
		if(agent != a) {
			pvj = pvj + agent -> Velocity; 
		}
	}

	pvj = pvj / (AGENT_COUNT - 1); 

	return (pvj - a -> Velocity) / 8; 
}

FVector UFlockingManager::bound_position(AAgent * a) {
	float Xmin = -50000.f; 
	float Xmax = 50000.f; 
	float Ymin = -50000.f; 
	float Ymax = 50000.f;
	float Zmin = -10000.f;
	float Zmax = 80000000.f; 
	FVector v; 

	FVector pos = a -> GetActorLocation(); 
	if(pos.X < Xmin) {
		v.X = 10.f;
	} else if (pos.X > Xmax) {
		v.X = -50.f; 
	}

	if(pos.Y < Ymin) {
		v.Y = 10.f;
	} else if (pos.Y > Ymax) {
		v.Y = -10.f; 
	}

	if(pos.Z < Zmin) {
		v.Z = 10.f;
	} else if (pos.Z > Zmax) {
		v.Z = -10.f; 
	}

	return v;
}

FVector UFlockingManager::tend_to_place(AAgent * a) {
	FVector place = FVector(0, 0, 0); 
	FVector pos = a -> GetActorLocation(); 

	return (place - pos) / 10; 
}

void UFlockingManager::limit_vel(AAgent * a) {
	float vlim = 50;
	FVector v = a -> Velocity; 
	
	if(abs((int)(v.Size())) > vlim) {
		a -> Velocity = (v / abs((int32)(v.Size()))) * vlim; 
	}
}