// Pew-Pew Game. All Rights Reserved.


#include "Player/PPBaseCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
APPBaseCharacter::APPBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APPBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APPBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APPBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

