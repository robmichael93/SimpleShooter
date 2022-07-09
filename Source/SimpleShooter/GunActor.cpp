// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"
#include "ShooterCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

#define OUT

// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGunActor::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn != nullptr)
	{
		AController* Controller = OwnerPawn->GetController();
		if (Controller != nullptr)
		{
			FVector ControllerLocation;
			FRotator ControllerRotation;
			Controller->GetPlayerViewPoint(OUT ControllerLocation, OUT ControllerRotation);

			FHitResult Hit;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			Params.AddIgnoredActor(GetOwner());

			FVector End = ControllerLocation + ControllerRotation.Vector() * MaxRange;
			if (GetWorld()->LineTraceSingleByChannel(Hit, ControllerLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params))
			{
				FVector ShotDirection = -ControllerRotation.Vector();
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.Location, ShotDirection.Rotation());
				AActor* DamagedActor = Hit.GetActor();
				if (DamagedActor != nullptr)
				{
					FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
					DamagedActor->TakeDamage(Damage, DamageEvent, Controller, this);
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

