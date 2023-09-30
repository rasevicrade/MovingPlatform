// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trigger.generated.h"

class UBoxComponent;
class APlatform;
UCLASS()
class MOVINGPLATFORM_API ATrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrigger();

	UPROPERTY(EditInstanceOnly, Category = "Platform Settings")
	TArray<APlatform*> PlatformsToTrigger;

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerVolume;
};
