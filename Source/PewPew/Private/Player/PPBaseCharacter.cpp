// Pew-Pew Game. All Rights Reserved.


#include "Player/PPBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PPCharacterMovementComponent.h"
#include "Components/PPHealthComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
 APPBaseCharacter::APPBaseCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<UPPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

 	HealthComponent = CreateDefaultSubobject<UPPHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
 	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

 	check(HealthComponent);
 	check(HealthTextComponent);
}

// Called every frame
void APPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

 	const auto Health = HealthComponent->GetHealth();
 	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

// Called to bind functionality to input
void APPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APPBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APPBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APPBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &APPBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APPBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APPBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APPBaseCharacter::OnStopRunning);
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
