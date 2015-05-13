// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemyController.generated.h"

UCLASS()
class SPAECINVAEDRS_API AEnemyController : public AActor
{
    GENERATED_BODY()

    float moveTimer;
    float shootTimer;
    float direction;
    float shootTime;
    float moveTime;
    float initialEnemyCount;
    bool flippedDirection;
    bool moveDown;
    int enemyCount;

    TSharedPtr<TActorIterator<class AEnemy>> EnemyMoveIter;
	
public:	
	// Sets default values for this actor's properties
	AEnemyController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION()
    void OnEnemyDeath();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float initialMoveTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float minimumMoveTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float shootTimeMin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float shootTimeMax;
};
