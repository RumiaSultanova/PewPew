// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PPGameInstance.generated.h"

UCLASS()
class PEWPEW_API UPPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FName GetStartupLevelName () const { return StartupLevelName; }

protected:
	UPROPERTY(EditDefaultsOnly, Category="Game")
	FName StartupLevelName = NAME_None;
};