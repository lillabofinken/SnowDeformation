// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ComputeShaderManagerComponent.h"

#include "DeformationCSLibrary.h"
#include "DeformationCS/DeformationCS.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Materials/MaterialParameterCollectionInstance.h"


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
	if( MPC )
	{
		MPC_Instance = GetWorld()->GetParameterCollectionInstance( MPC );
		UpdateCornersMPC();
	}
	if( IsValid( RenderTarget ) && IsValid( DeformationClearMaterial ) )
		UKismetRenderingLibrary::DrawMaterialToRenderTarget( this, RenderTarget, DeformationClearMaterial );
	
	// ...
	
}


// Called every frame
void UComputeShaderManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SendDataAndRunShader();
	// ...
}

void UComputeShaderManagerComponent::UpdateCornersMPC()
{
	if( MPC_Instance )
	{
		FLinearColor corners = FLinearColor(SnowCornerOne.X,SnowCornerOne.Y,SnowCornerTwo.X,SnowCornerTwo.Y );
		MPC_Instance->SetVectorParameterValue("Corners",corners);
		MPC_Instance->SetScalarParameterValue( "POMSnowHeight", MaxSnowDepth );
	}
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

void UComputeShaderManagerComponent::SendDataAndRunShader()
{
	TArray<FMatrix44f> matrices = MatricesToSend();
	FDeformationCSDispatchParams Params(RenderTarget->SizeX, RenderTarget->SizeY, 1);
	float time = GetWorld()->GetTimeSeconds();
	GEngine->AddOnScreenDebugMessage(63463, 5, FColor::Green, FString::SanitizeFloat(time));
	Params.Time = time;
	Params.RenderTarget = RenderTarget->GameThread_GetRenderTargetResource();
	Params.NoiseTexture = NoiseTexture;
	Params.MaxSnowDepth = MaxSnowDepth;
	Params.SnowCorners = FLinearColor(SnowCornerOne.X, SnowCornerOne.Y, SnowCornerTwo.X, SnowCornerTwo.Y);
	
	for(int i = 0; i < 64; i++ )
	{
		if(	i < matrices.Num() )
		{
			FMatrix44f matrix = FMatrix44f( matrices[ i ] );;
			Params.TrackedObjectMatrices[ i ] = matrix;
		}
		else
			Params.TrackedObjectMatrices[ i ] = FMatrix44f::Identity;
	}
	const int ObjectAmount = matrices.Num();
	Params.ObjectAmount = ObjectAmount;
	
	UDeformationCSLibrary::ExecuteRTComputeShader(Params);
}

TArray<FMatrix44f> UComputeShaderManagerComponent::MatricesToSend()
{
	TArray<FMatrix44f> output;
	int loop = ( ( MaxObjectUpdatesPerFrame < TrackedObjects.Num() ) ? MaxObjectUpdatesPerFrame : TrackedObjects.Num() );
	for( int i = 0; i < loop; i++ )
	{
		if( TrackedObjects.Num() == 0 ) return output;
		if( !TrackedObjects.IsValidIndex( ObjectIndex ) ) ObjectIndex = 0;

		auto object = TrackedObjects[ ObjectIndex ];
		ObjectIndex++; // CAN ONLY BE HERE IF IT WON'T BE USED BELLOW
		
		if( IsValid( object ) )
		{
			const float scale = object->GetComponentScale().X * object->GetComponentScale().X;
			
			const FVector traceStart = object->GetComponentLocation() + FVector( 0,0,scale );
			const FVector traceEnd = traceStart - FVector(0,0,scale * 2 + MaxSnowDepth + 100.0 );
			
			FCollisionObjectQueryParams objectQueryParams;
			objectQueryParams.AddObjectTypesToQuery(DeformationChannel);



			FHitResult hit;
			GetWorld()->LineTraceSingleByObjectType( hit, traceStart, traceEnd,objectQueryParams );

			if(debug) DrawDebugLine(GetWorld(),traceStart, traceEnd, hit.bBlockingHit ? FColor::Red :FColor::Green, false, 0.0f, 0, 10 );
			if ( !hit.bBlockingHit)
				continue;
			
			const float height = hit.bBlockingHit ? hit.Distance : 10000000.0f;

			FMatrix44f matrix = FMatrix44f( TrackedObjects[ i ]->GetComponentTransform().ToMatrixWithScale() );
			matrix.M[ 3 ][ 2 ] = height;
			
			output.Add( matrix) ;

		}
		else
		{
			TrackedObjects.RemoveAt( ObjectIndex );
			loop--;
			i--;
			
			continue;
		}
	}
	return output;
}


UComputeShaderManagerComponent* UComputeShaderManagerComponent::GetDeformationManager()
{
	return DeformationManager;
}

