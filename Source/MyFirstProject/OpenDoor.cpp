#include "OpenDoor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

UOpenDoor::UOpenDoor( ) {
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay( ) {
	Super::BeginPlay( );
}

void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) {
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if ( GetMassOfActors( ) >= KeyMass ) {
		OnOpen.Broadcast( );
	} else {
		OnClose.Broadcast( );
	}
}

float UOpenDoor::GetMassOfActors( ) {
	if ( !PressurePlate )
		return 0.f;
	float totalMass = 0.f;
	TArray<AActor*> actors;
	PressurePlate->GetOverlappingActors( OUT actors );
	for ( const auto* actor : actors ) {
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>( )->GetMass( );
	}
	return totalMass;
}