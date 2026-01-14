// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "ComputeShaderManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SNOWDEFORMATION_API UComputeShaderManagerComponent : public USceneComponent
{
	GENERATED_BODY()

	
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

	UPROPERTY( EditAnywhere, Category = "Manager" )
	int MaxObjectUpdatesPerFrame = 10;
	
	UPROPERTY( EditAnywhere, Category = "ImportantVariables" ) UMaterialInterface*           DeformationClearMaterial;
	UPROPERTY( EditAnywhere, Category = "ImportantVariables" ) UTextureRenderTarget2D*       RenderTarget;
	UPROPERTY( EditAnywhere, Category = "ImportantVariables" ) UMaterialParameterCollection* MPC = nullptr;

	UPROPERTY( EditAnywhere, Category = "SnowSettings" ) TEnumAsByte<ECollisionChannel> DeformationChannel;
	UPROPERTY( EditAnywhere, Category = "SnowSettings" ) float   MaxSnowDepth = 50;
	UPROPERTY( EditAnywhere, Category = "SnowSettings" ) FVector SnowCornerOne;
	UPROPERTY( EditAnywhere, Category = "SnowSettings" ) FVector SnowCornerTwo;
private:

	UPROPERTY()	UMaterialParameterCollectionInstance* MPC_Instance = nullptr;
	UPROPERTY()	TArray<USceneComponent*> TrackedObjects;
	int ObjectIndex = 0;
	

public:
	UFUNCTION( BlueprintCallable ) void SetSnowCornerOne( FVector _pos){SnowCornerOne = _pos;UpdateCornersMPC();}
	UFUNCTION( BlueprintCallable ) void SetSnowCornerTwo( FVector _pos){SnowCornerTwo = _pos;UpdateCornersMPC();}
	UFUNCTION( BlueprintCallable ) void UpdateCornersMPC();
	
	UFUNCTION( BlueprintCallable ) void AddTrackedObjects  ( TArray<USceneComponent*> _trackedComponent);
	UFUNCTION( BlueprintCallable ) void AddTrackedObject   ( USceneComponent*         _trackedComponent);
	UFUNCTION( BlueprintCallable ) void RemoveTrackedObject( USceneComponent*         _trackedComponent );

private:
	void SendDataAndRunShader();
	TArray<FMatrix44f> MatricesToSend();

	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static UComputeShaderManagerComponent* GetDeformationManager();
private:
	inline static UComputeShaderManagerComponent* DeformationManager = nullptr;
		
};
