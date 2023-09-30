#include "Platform.h"

#include "Components/BoxComponent.h"

APlatform::APlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!TriggerVolume)
		return;

	TriggerVolume->SetBoxExtent(FVector(50, 50, 50));
	TriggerVolume->SetupAttachment(RootComponent);

	SetMobility(EComponentMobility::Movable);
}

void APlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetActive(true);
}

void APlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetActive(false);
}

void APlatform::BeginPlay()
{
	Super::BeginPlay();

	WorldStartLocation = GetActorLocation();
	WorldTargetLocation = GetTransform().TransformPosition(TargetLocation);

	if (HasAuthority())
	{
		if (!IsTriggered)
		{
			IsActive = true;
		}

		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatform::OnOverlapBegin);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatform::OnOverlapEnd);

		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void APlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsActive)
		return;

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		if (FVector::Distance(Location, WorldStartLocation) > FVector::Distance(WorldTargetLocation, WorldStartLocation))
		{
			const FVector TempLocation = WorldStartLocation;
			WorldStartLocation = WorldTargetLocation;
			WorldTargetLocation = TempLocation;
		}
		const FVector Direction = (WorldTargetLocation - WorldStartLocation).GetSafeNormal();
		Location += Speed * DeltaTime * Direction;
		SetActorLocation(Location);
	}
}

void APlatform::SetActive(bool bActive)
{
	if (IsTriggered)
	{
		IsActive = bActive;
	}
}





