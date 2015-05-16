// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaecInvaedrs.h"
#include "EnemyLaser.h"

AEnemyLaser::AEnemyLaser(const FObjectInitializer &ObjectInitializer)
    : ALaser(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Couch.SM_Couch'"));
	if (MeshObj.Succeeded()) {
		mesh->SetStaticMesh(MeshObj.Object);
	} else {
		UE_LOG(LogTemp, Log, TEXT("Couldn't load static bench mesh, defaulting to nothing"));
	}

    mesh->SetRelativeScale3D(FVector(0.25, 0.25, 0.25));
    collision->SetWorldScale3D(FVector(1, 1, 1));

    direction = FVector(-1, 0, 0);
}
