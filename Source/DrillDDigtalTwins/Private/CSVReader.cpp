// Fill out your copyright notice in the Description page of Project Settings.


#include "CSVReader.h"


CSVReader::~CSVReader()
{
	if (ifs.is_open())
	{
		ifs.close();
	}
}

bool CSVReader::BuffDataFromFile()
{
	bIsFileLoaded = false;
	CurrentIndex = 0;

	ifs.close();
	ifs.open(FilePath);

	if (!ifs.bad())
	{
		try
		{
			std::string tempStr;
			std::getline(ifs, tempStr);

			while (std::getline(ifs, tempStr))
			{
				BuffedDatas.push_back(processRowData(tempStr));
			}

			ifs.close();
			bIsFileLoaded = true;
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}

	return false;
}



const std::vector<CSVReader::DrillRowData>* CSVReader::GetAllBuffedData()
{
	return &BuffedDatas;
}

CSVReader::DrillRowData CSVReader::processRowData(std::string rawStr, std::string spliteStr)
{
	std::vector<float> tempDataStore;

	size_t pos = 0;
	while ((pos = rawStr.find(spliteStr)) != std::string::npos)
	{
		tempDataStore.push_back(
			std::stof(rawStr.substr(0, rawStr.find(spliteStr)))
		);

		rawStr.erase(0, pos + spliteStr.length());
	}
	tempDataStore.push_back(std::stof(rawStr));

	DrillRowData myData;
	myData.torque = tempDataStore[0];
	myData.presure = tempDataStore[1];
	myData.power = tempDataStore[2];
	myData.innerPower = tempDataStore[3];
	myData.speed = tempDataStore[4];

	return myData;
}