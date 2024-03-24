#include "STestEditorViewport.h"

#include "EditorViewportClient.h"

void STestEditorViewport::Construct(const FArguments& InArgs/* , TSharedPtr<class ICommonEditorViewportToolbarInfoProvider> InInfoProvider*/)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

TSharedRef<SEditorViewport> STestEditorViewport::GetViewportWidget()
{
	return SharedThis(this);
}

TSharedPtr<FExtender> STestEditorViewport::GetExtenders() const
{
	TSharedPtr<FExtender> result (MakeShareable(new FExtender));
	return result;
}

void STestEditorViewport::OnFloatingButtonClicked()
{
}

STestEditorViewport::STestEditorViewport()
{
}

STestEditorViewport::~STestEditorViewport()
{
}

TSharedRef<FEditorViewportClient> STestEditorViewport::MakeEditorViewportClient()
{
	PreviewScene = MakeShareable(new FPreviewScene(FPreviewScene::ConstructionValues()));
	//向 PreViewScene 中添加模型
	{
		FString ModelPath = TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"); 
		UStaticMesh* SM = LoadObject<UStaticMesh>(NULL ,*ModelPath ,NULL , LOAD_None , NULL);
		UStaticMeshComponent* SMC = NewObject<UStaticMeshComponent>();
		SMC->SetStaticMesh(SM);
		PreviewScene->AddComponent(SMC, FTransform::Identity);
	}
	
	TSharedPtr<FEditorViewportClient> EditorViewportClient = MakeShareable( new FEditorViewportClient(nullptr, PreviewScene.Get()) );

	return EditorViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> STestEditorViewport::MakeViewportToolbar()
{
	return SNew(SCommonEditorViewportToolbarBase, SharedThis(this));
}
