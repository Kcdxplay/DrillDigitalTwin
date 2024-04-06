// Fill out your copyright notice in the Description page of Project Settings.


#include "DllBlueprintFunctionLibrary.h"
#include "../../../../../../../Source/Runtime/Core/Public/Misc/Paths.h"

typedef const int (*_MyAddNum)(int num1, int num2);
typedef const char* (*_GreetingFuncPtr)();

void* DLLHandle = NULL;

UDllBlueprintFunctionLibrary::UDllBlueprintFunctionLibrary()
{
	SetupDLLHandle();
}

int UDllBlueprintFunctionLibrary::AddNum(int num1, int num2)
{
	SetupDLLHandle();
	if (DLLHandle != NULL)
	{
		_MyAddNum DLLFuncPtr = NULL;
		FString procName = "MyAddNum";

		DLLFuncPtr = (_MyAddNum)FPlatformProcess::GetDllExport(DLLHandle, *procName);

		if (DLLFuncPtr != NULL)
		{
			return DLLFuncPtr(num1, num2);
		}
	}

	return 0;
}

FString UDllBlueprintFunctionLibrary::Greeting()
{
	SetupDLLHandle();
	if (DLLHandle != NULL)
	{
		_GreetingFuncPtr FuncPtr = NULL;
		FString procName = "GetGreeting";

		FuncPtr = (_GreetingFuncPtr)FPlatformProcess::GetDllExport(DLLHandle, *procName);

		if (FuncPtr != NULL)
		{
			return  FuncPtr();
		}
	}

	return "";
}

void UDllBlueprintFunctionLibrary::SetupDLLHandle()
{
	if (DLLHandle != NULL)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Load Dll Started"));
	FString filePath = FPaths::Combine(*FPaths::EnginePluginsDir(), TEXT("DrillLibrary.dll"));

	if (FPaths::FileExists(filePath))
	{
		DLLHandle = FPlatformProcess::GetDllHandle(*filePath); // Retrieve the DLL.
		UE_LOG(LogTemp, Warning, TEXT("Load Dll Success"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Load Dll Failed"));
	}
}

FString UDllBlueprintFunctionLibrary::GetCurrentDomain()
{
	typedef const char* (*_GetDomain)(bool res);
	FString filePath = FPaths::Combine(*FPaths::EnginePluginsDir(), TEXT("DrillLibrary.dll"));

	void* DLLHandleTRUE = NULL;
	if (FPaths::FileExists(filePath))
	{
		DLLHandleTRUE = FPlatformProcess::GetDllHandle(*filePath); // Retrieve the DLL.
	}
	if (DLLHandleTRUE != NULL)
	{
		_GetDomain DLLFuncPtr = NULL;
		FString procName = "GetDomain";
		DLLFuncPtr = (_GetDomain)FPlatformProcess::GetDllExport(DLLHandleTRUE, *procName);
		if (DLLFuncPtr != NULL)
		{
			const char* result = DLLFuncPtr(false);
			FString output(result);
			return output;
		}
	}
	return "Nope";
}