// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpiderPawn.generated.h"

UCLASS()
class SCHOOLSPIDER_API ASpiderPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere )
	float maxRopeLenght = 2000.0f;

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
private:
	void shootRope();
};
