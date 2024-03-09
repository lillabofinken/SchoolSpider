// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h" 
#include "cAttachPoint.generated.h"

UCLASS()
class SCHOOLSPIDER_API AcAttachPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AcAttachPoint();
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
		UPhysicsConstraintComponent* m_physicsConstraint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
