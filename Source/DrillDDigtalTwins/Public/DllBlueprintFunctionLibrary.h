// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DllBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DRILLDDIGTALTWINS_API UDllBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UDllBlueprintFunctionLibrary();

	UFUNCTION(BlueprintCallable,Category="DllHelper")
	static int AddNum(int num1, int num2);

	UFUNCTION(BlueprintCallable,Category="DllHelper")
	static FString Greeting();

	UFUNCTION(BlueprintCallable,Category="DllHelper")
	static FString GetCurrentDomain();

private:
	//static void* DLLHandle;


private:
	static void SetupDLLHandle();
};

//void* UDllBlueprintFunctionLibrary::DLLHandle = NULL;
