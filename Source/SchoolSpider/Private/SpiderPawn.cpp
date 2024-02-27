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

void ASpiderPawn::shootRope()
{
	
}