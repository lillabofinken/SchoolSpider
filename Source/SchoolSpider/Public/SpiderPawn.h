// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h" 
#include "cAttachPoint.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h" 
#include "Components/CapsuleComponent.h" 
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpiderPawn.generated.h"

UCLASS()
class SCHOOLSPIDER_API ASpiderPawn : public APawn
{
	GENERATED_BODY()
public:
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
		float m_maxRopeLenght = 2000.0f;

	UPROPERTY( BlueprintReadWrite )
		bool m_grounded = true;

	UPROPERTY( BlueprintReadWrite )
		bool m_swinging = false;

	UPROPERTY( BlueprintReadWrite )
		UCapsuleComponent* m_capsule;

	UPROPERTY( EditDefaultsOnly )
		TSubclassOf<AcAttachPoint> m_attach_BP;

private:

	AcAttachPoint* m_attachPoint = nullptr;

public:
	// Sets default values for this pawn's properties
	ASpiderPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UFUNCTION( BlueprintCallable, Category = "PlayerNodes" )
	void shootRope(FVector _mousePos, bool _optimalDirection );
};
