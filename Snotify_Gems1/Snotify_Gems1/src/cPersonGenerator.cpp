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

	if (!ReadBabyNameFile(babyNameFile))
	{
		return false;
	}


	if (!ReadSurnameFile(surnameFile))
	{
		return false;
	}

	if (!ReadStreetFile(streetNameFile))
	{
		return false;
	}


	return true;
}

unsigned int cPersonGenerator::getNumberOfNamesLoaded(void)
{
	return mListOfBabyNames.getSize();
}

unsigned int cPersonGenerator::getNumberOfSurnamesLoaded(void)
{
	return mListOfSurnames.getSize();
}

unsigned int cPersonGenerator::getNumberOfStreetsLoaded(void)
{
	return mListOfStreetName.getSize();
}

cPerson* cPersonGenerator::generateRandomPerson(void)
{
	cPerson* newPerson = new cPerson();

	BabyNameData randomBabyName = mListOfBabyNames.getAt(GetRandomIntNumber(0, mListOfBabyNames.getSize()));
	StreetData randomStreet = mListOfStreetName.getAt(GetRandomIntNumber(0, mListOfStreetName.getSize()));
	
	newPerson->first = randomBabyName.name;
	newPerson->middle = mListOfBabyNames.getAt(GetRandomIntNumber(0,mListOfBabyNames.getSize())).name;
	newPerson->last = mListOfSurnames.getAt(GetRandomIntNumber(0,mListOfSurnames.getSize()));
	newPerson->gender = randomBabyName.gender == "F" ? cPerson::eGenderType::FEMALE : cPerson::eGenderType::MALE;
	newPerson->age = GetRandomIntNumber(0, 100);
	newPerson->streetNumber = GetRandomIntNumber(0, 100);
	newPerson->streetName = randomStreet.streetName;
	newPerson->streetType = randomStreet.streetType;
	newPerson->streetDirection = randomStreet.streetDirection;
	newPerson->city = canadaCities[GetRandomIntNumber(0, 10)];
	newPerson->province = canadaProvinces[GetRandomIntNumber(0, 13)];

	//ANA NAN
	newPerson->postalCode[0] = GetRandomAlphabet();
	newPerson->postalCode[1] = (char)((GetRandomIntNumber(0,9) + '0'));
	newPerson->postalCode[2] = GetRandomAlphabet();
	newPerson->postalCode[3] = (char)((GetRandomIntNumber(0, 9) + '0'));
	newPerson->postalCode[4] = GetRandomAlphabet();
	newPerson->postalCode[5] = (char)((GetRandomIntNumber(0, 9) + '0'));

	//SIN
	newPerson->SIN = GetSINNumber();

	/*newPerson->m_Snotify_UniqueUserID = newPerson->m_NEXT_Snotify_UniqueUSerID;

	newPerson->m_NEXT_Snotify_UniqueUSerID++;*/

	return newPerson;
}

bool cPersonGenerator::ReadBabyNameFile(const std::string& fileName)
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

		lineCount++;
		std::stringstream ssLine(theLine);

		std::string value;
		unsigned int index = 0;

		BabyNameData data;

		while (std::getline(ssLine, value, ','))
		{
			if (index == 0)
			{
				data.name = value;
			}
			else if (index == 1)
			{
				data.gender = value;
			}
			index++;
		}

		mListOfBabyNames.addAtEnd(data);
	}

	return true;
}

bool cPersonGenerator::ReadSurnameFile(const std::string& fileName)
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

		lineCount++;
		std::stringstream ssLine(theLine);

		std::string value;
		unsigned int index = 0;

		if (lineCount == 1)
		{
			continue;
		}

		while (std::getline(ssLine, value, ','))
		{
			if (index == 0)
			{
				mListOfSurnames.addAtEnd(value);
			}
			index++;
		}
	}

	//std::cout << "Lines read = " << lineCount << std::endl;

	return true;
}

bool cPersonGenerator::ReadStreetFile(const std::string& fileName)
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

		lineCount++;
		std::stringstream ssLine(theLine);

		std::string value;
		unsigned int index = 0;

		if (lineCount == 1)
		{
		}

		StreetData data;

		while (std::getline(ssLine, value, ','))
		{
			if (index == 1)
			{
				data.streetName = value;
			}
			else if (index == 2)
			{
				data.streetType = value;
			}
			else if (index == 3)
			{
				data.streetDirection = value;
			}

			index++;
		}

		mListOfStreetName.addAtEnd(data);
	}

	return true;
}

int cPersonGenerator::GetRandomIntNumber(int minValue, int maxValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(minValue, maxValue);

	return distribution(gen);
}


char cPersonGenerator::GetRandomAlphabet()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> letterDistribution(0, 25);

	return ('A' + letterDistribution(gen));
}

unsigned int cPersonGenerator::GetSINNumber()
{
	unsigned int randomNumber;

	do
	{
		randomNumber = GetRandomIntNumber(100000000, 999999999);
	} while (IsSINExists(randomNumber));

	return randomNumber;
}

bool cPersonGenerator::IsSINExists(unsigned int number)
{
	for (unsigned int i = 0; i < mGeneratedSINNumbers.getSize(); i++)
	{
		if (mGeneratedSINNumbers.getAt(i) == number) return true;
	}

	return false;
}

