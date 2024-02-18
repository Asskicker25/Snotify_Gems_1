#include <iostream>
#include "cSnotify.h"


#include "Containers/SmartArray.h"
#include "Containers/LinkedList.h"
#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include "Profiler.h"

using namespace Containers;

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

	cPerson* updatedUser = new cPerson();

	unsigned int sizeOfUsers = 10;
	for (int i = 0; i < sizeOfUsers; i++)
	{
		cPerson* newPerson = personGenerator.generateRandomPerson();
		std::cout << "Person Added : " << newPerson->first << std::endl;
		snotify.AddUser(newPerson, errorMsg);

		if (i == 5)
		{
			updatedUser = personGenerator.generateRandomPerson();
			updatedUser->SIN = newPerson->SIN;
			updatedUser->setSpotifyUniqueUserId(newPerson->getSnotifyUniqueUserID());
			std::cout << "SIN : " << newPerson->SIN << std::endl;
		}
	}

	cPerson* listOfUsers;

	snotify.UpdateUser(updatedUser,errorMsg);

	snotify.GetUsers(listOfUsers, sizeOfUsers);

	for (int i = 0; i < sizeOfUsers; i++)
	{
		std::cout << "Fetched Name : " << listOfUsers[i].first << std::endl;

		if (i == 5)
		{
			std::cout << "SIN : " << listOfUsers[i].SIN << std::endl;
		}
	}

	return -1;
}