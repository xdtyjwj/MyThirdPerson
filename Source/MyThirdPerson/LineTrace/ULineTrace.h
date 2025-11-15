#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Components/PrimitiveComponent.h"
#include "ULineTrace.generated.h" // 注意：头文件名称要和类名一致（建议）


DECLARE_LOG_CATEGORY_EXTERN(LogMaterialParams, Log, All);
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYTHIRDPERSON_API ULineTrace : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULineTrace();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 射线配置参数（可在蓝图中调整）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace", meta = (AllowPrivateAccess = "true"))
	float TraceDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ETraceTypeQuery> TraceChannel = ETraceTypeQuery::TraceTypeQuery1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace", meta = (AllowPrivateAccess = "true"))
	bool bTraceComplex = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace", meta = (AllowPrivateAccess = "true"))
	bool bDrawDebugTrace = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace", meta = (AllowPrivateAccess = "true"))
	FLinearColor DebugTraceColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line Trace", meta = (AllowPrivateAccess = "true"))
	float DebugTraceDuration = 0.1f;

	UPROPERTY()
	AActor* OwnerActor;

	// 蓝图事件委托
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLineTraceHit, AActor*, HitActor);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLineTraceMiss);

	UPROPERTY(BlueprintAssignable, Category = "Line Trace")
	FOnLineTraceHit OnLineTraceHit;

	UPROPERTY(BlueprintAssignable, Category = "Line Trace")
	FOnLineTraceMiss OnLineTraceMiss;
};