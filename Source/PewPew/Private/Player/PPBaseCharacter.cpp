// Pew-Pew Game. All Rights Reserved.

#include "Player/PPBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PPCharacterMovementComponent.h"
#include "Components/PPHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/PPWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"

 APPBaseCharacter::APPBaseCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<UPPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

 	HealthComponent = CreateDefaultSubobject<UPPHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
 	HealthTextComponent->SetupAttachment(GetRootComponent());
 	HealthTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<UPPWeaponComponent>("WeaponComponent");
}

void APPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

 	check(HealthComponent);
 	check(HealthTextComponent);

 	OnHealthChanged(HealthComponent->GetHealth());
 	HealthComponent->OnDeath.AddUObject(this, &APPBaseCharacter::OnDeath);
 	HealthComponent->OnHealthChanged.AddUObject(this, &APPBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &APPBaseCharacter::OnGroundLanded);
}

void APPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APPBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APPBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APPBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &APPBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APPBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APPBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APPBaseCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UPPWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UPPWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UPPWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UPPWeaponComponent::Reload);
}

void APPBaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void APPBaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void APPBaseCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void APPBaseCharacter::OnStopRunning()
{
	WantsToRun = false;
}

bool APPBaseCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
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

void APPBaseCharacter::OnHealthChanged(float Health)
{
 	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void APPBaseCharacter::OnDeath()
{
	PlayAnimMontage(DeathAnimMontage);

 	GetCharacterMovement()->DisableMovement();

 	SetLifeSpan(LifeSpanOnDeath);

 	if (Controller)
 	{
 		Controller->ChangeState(NAME_Spectating);
 	}
 	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
 	WeaponComponent->StopFire();
}

void APPBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;

 	if (FallVelocityZ < LandedDamageVelocity.X) { return; }

 	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
 	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}