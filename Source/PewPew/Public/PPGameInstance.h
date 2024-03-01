// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PPCoreTypes.h"
#include "PPGameInstance.generated.h"

UCLASS()
class PEWPEW_API UPPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FLevelData GetStartupLevel () const { return StartupLevel; }
	void SetStartupLevel (const FLevelData& Data) { StartupLevel = Data; }

	TArray<FLevelData> GetLevelsData() const { return LevelsData; } // todo: copy by constant link 718
	
	FName GetMenuLevelName () const { return MenuLevelName; }

protected:
	UPROPERTY(EditDefaultsOnly, Category="Game", meta=(Tooltip = "Level names must be unique"))
	TArray<FLevelData> LevelsData;
	
	UPROPERTY(EditDefaultsOnly, Category="Game")
	FName MenuLevelName = NAME_None;

private:
	UPROPERTY(EditDefaultsOnly, Category="Game")
	FLevelData StartupLevel;
	
};