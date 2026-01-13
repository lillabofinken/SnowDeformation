#include "DeformationCSLibrary.h"

void UDeformationCSLibrary::ExecuteRTComputeShader(UTextureRenderTarget2D* _RT, float _SnowDepth, TArray<FMatrix44f> _TrackedObjectMatrices)
{
	//Create a dispatch parameters struct and fill it the input array with our args
	FDeformationCSDispatchParams Params(_RT->SizeX, _RT->SizeY, 1);
	Params.RenderTarget = _RT->GameThread_GetRenderTargetResource();
	Params.MaxSnowDepth = _SnowDepth;
	
	for(int i = 0; i < 64; i++ )
	{
		if(	i < _TrackedObjectMatrices.Num() )
		{
			FMatrix44f matrix = FMatrix44f( _TrackedObjectMatrices[ i ] );;
			Params.TrackedObjectMatrices[ i ] = matrix;
		}
		else
			Params.TrackedObjectMatrices[ i ] = FMatrix44f::Identity;
	}
	const int ObjectAmount = _TrackedObjectMatrices.Num();
	Params.ObjectAmount = ObjectAmount;
	
	FDeformationCSInterface::Dispatch(Params);
}

void UDeformationCSLibrary::ExecuteRTComputeShader(FDeformationCSDispatchParams _params)
{
	FDeformationCSInterface::Dispatch(_params);
}
