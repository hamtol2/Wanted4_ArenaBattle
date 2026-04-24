// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABStageGimmick.generated.h"

// 상태에 따른 처리를 위한 델리게이트.
DECLARE_DELEGATE(FOnStateChangedDelegate);

// 열거형.
// 상태를 나타내는 열거형.
UENUM(BlueprintType)
enum class EStageState : uint8
{
	Ready = 0,
	Fight,
	Reward,
	Next
};

UCLASS()
class ARENABATTLE_API AABStageGimmick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABStageGimmick();

	// Stage Section.
protected:
	// 스테이지를 보여줄 메시 컴포넌트.
	UPROPERTY(VisibleAnywhere, Category = Stage)
	TObjectPtr<class UStaticMeshComponent> Stage;

	// 박스 컴포넌트 (오버랩 이벤트 처리를 위한 컴포넌트).
	UPROPERTY(VisibleAnywhere, Category = Stage)
	TObjectPtr<class UBoxComponent> StageTrigger;

	// StageTrigger에 등록할 오버랩 이벤트 처리 함수.
	UFUNCTION()
	void OnStageTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	// Gate Section(4개 문).
protected:
	// 4개의 문을 Map으로 관리.
	UPROPERTY(VisibleAnywhere, Category = Gate)
	TMap<FName, TObjectPtr<class UStaticMeshComponent>> Gates;

	// 각 문을 담당하는 콜리전을 배열로 관리.
	UPROPERTY(VisibleAnywhere, Category = Gate)
	TArray<TObjectPtr<class UBoxComponent>> GateTriggers;

	// 각 문의 이벤트를 처리할 함수.
	UFUNCTION()
	void OnGateTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	// 문 열고 닫는 함수.
	void OpenAllGates();
	void CloseAllGates();

	// State Section.
protected:
	// 현재 상태를 나타내는 열거형 변수.
	UPROPERTY(EditAnywhere, Category = Stage)
	EStageState CurrentState;

	// 상태 설정에 사용할 함수.
	void SetState(EStageState InNewState);

	// 상태에 따른 처리를 위한 맵.
	TMap<EStageState, FOnStateChangedDelegate> StateChangedActions;

	// 각 상태 처리에 대응하는 함수.
	void SetReady();
	void SetFight();
	void SetChooseReward();
	void SetChooseNext();
};
