#include "Trigger.h"

#include "Platform.h"
#include "Components/BoxComponent.h"

ATrigger::ATrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!TriggerVolume) 
		return;

	RootComponent = TriggerVolume;
}

void ATrigger::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerVolume)
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::OnOverlapBegin);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ATrigger::OnOverlapEnd);
	}
}

void ATrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (APlatform* Platform : PlatformsToTrigger)
	{
		if (Platform != nullptr)
			Platform->SetActive(true);
	}
}

void ATrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (APlatform* Platform : PlatformsToTrigger)
	{
		if (Platform != nullptr)
			Platform->SetActive(false);
	}
}


