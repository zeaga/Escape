// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FDoorEvent );

UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class MYFIRSTPROJECT_API UOpenDoor : public UActorComponent {
	GENERATED_BODY( )
public:
	UOpenDoor( );
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	UPROPERTY( BlueprintAssignable ) FDoorEvent OnOpen;
	UPROPERTY( BlueprintAssignable ) FDoorEvent OnClose;
private:
	float GetMassOfActors( );
	UPROPERTY( EditAnywhere ) float OpenAngle;
	UPROPERTY( EditAnywhere ) float KeyMass;
	UPROPERTY( EditAnywhere ) ATriggerVolume* PressurePlate;
protected:
	virtual void BeginPlay( ) override;
};
