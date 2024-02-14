// Pew-Pew Game. All Rights Reserved.

#include "Player/PPPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/PPWeaponComponent.h"

APPPlayerCharacter::APPPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}


void APPPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APPPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APPPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APPPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &APPPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APPPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APPPlayerCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APPPlayerCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UPPWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UPPWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UPPWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UPPWeaponComponent::Reload);
}

void APPPlayerCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void APPPlayerCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void APPPlayerCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void APPPlayerCharacter::OnStopRunning()
{
	WantsToRun = false;
}

bool APPPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void APPPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}
