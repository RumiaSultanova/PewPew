// Pew-Pew Game. All Rights Reserved.

#include "Player/PPBaseCharacter.h"
#include "Components/PPCharacterMovementComponent.h"
#include "Components/PPHealthComponent.h"
#include "Components/PPWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"

 APPBaseCharacter::APPBaseCharacter(const FObjectInitializer& ObjInit)
:Super(ObjInit.SetDefaultSubobjectClass<UPPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
 	
 	HealthComponent = CreateDefaultSubobject<UPPHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UPPWeaponComponent>("WeaponComponent");
}

void APPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

 	check(HealthComponent);
 	check(GetCharacterMovement());
 	check(GetMesh());

 	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
 	HealthComponent->OnDeath.AddUObject(this, &APPBaseCharacter::OnDeath);
 	HealthComponent->OnHealthChanged.AddUObject(this, &APPBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &APPBaseCharacter::OnGroundLanded);
}

void APPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APPBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
 	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
 	if (!MaterialInst){ return; }

 	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}

bool APPBaseCharacter::IsRunning() const
{
	return false;
}

float APPBaseCharacter::GetMovementDirection() const
{
 	if (GetVelocity().IsZero()) { return 0.0f; }
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
 	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
 	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
 	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void APPBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
}

void APPBaseCharacter::OnDeath()
{
	// PlayAnimMontage(DeathAnimMontage);

 	GetCharacterMovement()->DisableMovement();

 	SetLifeSpan(LifeSpanOnDeath);
 	
 	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
 	WeaponComponent->StopFire();

 	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
 	GetMesh()->SetSimulatePhysics(true);
}

void APPBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;

 	if (FallVelocityZ < LandedDamageVelocity.X) { return; }

 	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
 	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}