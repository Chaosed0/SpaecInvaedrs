// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaecInvaedrs.h"
#include "ShipMovementComponent.h"



UShipMovementComponent::UShipMovementComponent(const FObjectInitializer &ObjectInitializer)
    : UMovementComponent(ObjectInitializer)
{
    bAutoRegisterUpdatedComponent = true;
    bConstrainToPlane = true;
    bSnapToPlaneAtStart = true;

    SetPlaneConstraintNormal(FVector(0,0,1));
}

