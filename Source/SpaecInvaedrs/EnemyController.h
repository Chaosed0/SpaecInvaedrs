// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemyController.generated.h"

UCLASS()
class SPAECINVAEDRS_API AEnemyController : public AActor
{
    GENERATED_BODY()

    float moveTimer;
    float direction;
    bool flippedDirection;
    bool moveDown;

    TSharedPtr<TActorIterator<class AEnemy>> EnemyIter;
	
public:	
	// Sets default values for this actor's properties
	AEnemyController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float moveTime;
};
