// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSVReader.h"
#include "DataDistributeComponent.generated.h"



class CSVReader;

USTRUCT(BlueprintType)
struct FDrillDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float DrillPressure;
	UPROPERTY(BlueprintReadWrite)
	float DrillTorque;
	UPROPERTY(BlueprintReadWrite)
	float DrillSpeed;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewData , FDrillDataStruct, DrillData);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRILLDDIGTALTWINS_API UDataDistributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDataDistributeComponent();

	UFUNCTION(BlueprintCallable)
	void DispatchData(FDrillDataStruct data);

	
	UFUNCTION(BlueprintCallable)
	void StartBuffData();

	UFUNCTION(BlueprintCallable)
	void StopBuffData();

	UFUNCTION(BlueprintCallable)
	bool BuffAllData();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(BlueprintAssignable)
	FOnNewData OnNewData;



protected:
	bool bIsDataLoadFinished = false;

	CSVReader* CSVInstance;

	UPROPERTY(BlueprintReadWrite)
	int CurrentDataIndex;

	UPROPERTY(EditDefaultsOnly, Category = "FileSetting");
	FString FileName;

	UPROPERTY(BlueprintReadOnly)
	TArray<FDrillDataStruct> BuffedDrillData;

	FTimerHandle FileLoadTimeHandle;
};
