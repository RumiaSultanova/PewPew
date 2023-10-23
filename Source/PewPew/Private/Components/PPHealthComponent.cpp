// Pew-Pew Game. All Rights Reserved.


#include "Components/PPHealthComponent.h"

// Sets default values for this component's properties
UPPHealthComponent::UPPHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPPHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
}

