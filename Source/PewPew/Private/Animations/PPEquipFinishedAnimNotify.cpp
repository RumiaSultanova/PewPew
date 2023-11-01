// Pew-Pew Game. All Rights Reserved.


#include "Animations/PPEquipFinishedAnimNotify.h"

void UPPEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}