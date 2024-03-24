#pragma once

#include "CoreMinimal.h"
#include "SCommonEditorViewportToolbarBase.h"
#include "SEditorViewport.h"

class STestEditorViewport : public SEditorViewport , public ICommonEditorViewportToolbarInfoProvider
{
public:
	SLATE_BEGIN_ARGS(STestEditorViewport){}
	SLATE_END_ARGS()

	// Begin ofICommonEditorViewportToolbarInfoProvider interface
	virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;
	virtual TSharedPtr<FExtender> GetExtenders() const override;
	virtual void OnFloatingButtonClicked() override;
	// End of ICommonEditorViewportToolbarInfoProvider interface
	
	void Construct(const FArguments& InArgs /*, TSharedPtr<class ICommonEditorViewportToolbarInfoProvider> InInfoProvider*/);
	STestEditorViewport();
	~STestEditorViewport();

protected:
	/* SEditorViewport interface */
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
	
public:
	TSharedPtr<class FPreviewScene> PreviewScene;
};
