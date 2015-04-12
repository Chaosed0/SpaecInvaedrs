// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaecInvaedrs.h"
#include "Enemy.h"
#include "Laser.h"


// Sets default values
AEnemy::AEnemy(const FObjectInitializer &ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh"));
    collision = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxCollider"));
    deathSound = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathSound"));

    SetRootComponent(mesh);
    collision->AttachTo(mesh);
    deathSound->AttachTo(mesh);

    collision->bGenerateOverlapEvents = true;
    deathSound->bAutoActivate = false;

    OnActorBeginOverlap.AddDynamic(this, &AEnemy::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AEnemy::OnBeginOverlap(AActor *otherActor) {
    if (otherActor->IsA(ALaser::StaticClass())) {
        deathSound->Play();
        mesh->SetVisibility(false);
        bAutoDestroyWhenFinished = true;
        otherActor->Destroy();
    }
}