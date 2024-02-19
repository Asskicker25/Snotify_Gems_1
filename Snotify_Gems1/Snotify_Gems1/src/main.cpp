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

	unsigned int sizeOfUsers = 5;
	for (int i = 0; i < sizeOfUsers; i++)
	{
		cPerson* newPerson = personGenerator.generateRandomPerson();
		std::cout << "Added : " << newPerson->first << std::endl;
		snotify.AddUser(newPerson, errorMsg);

		if (i == 0)
		{
			updatedUser = personGenerator.generateRandomPerson();
			updatedUser->SIN = newPerson->SIN;
			updatedUser->setSpotifyUniqueUserId(newPerson->getSnotifyUniqueUserID());
			std::cout << "SIN : " << newPerson->SIN << std::endl;
		}
	}

	cPerson* listOfUsers;
	unsigned int usersCount;

	snotify.UpdateUser(updatedUser, errorMsg);

	snotify.GetUsers(listOfUsers, usersCount);

	for (int i = 0; i < usersCount; i++)
	{
		std::cout << "Updated Name : " << listOfUsers[i].first << std::endl;

		if (i == 0)
		{
			std::cout << "SIN : " << listOfUsers[i].SIN << std::endl;
		}
	}

	snotify.DeleteUser(updatedUser->getSnotifyUniqueUserID(), errorMsg);

	snotify.GetUsers(listOfUsers, usersCount);
	for (int i = 0; i < usersCount; i++)
	{
		std::cout << "Deleted : " << listOfUsers[i].first << std::endl;

		if (i == 0)
		{
			std::cout << "SIN : " << listOfUsers[i].SIN << std::endl;
		}
	}

	cSong* songToUpdate = musicGenerator.getRandomSong();
	unsigned int uniqueId = songToUpdate->getUniqueID();

	snotify.AddSong(songToUpdate, errorMsg);

	cSong* songFound = snotify.FindSong(songToUpdate->name, songToUpdate->artist);

	if (snotify.FindSong(uniqueId))
	{
		std::cout << "Added Song : " << snotify.FindSong(uniqueId)->name << std::endl;
	}

	if (!snotify.AddSongToUserLibrary(listOfUsers[0].getSnotifyUniqueUserID(), songToUpdate, errorMsg))
	{
		std::cout << errorMsg << std::endl;
	}

	snotify.UpdateRatingOnSong(listOfUsers[0].getSnotifyUniqueUserID(), songToUpdate->getUniqueID(), 3);
	
	unsigned int rating;

	if (snotify.GetCurrentSongRating(listOfUsers[0].getSnotifyUniqueUserID(), songToUpdate->getUniqueID(), rating))
	{
		std::cout << "Rating of " << songToUpdate->name << " : " << rating << std::endl;
	}

	unsigned int numOfPlays;

	if (snotify.GetCurrentSongNumberOfPlays(listOfUsers[0].getSnotifyUniqueUserID(), songToUpdate->getUniqueID(), numOfPlays))
	{
		std::cout << "Num of Plays : " << numOfPlays << std::endl;
	}


	cSong* songInUser = snotify.GetSong(listOfUsers[0].getSnotifyUniqueUserID(), songToUpdate->getUniqueID(), errorMsg);
	std::cout << (songInUser == nullptr ? errorMsg : songInUser->name )<< std::endl;

	if (snotify.GetCurrentSongNumberOfPlays(listOfUsers[0].getSnotifyUniqueUserID(), songToUpdate->getUniqueID(), numOfPlays))
	{
		std::cout << "Num of Plays : " << numOfPlays << std::endl;
	}

	snotify.AddSongToUserLibrary(listOfUsers[0].getSnotifyUniqueUserID(), musicGenerator.getRandomSong(), errorMsg);
	snotify.AddSongToUserLibrary(listOfUsers[0].getSnotifyUniqueUserID(), musicGenerator.getRandomSong(), errorMsg);
	snotify.AddSongToUserLibrary(listOfUsers[0].getSnotifyUniqueUserID(), musicGenerator.getRandomSong(), errorMsg);


	cSong* songArray = nullptr;
	unsigned int sizeOfSongArray = 0;
	snotify.GetUsersSongLibrary(listOfUsers[0].getSnotifyUniqueUserID(), songArray, sizeOfSongArray);
	snotify.GetUsersSongLibraryAscendingByTitle(listOfUsers[0].getSnotifyUniqueUserID(), songArray, sizeOfSongArray);

	for (int i = 0; i < sizeOfSongArray; i++)
	{
		std::cout << "Song : " << songArray[i].name << std::endl;
	}

	if (!snotify.RemoveSongFromUserLibrary(listOfUsers[0].getSnotifyUniqueUserID(), songToUpdate->getUniqueID(), errorMsg))
	{
		std::cout << errorMsg << std::endl;
	}

	songInUser = snotify.GetSong(listOfUsers[0].getSnotifyUniqueUserID(), songToUpdate->getUniqueID(), errorMsg);
	std::cout << (songInUser == nullptr ? errorMsg : songInUser->name) << std::endl;

	snotify.UpdateRatingOnSong(listOfUsers[0].getSnotifyUniqueUserID(), songToUpdate->getUniqueID(), 3);

	songToUpdate = musicGenerator.getRandomSong();

	songToUpdate->setUniqueID(uniqueId);

	snotify.UpdateSong(songToUpdate, errorMsg);

	std::cout << "Updated Song : " << snotify.FindSong(uniqueId)->name << std::endl;

	

	snotify.DeleteSong(uniqueId, errorMsg);


	return -1;
}