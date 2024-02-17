#include <iostream>

#include "Containers/SmartArray.h"
#include "Containers/LinkedList.h"
#include "cPersonGenerator.h"

using namespace Containers;

int main(int argc, char* argv[])
{
	cPersonGenerator personGenerator;

	std::string errorMsg;
	personGenerator.LoadCensusFiles(
		"Assets/BabyName/yob2019.txt", 
		"Assets/Surname/Names_2010Census.csv",
		"Assets/StreetName/Street_Names.csv", errorMsg);

	return -1;
}