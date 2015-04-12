// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaecInvaedrs.h"
#include "EnemyController.h"
#include "EngineUtils.h"
#include "Enemy.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    speed = 50.0f;
    direction = 1.0f;
    flippedDirection = false;
    moveDown = false;
    moveTime = 1;
    EnemyIter = NULL;
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    moveTimer += DeltaTime;

    if (moveTimer >= moveTime && !EnemyIter.IsValid()) {
        moveTimer -= moveTime;
        EnemyIter = TSharedPtr<TActorIterator<AEnemy>>(new TActorIterator<AEnemy>(GetWorld()));
        UE_LOG(LogTemp, Log, TEXT("Moving Enemies"));
    }

    if (EnemyIter.IsValid() && (*EnemyIter)) {
        /* If we hit the border last movement, move down instead of left/right */
        FVector movement;
        if (!moveDown) {
            movement = FVector(0, direction * speed, 0);
        } else {
            movement = FVector(-speed, 0, 0);
        }

        (*EnemyIter)->AddActorWorldOffset(movement);

        /* If we hit the border with one of our ships this movement, change direction
         * and move down in the next movement */
        if (!moveDown && FMath::Abs((*EnemyIter)->GetActorLocation().Y) >= 500) {
            flippedDirection = true;
        }

        ++(*EnemyIter);
        
        /* Have we run out of enemies to move? */
        if (!(*EnemyIter)) {
            /* Null out the enemy iterator pointer so we know we ran out*/
            EnemyIter = NULL;
            if (flippedDirection) {
                /* Flip the direction */
                direction = -direction;
                flippedDirection = false;
                /* If we've flipped direction, we should move down first */
                moveDown = true;
            } else {
                moveDown = false;
            }
        }
    }
}

