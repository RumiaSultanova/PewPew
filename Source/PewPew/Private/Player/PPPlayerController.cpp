// Pew-Pew Game. All Rights Reserved.


#include "Player/PPPlayerController.h"
#include "PewPewGameModeBase.h"
#include "Components/PPRespawnComponent.h"
#include "PPGameInstance.h"

APPPlayerController::APPPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UPPRespawnComponent>("RespawnComponent");
}

void APPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		if (const auto GameMode = Cast<APewPewGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &APPPlayerController::OnMatchStateChanged);
		}
	}
}

void APPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent) { return; }

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &APPPlayerController::OnPauseGame);
	InputComponent->BindAction("Mute", IE_Pressed, this, &APPPlayerController::OnMuteSound);
}

void APPPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) { return; }

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void APPPlayerController::OnMatchStateChanged(EPPMatchState State)
{
	if (State == EPPMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void APPPlayerController::OnMuteSound()
{
	if (!GetWorld()) { return; }

	const auto PPGameInstance = GetWorld()->GetGameInstance<UPPGameInstance>();
	if (!PPGameInstance) { return; }

	PPGameInstance->ToggleVolume();
}
