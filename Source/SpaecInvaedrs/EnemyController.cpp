// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaecInvaedrs.h"
#include "EnemyController.h"
#include "EngineUtils.h"
#include "Enemy.h"

// Sets default values
AEnemyController::AEnemyController() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    speed = 50.0f;
    direction = 1.0f;
    flippedDirection = false;
    moveDown = false;
    EnemyMoveIter = NULL;

    shootTimeMin = 0.5;
    shootTimeMax = 1.25;

    initialMoveTime = 1;
    minimumMoveTime = 0.05;

    shootTimer = 0;
    enemyCount = 0;
    moveTime = initialMoveTime;
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay() {
	Super::BeginPlay();

    /* Count how many enemies exist, and add a callback to tell us when they're dead */
    for (auto EnemyIter = TActorIterator<AEnemy>(GetWorld()); EnemyIter; ++EnemyIter) {
        initialEnemyCount++;
        EnemyIter->OnDestroyed.AddDynamic(this, &AEnemyController::OnEnemyDeath);
    }
    enemyCount = initialEnemyCount;

    /* Figure out when we should move & shoot */
    shootTime = FMath::FRandRange(shootTimeMin, shootTimeMax);
    moveTime = initialMoveTime;
}

// Called when any enemy dies
void AEnemyController::OnEnemyDeath() {
    --enemyCount;
    moveTime = minimumMoveTime + (initialMoveTime - minimumMoveTime) * enemyCount / initialEnemyCount;

    /* Check if any enemies remain */
    if (enemyCount <= 0) {
        OnAllEnemiesDead();
    }
}

// Called every frame
void AEnemyController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    moveTimer += DeltaTime;
    shootTimer += DeltaTime;

    if (shootTimer >= shootTime && enemyCount > 0) {
        shootTimer -= shootTime;
        shootTime = FMath::FRandRange(shootTimeMin, shootTimeMax);

        // Fire off a random shot
        int shooterIndex = FMath::RandHelper(enemyCount);
        auto shooter = TActorIterator<AEnemy>(GetWorld());
        for (int i = 0; i < shooterIndex; i++) {
            ++shooter;
        }

        shooter->shoot();
    }

    if (moveTimer >= moveTime && !EnemyMoveIter.IsValid()) {
        /* Begin another move */
        moveTimer -= moveTime;
        EnemyMoveIter = TSharedPtr<TActorIterator<AEnemy>>(new TActorIterator<AEnemy>(GetWorld()));
    }

    if (EnemyMoveIter.IsValid() && (*EnemyMoveIter)) {
        /* If we hit the border last movement, move down instead of left/right */
        FVector movement;
        if (!moveDown) {
            movement = FVector(0, direction * speed, 0);
        } else {
            movement = FVector(-speed, 0, 0);
        }

        (*EnemyMoveIter)->AddActorWorldOffset(movement);

        /* If we hit the border with one of our ships this movement, change direction
         * and move down in the next movement */
        if (!moveDown && FMath::Abs((*EnemyMoveIter)->GetActorLocation().Y) >= 500) {
            flippedDirection = true;
        }

        ++(*EnemyMoveIter);
        
        /* Have we run out of enemies to move? */
        if (!(*EnemyMoveIter)) {
            /* Null out the enemy iterator pointer so we know we ran out*/
            EnemyMoveIter = NULL;
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

