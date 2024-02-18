#include <iostream>
#include "cSnotify.h"


#include "Containers/SmartArray.h"
#include "Containers/LinkedList.h"
#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include "Profiler.h"

using namespace Containers;

Profiler profiler;

#define TIMER_CALL(x)	profiler.StartTimer();\
						x;\
						profiler.EndTimer();\
						std::cout << "Elapsed Time : " <<profiler.GetElapsedTime() << std::endl;

int main(int argc, char* argv[])
{
	cPersonGenerator personGenerator;
	cMusicGenerator musicGenerator;
	cSnotify snotify;

	std::string errorMsg;

	personGenerator.LoadCensusFiles(
		"Assets/BabyName/yob2019.txt",
		"Assets/Surname/Names_2010Census.csv",
		"Assets/StreetName/Street_Names.csv", errorMsg);

	TIMER_CALL(musicGenerator.LoadMusicInformation("Assets/Billboard/hot_stuff_2 - Copy.csv", errorMsg));

	unsigned int sizeOfUsers = 10;
	for (int i = 0; i < sizeOfUsers; i++)
	{
		cPerson* newPerson = personGenerator.generateRandomPerson();
		std::cout << "Person Added : " << newPerson->first << std::endl;
		snotify.AddUser(newPerson, errorMsg);
	}

	cPerson* listOfUsers;
	snotify.GetUsers(listOfUsers, sizeOfUsers);

	for (int i = 0; i < sizeOfUsers; i++)
	{
		std::cout << "Fetched Name : " << listOfUsers[i].first << std::endl;
	}

	return -1;
}