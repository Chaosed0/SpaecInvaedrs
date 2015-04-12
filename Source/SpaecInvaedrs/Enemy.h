// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class SPAECINVAEDRS_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
    AEnemy(const FObjectInitializer &ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION()
    void OnBeginOverlap(AActor *otherActor);

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    class UStaticMeshComponent *mesh;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    class UBoxComponent *collision;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    class UAudioComponent *deathSound;
};
