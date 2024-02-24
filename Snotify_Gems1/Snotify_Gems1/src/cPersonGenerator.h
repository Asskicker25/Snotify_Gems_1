#ifndef _cPersonGenerator_HG_
#define _cPersonGenerator_HG_

#include <string>

#include "cPerson.h"
#include "Containers/SmartArray.h"

using namespace Containers;

struct StreetData
{
	int streetNumber = 0;
	std::string streetName;
	std::string streetType;
	std::string streetDirection;
};

struct BabyNameData
{
	std::string name;
	std::string gender;
};

class cPersonGenerator
{
public:
	cPersonGenerator();
	~cPersonGenerator();

	// This takes three files:
	// - One of the "Popular Baby Names" found here: https://www.ssa.gov/oact/babynames/limits.html
	//   (example: "yob2001.txt" which are babies born in the year 2001
	// - The "Names_2010Census.csv" file, from:
	//   "Frequently Occurring Surnames from the 2010 Census" from here:
	//   https://www.census.gov/topics/population/genealogy/data/2010_surnames.html
	// - The "Street_Names.csv" file, from:
	//   "Street Names (San Francisco)" from here: 
	//   https://catalog.data.gov/dataset/street-names-37fec/resource/d655cc82-c98f-450a-b9bb-63521c870503
	// Returns:
	// - true of successful
	// - false if there's any issue (can't find file, or whatever)
	//   If false, then the "errorString" (passed by reference) should be loaded with some sort of 
	//   description of what went wrong (file didn't open, parse issue, Skynet became self aware, etc.)
	//   Use your discretion (and creativity) for this. 
	bool LoadCensusFiles(
		std::string babyNameFile,
		std::string surnameFile,
		std::string streetNameFile,
		std::string& errorString);

	unsigned int getNumberOfNamesLoaded(void);
	unsigned int getNumberOfSurnamesLoaded(void);
	unsigned int getNumberOfStreetsLoaded(void);

	// Randomly generates a person from the data
	// Returns 0, NULL, or nullptr if it can't do this. 
	cPerson* generateRandomPerson(void);

private:
	bool ReadBabyNameFile(const std::string& fileName);
	bool ReadSurnameFile(const std::string& fileName);
	bool ReadStreetFile(const std::string& fileName);
	int GetRandomIntNumber(int minValue, int maxValue);
	char GetRandomAlphabet();
	unsigned int GetSINNumber();
	bool IsSINExists(unsigned int number);


	SmartArray<unsigned int> mGeneratedSINNumbers;
	SmartArray<std::string> mListOfSurnames;
	SmartArray<BabyNameData> mListOfBabyNames;
	SmartArray<StreetData> mListOfStreetName;

	std::string cities[10] = { "Toronto","Montreal","Vancouver","Calgary","Edmonton",
		"Ottawa","Quebec City","Hamilton","Halifax","London" };

	std::string provinces[8] = { "Alberta","British Columbia","Manitoba","Ontario","Quebec","Saskatchewan",
		"Nunavut","Yukon" };


};


#endif 
