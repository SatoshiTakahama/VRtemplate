// Fill out your copyright notice in the Description page of Project Settings.

#include "MySingleton.h"

class FMyOutputDevice : public FOutputDevice
{
public:
  UMySingleton *mySingleton;
  FMyOutputDevice()
  {
    mySingleton = nullptr;
  }

  virtual void Serialize(const TCHAR* Data, ELogVerbosity::Type Verbosity, const class FName& Category) override {
    if (!mySingleton) return;
    if (!mySingleton->IsValidLowLevel()) return;
      FString verbosityString;
      if (Verbosity == ELogVerbosity::Error) {
        verbosityString = "Error: ";
      } else if (Verbosity == ELogVerbosity::Warning) {
        verbosityString = "Warning: ";
      } else if (Verbosity == ELogVerbosity::Display) {
        verbosityString = "Display: ";
      } else {
        verbosityString = "";
      }
      FString add = Category.ToString() + ": " + verbosityString + FString(Data);
      mySingleton->addConsoleText(add);
  }

  virtual bool CanBeUsedOnAnyThread() const override { return false; }
};

static FMyOutputDevice *d = nullptr;

UMySingleton::UMySingleton(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
  if (d == nullptr) {
    d = new FMyOutputDevice;
    check(GLog);
    GLog->AddOutputDevice(d);
  }
  if (d) {
    d->mySingleton = this;
  }
}

void UMySingleton::BeginDestroy() {
  if (d) {
    d->mySingleton = nullptr;
  }
  Super::BeginDestroy();
}

void UMySingleton::addConsoleText(FString Data) {
  Buffer.Insert(Data, 0);
  Buffer.SetNum(30);

  static bool bFirst = false;
  if (bFirst == false) {
    bFirst = true;
    OnOutputUpdate.Broadcast();
    bFirst = false;
  }
}