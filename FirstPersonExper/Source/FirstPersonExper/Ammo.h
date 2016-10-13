// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Ammo.generated.h"

UENUM(BlueprintType)
enum class AmmoBehavior : uint8
{
	Hitscan,
	Projectile
};

UENUM(BlueprintType)
enum class AmmoType : uint8
{
	Bullet,
	Grenade
};


UCLASS()
class FIRSTPERSONEXPER_API AAmmo : public AActor
{
	GENERATED_BODY()

private:

	void HitScan();
	void OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Sets default values for this actor's properties
	AAmmo();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	UFUNCTION(BlueprintCallable, Category = "AmmoActions")
		void LaunchProjectile(float,float bulletRange = 0.f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AmmoInfo")
		AmmoType AmmoT;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AmmoInfo")
		AmmoBehavior Behavior;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AmmoInfo")
		uint8 BaseDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AmmoInfo")
		float BaseImpactForce;

	// this can be made such that when we need a particle we can get it from the "default" unless there is an override from the hit component's parent actor
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AmmoFx")
		USphereComponent *ProjectileCollision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AmmoFx")
	UParticleSystem *ImpactFx;

};