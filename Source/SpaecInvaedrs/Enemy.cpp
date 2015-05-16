// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaecInvaedrs.h"
#include "Enemy.h"
#include "Laser.h"
#include "EnemyLaser.h"


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

    if (isShooting) {
        /* For who-knows-what reason, UE4 checks for collisions immediately upon
         * actor spawn, which will destroy us immediately as the laser hasn't been
         * initialized as an enemy laser yet; thus, we disable collisions, then
         * re-enable them after we set the isEnemyLaser property */
        SetActorEnableCollision(false);
        FVector location = GetRootComponent()->GetComponentLocation();
        AEnemyLaser *laser = GetWorld()->SpawnActor<AEnemyLaser>(location, FRotator(0, 90, 0));
        isShooting = false;
        SetActorEnableCollision(true);
    }
}

void AEnemy::OnBeginOverlap(AActor *otherActor) {
    if (otherActor->IsA(ALaser::StaticClass()) && !otherActor->IsA(AEnemyLaser::StaticClass())) {
        deathSound->Play();
        mesh->SetVisibility(false);
        bAutoDestroyWhenFinished = true;
        otherActor->Destroy();
    }
}

void AEnemy::shoot() {
    isShooting = true;
}