// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFunctionLibrary.h"

UObject* UMyFunctionLibrary::GetSingleton(bool& IsValid)
{
	IsValid = false;
	UObject* o = (GEngine->GameSingleton);

	if (!o) return NULL;
	if (!o->IsValidLowLevel()) return NULL;

	IsValid = true;
	return o;
}