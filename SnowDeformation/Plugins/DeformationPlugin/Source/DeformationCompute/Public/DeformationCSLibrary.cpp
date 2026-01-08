#include "DeformationCSLibrary.h"
#include "DeformationCS/DeformationCS.h"
void UDeformationCSLibrary::ExecuteRTComputeShader(UTextureRenderTarget2D* RT)
{
	//Create a dispatch parameters struct and fill it the input array with our args
	FDeformationCSDispatchParams Params(RT->SizeX, RT->SizeY, 1);
	Params.RenderTarget = RT->GameThread_GetRenderTargetResource();
	
	FDeformationCSInterface::Dispatch(Params);
}
