// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaecInvaedrs.h"
#include "Ship.h"
#include "Laser.h"

float AShip::shootCooldown = 1;

// Sets default values
AShip::AShip(const FObjectInitializer &ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMesh"));
    shootSound = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("ShootSound"));
    deathSound = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("DeathSound"));

    SetRootComponent(mesh);
    shootSound->AttachTo(mesh);
    shootSound->bAutoActivate = false;
    deathSound->AttachTo(mesh);
    deathSound->bAutoActivate = false;

    speed = 100;

    OnActorBeginOverlap.AddDynamic(this, &AShip::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShip::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    shootTimer += DeltaTime;
    if (direction != 0.0) {
        FVector newLocation = GetRootComponent()->GetComponentLocation();
        newLocation.Y += DeltaTime * speed * direction;
        newLocation.Y = FMath::Min(FMath::Max(newLocation.Y, -500.0f), 500.0f);
        SetActorLocation(newLocation);
    }
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

    InputComponent->BindAxis("LRAxis", this, &AShip::Move);
    InputComponent->BindAction("Shoot", IE_Pressed, this, &AShip::Shoot);
}

void AShip::Move(float axisValue) {
    direction = axisValue;
}

void AShip::Shoot() {
    if (shootTimer >= shootCooldown) {
        FVector location = GetRootComponent()->GetComponentLocation();
        AActor *laser = GetWorld()->SpawnActor<ALaser>(location, FRotator(90, 0, 0));
        shootSound->Play();
        shootTimer = 0;
    }
}

void AShip::OnBeginOverlap(AActor *otherActor) {
    if (otherActor->IsA(ALaser::StaticClass()) && ((ALaser*)otherActor)->isEnemyLaser) {
        deathSound->Play();
        mesh->SetVisibility(false);
        bAutoDestroyWhenFinished = true;
        otherActor->Destroy();
    }
}