#pragma once

#include "CoreMinimal.h"
#include "Rendering/CustomRenderPass.h"
#include "Engine/TextureRenderTarget2D.h"


class FYHCustomRenderPass final : public FCustomRenderPassBase
{
public:
	IMPLEMENT_CUSTOM_RENDER_PASS(FYHCustomRenderPass)

	FYHCustomRenderPass(const FString& InDebugName, ERenderMode InRenderMode, ERenderOutput InRenderOutput, UTextureRenderTarget2D* InRenderTarget)
		:FCustomRenderPassBase(InDebugName , InRenderMode , InRenderOutput , FIntPoint(InRenderTarget->GetSurfaceWidth(), InRenderTarget->GetSurfaceHeight()))
		,OutRenderTarget(InRenderTarget->GameThread_GetRenderTargetResource())	
	{}

	virtual void OnPreRender(FRDGBuilder& GraphBuilder) override
	{
		RenderTargetTexture = OutRenderTarget->GetRenderTargetTexture(GraphBuilder);
	}

	FRenderTarget* OutRenderTarget = nullptr;
};
