// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "CoreMinimal.h"

/**
 * 
 */
class DRILLDDIGTALTWINS_API CSVReader
{
public:
	CSVReader(std::string FilePath) : FilePath(FilePath), CurrentIndex(0) {}
	~CSVReader();

public:
	struct DrillRowData
	{
		float torque;
		float presure;
		float power;
		float innerPower;
		float speed;
	};

public:

	bool BuffDataFromFile();

	//DrillRowData GetNextData();

	const std::vector<DrillRowData>* GetAllBuffedData();
private:
	inline DrillRowData processRowData(std::string rawStr, std::string spliteStr = ",");

private:
	std::string FilePath;
	std::vector<DrillRowData> BuffedDatas;

	std::ifstream ifs;

	bool bIsFileLoaded = false;

	int CurrentIndex;
};
