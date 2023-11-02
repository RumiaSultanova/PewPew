// Pew-Pew Game. All Rights Reserved.


#include "Animations/PPAnimNotify.h"

void UPPAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}