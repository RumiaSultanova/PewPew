// Pew-Pew Game. All Rights Reserved.


#include "Sound/PPSoundFuncLib.h"
#include "Sound/SoundClass.h"

void UPPSoundFuncLib::SetSoundVolume(USoundClass* SoundClass, float Volume)
{
	if (!SoundClass) { return; }

	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void UPPSoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
	if (!SoundClass) { return; }

	const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f :1.0f;
	SetSoundVolume(SoundClass, NextVolume);
}
