// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonExper.h"
#include "Ammo.h"

// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();
	
	if (ProjectileCollision != NULL &&
		Behavior != AmmoBehavior::Hitscan)
	{
		ProjectileCollision->OnComponentHit.AddDynamic(this, &AAmmo::OnHit);
	}
}

// Called every frame
void AAmmo::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AAmmo::LaunchProjectile(float dmgModifier, float bulletRange = 0.f)
{
	switch (Behavior)
	{
	case AmmoBehavior::Hitscan:
		HitScan();
		break;
	case AmmoBehavior::Projectile:
		// Enable projectile stuff (rockets fx etc)
		break;
	default:
		// Do some logging here for unsupported types
		break;
	}
}

void AAmmo::HitScan()
{
	UWorld *world = GetWorld();
	FHitResult Hit;//the thing that is an output of the statement
	FName HitScanTrace = FName("HitScanTest");

	//world->DebugDrawTraceTag = HitScanTrace;
	FCollisionQueryParams Line(HitScanTrace, true);
	FTransform aTransform = this->GetActorTransform();

	FVector forward = aTransform.GetRotation().GetForwardVector();
	forward.Normalize();
	forward *= 20000.f;

	FVector startPos = aTransform.GetLocation();

	// Fix forward to be the center of the camera at weapon range.

	forward += startPos;

	UE_LOG(LogTemp, Log, TEXT("HitScanTest!"));
	//world->LineTraceSingleByChannel
	//world->LineTraceSingleByObjectType(Hit, startPos, forward,EObjectTypeQuery::ObjectTypeQuery1 ,Line);

	if (world->LineTraceSingleByChannel(Hit, startPos, forward, ECollisionChannel::ECC_GameTraceChannel1, Line))
	{
		UE_LOG(LogTemp, Log, TEXT("Hit Something TRUE"));
	}

	if (Hit.Actor != NULL)
	{
		UE_LOG(LogTemp, Log, TEXT("Hit Something %s %s"), *Hit.Actor->GetName(), *Hit.ImpactPoint.ToString());

		//OtherComp->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);

		UPrimitiveComponent* DamagedComponent = Hit.GetComponent();

		//FVector test = FVector(0,300000, 0);
		DamagedComponent->AddImpulseAtLocation(forward * 100, Hit.ImpactPoint);
		FVector rotation = FVector(0.0f, 0.0f, 0.0f);

		// How to spawn a locator in the world however this wont follow the target.
		//world->SpawnActor<ImpactFx>(ImpactFx, Hit.ImpactPoint, rotation.Rotation() , NULL);
		//UGameplayStatics::SpawnEmitterAtLocation(world,ImpactFx, Hit.ImpactPoint, rotation.Rotation(), true);

		UParticleSystemComponent* particleSystemComponent = UGameplayStatics::SpawnEmitterAttached(ImpactFx, DamagedComponent, "", Hit.ImpactPoint, rotation.Rotation(), EAttachLocation::KeepWorldPosition);

		FVector scale = FVector(1.f / DamagedComponent->GetComponentScale().X,
			1.f / DamagedComponent->GetComponentScale().Y,
			1.f / DamagedComponent->GetComponentScale().Z);
		particleSystemComponent->SetRelativeScale3D(scale);


		// TODO: Apply dmg etc...
	}

	// All processing is done, destroy()
	this->Destroy();
}

void AAmmo::OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}
