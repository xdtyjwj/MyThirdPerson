#include "ULineTrace.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/PrimitiveComponent.h"
#include "Components/MeshComponent.h"
#include "Materials/MaterialInstance.h"
#include "Engine/World.h"
// ULineTrace.cpp 顶部的 #include 区域添加
DEFINE_LOG_CATEGORY(LogMaterialParams);
ULineTrace::ULineTrace()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULineTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!OwnerActor)
	{
		OwnerActor = GetOwner();
		if (!OwnerActor) return;
	}

	// 射线起点和方向
	FVector StartLocation = OwnerActor->GetActorLocation();
	FVector ForwardDirection = OwnerActor->GetActorForwardVector();
	FVector EndLocation = StartLocation + ForwardDirection * TraceDistance;

	// 射线参数配置
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwnerActor);
	FHitResult HitResult;

	// 执行射线检测
	bool bTraceSuccess = UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		StartLocation,
		EndLocation,
		TraceChannel,
		true, // 是否忽略复杂碰撞（与bTraceComplex相反）
		ActorsToIgnore,
		bDrawDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		HitResult,
		true, // 是否生成碰撞响应
		DebugTraceColor, // 射线颜色
		FLinearColor::Green, // 碰撞点颜色
		DebugTraceDuration // 调试显示时长
	);

	// 处理检测结果
	if (bTraceSuccess)
	{
		AActor* HitActor = HitResult.GetActor();
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		int32 FaceIndex = HitResult.FaceIndex;
		if (!HitComponent || FaceIndex < 0) return;

		// 读取金属度和粗糙度
		float Metallic = 0.0f;
		float Roughness = 0.0f;
		UMaterialInterface* HitMaterial = nullptr;

		if (UMeshComponent* MeshComponent = Cast<UMeshComponent>(HitComponent))
		{
			int32 SectionIndex;
			HitMaterial = MeshComponent->GetMaterialFromCollisionFaceIndex(FaceIndex, SectionIndex);
			if (HitMaterial)
			{
				// 区分材质实例和基础材质
				if (UMaterialInstance* MaterialInstance = Cast<UMaterialInstance>(HitMaterial))
				{
					MaterialInstance->GetScalarParameterValue(TEXT("Metallic"), Metallic);
					MaterialInstance->GetScalarParameterValue(TEXT("Roughness"), Roughness);
				}
				else if (UMaterial* BaseMaterial = Cast<UMaterial>(HitMaterial))
				{
					FMaterialParameterInfo MetallicParamInfo(TEXT("Metallic"));
					FMaterialParameterInfo RoughnessParamInfo(TEXT("Roughness"));
					BaseMaterial->GetScalarParameterValue(MetallicParamInfo, Metallic);
					BaseMaterial->GetScalarParameterValue(RoughnessParamInfo, Roughness);
				}

				// 自定义日志输出
				UE_LOG(LogMaterialParams, Log, TEXT("命中材质 - 金属度：%.2f | 粗糙度：%.2f"), Metallic, Roughness);
				if (Metallic > 0.8f)
				{
					UE_LOG(LogMaterialParams, Warning, TEXT("命中高金属材质！金属度：%.2f"), Metallic);
				}

				// 屏幕打印
				FString DebugText = FString::Printf(TEXT("金属度: %.2f | 粗糙度: %.2f"), Metallic, Roughness);
				GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, DebugText);
			}
		}

		OnLineTraceHit.Broadcast(HitActor);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("射线未命中任何物体"));
		OnLineTraceMiss.Broadcast();
	}
}