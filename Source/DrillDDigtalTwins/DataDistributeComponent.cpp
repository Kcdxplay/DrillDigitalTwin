// Fill out your copyright notice in the Description page of Project Settings.


#include "DataDistributeComponent.h"
#include "CSVReader.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include <vector>

// Sets default values for this component's properties
UDataDistributeComponent::UDataDistributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDataDistributeComponent::BeginPlay()
{
	Super::BeginPlay();

	FString FilePath = UKismetSystemLibrary::GetProjectContentDirectory();
	FilePath.Append("WebFiles/");
	FilePath.Append(FileName);
	CSVInstance = new CSVReader(TCHAR_TO_UTF8(*FilePath));
}


// Called every frame
void UDataDistributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDataDistributeComponent::DispatchData(FDrillDataStruct data)
{
	OnNewData.Broadcast(data);
}

void UDataDistributeComponent::StartBuffData()
{
	if (bIsDataLoadFinished)
	{
		return;
	}

	bIsDataLoadFinished = true;
	try
	{
		if (BuffAllData())
		{
			CurrentDataIndex = 0;
			GetOwner()->GetWorldTimerManager().SetTimer(FileLoadTimeHandle, this, &UDataDistributeComponent::StartBuffData, 60.f);
		}
		else
		{
			GetOwner()->GetWorldTimerManager().SetTimer(FileLoadTimeHandle, this, &UDataDistributeComponent::StartBuffData, 5.f);
		}
	}
	catch (const std::exception&)
	{

	}
	bIsDataLoadFinished = false;
}

void UDataDistributeComponent::StopBuffData()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(FileLoadTimeHandle);
}

bool UDataDistributeComponent::BuffAllData()
{
	if (CSVInstance->BuffDataFromFile())
	{
		const std::vector<CSVReader::DrillRowData>* TEMPDrillRowDatas = CSVInstance->GetAllBuffedData();

		if (ensure(TEMPDrillRowDatas != NULL))
		{
			bIsDataLoadFinished = false;
			BuffedDrillData.Empty();
			std::for_each(TEMPDrillRowDatas->begin(), TEMPDrillRowDatas->end(), [this](CSVReader::DrillRowData Data) {BuffedDrillData.Add({ Data.presure,Data.torque,Data.speed }); });
		}

		bIsDataLoadFinished = true;
		return true;
	}
	else
	{
		return false;
	}

	return false;
}