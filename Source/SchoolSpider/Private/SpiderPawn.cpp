// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderPawn.h"

// Sets default values
ASpiderPawn::ASpiderPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpiderPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpiderPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASpiderPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpiderPawn::shootRope( FVector _mousePos, bool _optimalDirection )
{
	FVector velocity = AActor::GetVelocity();
	FVector dir;
	FVector playerPos = AActor::GetActorLocation();

	if( _optimalDirection )
	{
		dir = FVector( velocity.X, -velocity.Z, velocity.Y );
		if( dir.Z < 0 )
			dir *= -1;
		dir.Normalize();
	}
	else
	{
		dir = _mousePos - playerPos;
		dir.Normalize();
	}

	FHitResult hit;
	FCollisionQueryParams paramaters;
	//paramaters.AddIgnoredActor( AActor::GetUniqueID() );
	paramaters.bTraceComplex = true;

	//ActorLineTraceSingle( hit, playerPos + dir * 300, playerPos + dir * m_maxRopeLenght, ECollisionChannel::ECC_Visibility, paramaters );
	DrawDebugLine( GetWorld(), playerPos + dir, playerPos + dir * m_maxRopeLenght, FColor::Emerald, false, 100, 10 );

	if( !ActorLineTraceSingle(hit, playerPos + dir, playerPos + dir * m_maxRopeLenght, ECollisionChannel::ECC_Visibility, paramaters) )
	{
		if( GEngine )
			GEngine->AddOnScreenDebugMessage( -1, 105.0f, FColor::Yellow, "Miss");
	}

	FActorSpawnParameters spawnParamaters;
	m_attachPoint = GetWorld()->SpawnActor<AcAttachPoint>( m_attach_BP, hit.Location, FRotator::ZeroRotator, spawnParamaters );
	auto constraint = m_attachPoint->m_physicsConstraint;
	constraint->SetConstrainedComponents( NULL, "", m_capsule, "");
	constraint->SetConstraintReferencePosition( EConstraintFrame::Frame1, FVector::Zero() );
	constraint->SetLinearXLimit( ELinearConstraintMotion::LCM_Free, hit.Distance );
}