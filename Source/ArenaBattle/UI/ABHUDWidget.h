// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 생성자.
	UABHUDWidget(const FObjectInitializer& ObjectInitializer);

protected:
	// AddToViewport 함수 호출 이후에 호출되는 초기화 함수.
	virtual void NativeConstruct() override;
};
