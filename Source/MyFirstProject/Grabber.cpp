#include "Grabber.h"
#include "Engine/World.h"

UGrabber::UGrabber( ) {
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay( ) {
	Super::BeginPlay( );
	Input = GetOwner( )->FindComponentByClass<UInputComponent>( );
	if ( Input == nullptr ) {
		UE_LOG( LogTemp, Error, TEXT( "No UInputComponent found in %s!" ), *GetOwner( )->GetName( ) );
	} else {
		Input->BindAction( "Grab", IE_Pressed, this, &UGrabber::Grab );
		Input->BindAction( "Grab", IE_Released, this, &UGrabber::Drop );
	}
	PhysicsHandle = GetOwner( )->FindComponentByClass<UPhysicsHandleComponent>( );
	if ( PhysicsHandle == nullptr )
		UE_LOG( LogTemp, Error, TEXT( "No UPhysicsHandleComponent found in %s!" ), *GetOwner( )->GetName( ) );
}

void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) {
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if ( PhysicsHandle && PhysicsHandle->GrabbedComponent )
		PhysicsHandle->SetTargetLocation( GetLineTrace( ).v2 );
}

void UGrabber::Grab( ) {
	FHitResult hit = GetFirstPhysicsBodyInReach( );
	UPrimitiveComponent* component = hit.GetComponent( );
	AActor* actor = hit.GetActor( );
	if ( PhysicsHandle && actor )
		PhysicsHandle->GrabComponent( component, NAME_None, component->GetOwner( )->GetActorLocation( ), true );
}

void UGrabber::Drop( ) {
	if ( PhysicsHandle )
		PhysicsHandle->ReleaseComponent( );
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach( ) {
	FTwoVectors LineTrace = GetLineTrace( );
	FCollisionQueryParams traceParameters( FName( TEXT( "" ) ), false, GetOwner( ) );
	FHitResult hit;
	GetWorld( )->LineTraceSingleByObjectType( OUT hit, LineTrace.v1, LineTrace.v2, FCollisionObjectQueryParams( ECollisionChannel::ECC_PhysicsBody ), traceParameters );
	return hit;
}

FTwoVectors UGrabber::GetLineTrace( ) {
	FVector PlayerViewPointPosition;
	FRotator PlayerViewPointRotation;
	GetWorld( )->GetFirstPlayerController( )->GetPlayerViewPoint( OUT PlayerViewPointPosition, OUT PlayerViewPointRotation );
	return FTwoVectors( PlayerViewPointPosition, PlayerViewPointPosition + ( PlayerViewPointRotation.Vector( ) * Reach ) );
}