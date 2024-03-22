// Pew-Pew Game. All Rights Reserved.

#include "Components/PPHealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "PewPewGameModeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Perception/AISense_Damage.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UPPHealthComponent::UPPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPPHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	if (AActor* ComponentOwner = GetOwner())
	{
		ComponentOwner->OnTakePointDamage.AddDynamic(this, &UPPHealthComponent::OnTakePointDamage);
		ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &UPPHealthComponent::OnTakeRadialDamage);
	}
}

void UPPHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
	UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
	ApplyDamage(FinalDamage, InstigatedBy);
	UE_LOG(LogHealthComponent, Log, TEXT("%s take %f damage to %s"), *DamagedActor->GetFName().ToString(), FinalDamage, *BoneName.ToString())
}

void UPPHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin,
	const FHitResult& HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	ApplyDamage(Damage, InstigatedBy);
}

void UPPHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);

	if (iSHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void UPPHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;

	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool UPPHealthComponent::TryToAddHealth(int32 HealthAmount)
{
	if (IsDead() || iSHealthFull()){ return false; }

	SetHealth(Health + HealthAmount);
	return true;
}

bool UPPHealthComponent::iSHealthFull() const
{
	return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UPPHealthComponent::PlayCameraShake()
{
	if (IsDead()) { return; }

	const auto Player = Cast<APawn>(GetOwner());
	if (!Player) { return; }

	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) { return; }

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void UPPHealthComponent::Killed(AController* KillerController)
{
	if (!GetWorld()) { return; }
	
	const auto GameMode = Cast<APewPewGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) { return; }

	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);
}

void UPPHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()){ return; }

	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UPPHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}

	PlayCameraShake();
	ReportDamageEvent(Damage, InstigatedBy);
}

float UPPHealthComponent::GetPointDamageModifier(AActor* DamagedActor, const FName& BoneName)
{
	const auto Character = Cast<ACharacter>(DamagedActor);
	if (!Character ||
		!Character->GetMesh() ||
		!Character->GetMesh()->GetBodyInstance(BoneName)) { return 1.0f; }

	const auto PhysicalMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
	if (!DamageModifiers.Contains(PhysicalMaterial)) { return  1.0f; }

	return DamageModifiers[PhysicalMaterial];
}

void UPPHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if (!InstigatedBy || !InstigatedBy->GetPawn() ||!GetOwner()) { return; }
	
	UAISense_Damage::ReportDamageEvent(GetWorld(), GetOwner(), InstigatedBy->GetPawn(),
		Damage, InstigatedBy->GetPawn()->GetActorLocation(), GetOwner()->GetActorLocation());
}
