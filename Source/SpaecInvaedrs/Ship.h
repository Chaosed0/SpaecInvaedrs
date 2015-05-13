// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Ship.generated.h"

UCLASS()
class SPAECINVAEDRS_API AShip : public APawn
{
    GENERATED_BODY()

    bool isShooting;
    float direction;
    float shootTimer;

public:
	// Sets default values for this pawn's properties
	AShip(const FObjectInitializer &ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    void Move(float axisValue);
    void StartShoot();
    void StopShoot();

    UFUNCTION()
    void OnBeginOverlap(AActor *otherActor);

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    class UStaticMeshComponent *mesh;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    class UAudioComponent *shootSound;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    class UAudioComponent *deathSound;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    class UBoxComponent *collision;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float speed;

    static float shootCooldown;
};
