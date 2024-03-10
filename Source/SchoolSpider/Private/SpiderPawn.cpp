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
	if( !m_attachPoint )
		delete m_attachPoint;

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
		FVector location;
		FVector direction;
		m_playerController->DeprojectMousePositionToWorld( location, direction );
		location = m_playerController->PlayerCameraManager.Get()->GetCameraLocation();

		float magnitude = abs( location.X / direction.X );

		dir = (location + direction * magnitude ) - playerPos;
		//dir.X = 0;
		dir.Normalize();
	}

	FHitResult hit;
	FCollisionQueryParams paramaters;
	paramaters.AddIgnoredActor( this );
	FCollisionResponseParams collisionResponse;

	//ActorLineTraceSingle( hit, playerPos + dir * 300, playerPos + dir * m_maxRopeLenght, ECollisionChannel::ECC_Visibility, paramaters );
	DrawDebugLine( GetWorld(), playerPos + dir, playerPos + dir * m_maxRopeLenght, FColor::Red, false, 100, 100 );

	//if( !ActorLineTraceSingle(hit, playerPos + FuckUE + dir, playerPos + dir * m_maxRopeLenght, ECollisionChannel::ECC_Visibility, paramaters, collisionResponse ) )
	if( !GetWorld()->LineTraceSingleByChannel( hit, playerPos + dir, playerPos + dir * m_maxRopeLenght, ECollisionChannel::ECC_Visibility, paramaters, FCollisionResponseParams() ) )
	{
		if( GEngine )
			GEngine->AddOnScreenDebugMessage( -1, 105.0f, FColor::Red, "Miss");
	}
	else
	{
			GEngine->AddOnScreenDebugMessage( -1, 105.0f, FColor::Emerald, TEXT("Hit : ") + hit.GetActor()->GetName());
		DrawDebugLine( GetWorld(), playerPos + dir, hit.Location, FColor::Emerald, false, 100, 200 );
		
		FActorSpawnParameters spawnParamaters;
		m_attachPoint = GetWorld()->SpawnActor<AcAttachPoint>( m_attach_BP, hit.Location, FRotator::ZeroRotator, spawnParamaters );
		auto constraint = m_attachPoint->m_physicsConstraint;
		constraint->SetConstrainedComponents( NULL, "", m_capsule, "");
		constraint->SetConstraintReferencePosition( EConstraintFrame::Frame1, FVector::Zero() );
		constraint->SetLinearXLimit( ELinearConstraintMotion::LCM_Free, hit.Distance );
	}

}

FVector ASpiderPawn::playerMovement( float _input, float _deltaTime )
{
	FVector change;
	FVector velocity = GetVelocity();

	if( m_swinging )
	{
		FVector dir = GetActorLocation() - m_attachPoint->GetActorLocation();
		FVector output{ dir.X,-dir.Z, dir.Y };
		output.Normalize();
		if( dir.Z > 0 && abs( dir.Y ) > abs( dir.Y + _input ) )
		{
			change = dir * m_acceleration * _input;
			if( GEngine )
				GEngine->AddOnScreenDebugMessage( -1, 105.0f, FColor::Red, "Swing" );
		}
	}
	else //if( m_grounded )
	{
		//if( velocity.Length() > m_maxSpeed && abs( m_maxSpeed ) < abs( m_maxSpeed + _input ) )
		//	return;
		if( GEngine )
			GEngine->AddOnScreenDebugMessage( -1, 105.0f, FColor::Red, "Walk");
		change = { 0, _input * m_acceleration, 0 };
	}
	m_primative->AddForce( change  );
	return change;
}
