// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ComputeShaderManagerComponent.h"

// Sets default values for this component's properties
UComputeShaderManagerComponent::UComputeShaderManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	DeformationManager = this;
	// ...
}


// Called when the game starts
void UComputeShaderManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UComputeShaderManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	tempTest += DeltaTime;
	
	// ...
}

void UComputeShaderManagerComponent::AddTrackedObjects(TArray<USceneComponent*> _trackedComponents)
{
	for (USceneComponent* comp : _trackedComponents)
	{
		AddTrackedObject(comp);
	}
}

void UComputeShaderManagerComponent::AddTrackedObject(USceneComponent* _trackedComponent)
{
	if( !_trackedComponent ) return;
	TrackedObjects.Add( _trackedComponent );
}

void UComputeShaderManagerComponent::RemoveTrackedObject(USceneComponent* _trackedComponent)
{
	if( !_trackedComponent ) return;
	for( int i = 0; i < TrackedObjects.Num(); i++ )
	{
		if( TrackedObjects[ i ] == _trackedComponent )
		{
			TrackedObjects.RemoveAt( i );
			i--;
		}
	}
}

void UComputeShaderManagerComponent::UpdateTrackedObjectList()
{
	
}

UComputeShaderManagerComponent* UComputeShaderManagerComponent::GetDeformationManager()
{
	return DeformationManager;
}

