// Pew-Pew Game. All Rights Reserved.

#include "Components/PPHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "PewPewGameModeBase.h"

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
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UPPHealthComponent::OnTakeAnyDamage);
	}
}

void UPPHealthComponent::OnTakeAnyDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
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
