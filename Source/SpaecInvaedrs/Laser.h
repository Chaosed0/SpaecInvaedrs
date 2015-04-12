// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Laser.generated.h"

UCLASS()
class SPAECINVAEDRS_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaser(const FObjectInitializer &ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    UStaticMeshComponent *mesh;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
    class UBoxComponent *collision;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float speed;
};
