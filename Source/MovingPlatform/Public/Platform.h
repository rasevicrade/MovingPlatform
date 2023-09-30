
#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "Platform.generated.h"

class UBoxComponent;
class ATrigger;

UCLASS()
class MOVINGPLATFORM_API APlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	APlatform();

	/** Should this platform be always on, or triggered by a source */
	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	bool IsTriggered = false;

	//** Should this platform be triggered by a volume present on itself */
	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	bool IsSelfTriggered = false;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerVolume;

	/** Movement speed for the platform */
	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	float Speed = 200.f;

	/** Gadget to set where platform should end */
	UPROPERTY(EditAnywhere, Category = "Platform Settings", Meta = (MakeEditWidget = true))
	FVector TargetLocation;


	/**
	 * @brief If platform is activated by an external source, this function
	 * should be used to set its state
	 * @param bActive 
	 */
	void SetActive(bool bActive);

private:
	/** Private property to keep starting location of platform */
	FVector WorldStartLocation;
	/** Private property to keep target location of platform */
	FVector WorldTargetLocation;
	/** Private property for tracking of platform movement state */
	bool IsActive;


protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
