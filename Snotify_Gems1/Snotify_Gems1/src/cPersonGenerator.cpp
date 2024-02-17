#include "cPersonGenerator.h"

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )

#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>

cPersonGenerator::cPersonGenerator()
{
}

cPersonGenerator::~cPersonGenerator()
{

}

bool cPersonGenerator::LoadCensusFiles(
	std::string babyNameFile,
	std::string surnameFile,
	std::string streetNameFile,
	std::string& errorString)
{

	if (!ReadCSVFile(babyNameFile, false, [this](std::string value)
		{
			mListOfBabyNames.addAtEnd(value);
		}))
	{
		return false;
	}


	if (!ReadCSVFile(surnameFile, true, [this](std::string value)
		{
			mListOfSurnames.addAtEnd(value);
		}))
	{
		return false;
	}

	if (!ReadCSVFile(streetNameFile, true, [this](std::string value)
		{
			mListOfStreetName.addAtEnd(value);
		}))
	{
		return false;
	}

	std::cout << "Name : " << mListOfBabyNames.getAt(0) << std::endl;
	std::cout << "Surname : " << mListOfSurnames.getAt(0) << std::endl;
	std::cout << "StreetName : " << mListOfStreetName.getAt(0) << std::endl;

	return true;
}

bool cPersonGenerator::ReadCSVFile(const std::string& fileName, bool headerAvailable,
	std::function<void(std::string) > OnLineRead)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "Didn't open file" << std::endl;
		return false;
	}

	std::string theLine;

	unsigned int lineCount = 0;
	while (std::getline(file, theLine))
	{
		std::string name;

		lineCount++;
		std::stringstream ssLine(theLine);

		std::string value;
		unsigned int index = 0;

		if (headerAvailable && lineCount == 1)
		{
			continue;
		}

		while (std::getline(ssLine, value, ','))
		{
			if (index == 0)
			{
				name = value;
			}
			index++;
		}

		OnLineRead(name);
	}

	std::cout << "Lines read = " << lineCount << std::endl;

	return true;
}

