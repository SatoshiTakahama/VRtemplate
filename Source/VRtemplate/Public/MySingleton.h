#pragma once
#include "Engine.h"
#include "CoreMinimal.h"
#include "Misc/OutputDevice.h"
#include "UObject/NoExportTypes.h"
#include "MySingleton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMySingletonOutputDeviceUpdate);

UCLASS(Blueprintable, BlueprintType)
class UMySingleton : public UObject
{
  GENERATED_UCLASS_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyConsole)
  TArray<FString> Buffer;

  virtual void BeginDestroy() override;

  void addConsoleText(FString Data);

  UPROPERTY(BlueprintAssignable)
  FMySingletonOutputDeviceUpdate OnOutputUpdate;

};