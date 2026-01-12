// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ComputeShaderManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SNOWDEFORMATION_API UComputeShaderManagerComponent : public USceneComponent
{
	GENERATED_BODY()

	float tempTest = 0;
public:	
	// Sets default values for this component's properties
	UComputeShaderManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<int32> DeformationCS;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY( EditAnywhere )
	bool debug = false;

	UPROPERTY( EditAnywhere )
	int MaxObjectUpdatesPerFrame = 10;
	
	UPROPERTY( EditAnywhere )
	UMaterialParameterCollection* MPC;
	
	UPROPERTY( EditAnywhere )
	TEnumAsByte<ECollisionChannel> DeformationChannel;

	UPROPERTY( EditAnywhere )
	UMaterialInterface* DeformationCalculationMaterial;
	UPROPERTY( EditAnywhere )
	UMaterialInterface* DeformationClearMaterial;
	UPROPERTY( EditAnywhere )
	UTextureRenderTarget2D* RenderTarget;

	UPROPERTY( EditAnywhere, Category = "SnowSettings" )
	FVector SnowCornerOne;
	UPROPERTY( EditAnywhere, Category = "SnowSettings" )
	FVector SnowCornerTwo;
private:
	UPROPERTY()
	UMaterialParameterCollectionInstance* MPC_Instance = nullptr;

	UPROPERTY()
	TArray<USceneComponent*> TrackedObjects;
	int ObjectIndex = 0;
	

public:
	UFUNCTION( BlueprintCallable )
	void AddTrackedObjects( TArray<USceneComponent*> _trackedComponent);
	
	UFUNCTION( BlueprintCallable )
	void AddTrackedObject( USceneComponent* _trackedComponent);
	UFUNCTION( BlueprintCallable )
	void RemoveTrackedObject( USceneComponent* _trackedComponent );

private:
	void UpdateTrackedObjectList();

	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UComputeShaderManagerComponent* GetDeformationManager();
private:
	inline static UComputeShaderManagerComponent* DeformationManager = nullptr;
		
};
