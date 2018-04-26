#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class MYFIRSTPROJECT_API UGrabber : public UActorComponent {
	GENERATED_BODY( )
public:
	UGrabber( );
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
private:
	UPROPERTY( EditAnywhere ) float Reach;
	UInputComponent* Input;
	UPhysicsHandleComponent* PhysicsHandle;
	void Grab( );
	void Drop( );
	FHitResult GetFirstPhysicsBodyInReach( );
	FTwoVectors GetLineTrace( );
protected:
	virtual void BeginPlay( ) override;
};
