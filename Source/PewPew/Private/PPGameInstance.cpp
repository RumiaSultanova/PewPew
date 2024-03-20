// Pew-Pew Game. All Rights Reserved.

#include "PPGameInstance.h"
#include "Sound/PPSoundFuncLib.h"

void UPPGameInstance::ToggleVolume()
{
	UPPSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}
