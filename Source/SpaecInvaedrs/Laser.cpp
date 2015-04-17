// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaecInvaedrs.h"
#include "Laser.h"


// Sets default values
ALaser::ALaser(const FObjectInitializer &ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh"));
    collision = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxCollider"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Props/SM_Lamp_Wall.SM_Lamp_Wall"));
	if (MeshObj.Succeeded()) {
		mesh->SetStaticMesh(MeshObj.Object);
	} else {
		UE_LOG(LogTemp, Log, TEXT("Couldn't load static lamp mesh, defaulting to nothing"));
	}

    SetRootComponent(mesh);
    collision->AttachTo(mesh);
    
    collision->InitBoxExtent(FVector(10, 20, 20));

    speed = 500;
    isEnemyLaser = false;
}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALaser::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    float direction = 1.0f;

    if (isEnemyLaser) {
        direction = -1.0f;
    }

    AddActorWorldOffset(FVector(DeltaTime * speed * direction, 0, 0));

    FVector location = GetRootComponent()->GetComponentLocation();
    if (FMath::Abs(location.X) > 500) {
        Destroy();
    }
}
