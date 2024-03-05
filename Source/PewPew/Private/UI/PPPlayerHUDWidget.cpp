// Pew-Pew Game. All Rights Reserved.

#include "UI/PPPlayerHUDWidget.h"
#include "Components/PPHealthComponent.h"
#include "Components/PPWeaponComponent.h"
#include "PPUtils.h"
#include "Components/ProgressBar.h"
#include "Player/PPPlayerState.h"

 void UPPPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
	
	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UPPPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
}

void UPPPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta <0.0f)
	{
		OnTakeDamage();

		if (!IsAnimationPlaying(DamageAnimation))
		{
			PlayAnimation(DamageAnimation);
		}
	}

 	UpdateHealthBar();
}

float UPPPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) { return 0.0f; }

	return HealthComponent->GetHealthPercent();
}

bool UPPPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = PPUtils::GetPPPlayerComponent<UPPWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) { return false; }

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UPPPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = PPUtils::GetPPPlayerComponent<UPPWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) { return false; }

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData) ;
}

bool UPPPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool UPPPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->StateName == NAME_Spectating;
}

int32 UPPPlayerHUDWidget::GetKillsNum() const
{
 	const auto Controller = GetOwningPlayer();
	if (!Controller) { return 0; }

 	const auto PlayerState = Cast<APPPlayerState>(Controller->PlayerState);
 	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 UPPPlayerHUDWidget::GetDeathsNum() const
{
 	const auto Controller = GetOwningPlayer();
 	if (!Controller) { return 0; }

 	const auto PlayerState = Cast<APPPlayerState>(Controller->PlayerState);
 	return PlayerState ? PlayerState->GetDeathNum() : 0;
}

FString UPPPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
 	const int32 MaxLen = 3;
 	const TCHAR PrefixSymbol = '0';

 	auto BulletStr = FString::FromInt(BulletsNum);
 	const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

 	if (SymbolsNumToAdd > 0)
 	{
 		BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
 	}

 	return BulletStr;
}

void UPPPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
 	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(NewPawn);
 	if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
 	{
 		HealthComponent->OnHealthChanged.AddUObject(this, &UPPPlayerHUDWidget::OnHealthChanged);
 	}
 	UpdateHealthBar();
}

void UPPPlayerHUDWidget::UpdateHealthBar()
{
 	if (HealthProgressBar)
 	{
 		HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
 	}
}
