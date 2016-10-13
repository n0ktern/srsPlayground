// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Ammo.h"
#include "Weapon.generated.h"

UCLASS()
class FIRSTPERSONEXPER_API AWeapon :  public AActor // I need to inherit from this in order for the current pattern to work...
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = Collision)
		USphereComponent *ProxSphere;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* WeaponMeshAsset;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "WeaponActions")
		void Fire();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponInfo")
		TSubclassOf<AAmmo> AmmoClass;

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponInfo")
	uint8 BaseDamageMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponInfo")
	float FireRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponInfo")
	bool InfiniteAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponInfo")
	uint8 MaxAmmo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponInfo")
	uint8 ClipSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeaponInfo")
	uint8 AmmoCount;


};
