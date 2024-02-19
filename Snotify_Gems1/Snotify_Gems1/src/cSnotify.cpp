#include <iostream>
#include "Profiler.h"
#include "cSnotify.h"

//// This returns a COPY of the users library, in the form of a regular dynamic array.
//bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary);
//{
//	// The caller would do something like this (assume the user ID = 28472382)
//	//
//	//	cSong* pTheSongs = 0;
//	//	unsigned int arraySize = 0;
//	//	GetUsersSongLibrary( 28472382, pTheSongs, arraySize );
//	// 
//	// Inside this method, you'd do something like this:
//
//	// TODO: Find that user... 
//
//	// Alloate a heap based array to hold all the songs...
//
////	sizeOfLibary = WhateverYouHaveToDoToGetThisValue();
////	pCopyOfLibrary = new cSong[sizeOfLibary];
//
//	// The array and the size of the array are "returned" by reference to the caller. 
//
//	// TODO: Copy all the songs over
//
//	return true;
//}

cSong* cSnotify::FindSong(unsigned int uniqueID)
{
	cSong* songInList = nullptr;
	std::string errorMsg;

	GetSongWithId(uniqueID, songInList, errorMsg);

	return songInList;
}

bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	return false;
}



cSnotify::cSnotify()
{
}

cSnotify::~cSnotify()
{
}

bool cSnotify::AddUser(cPerson* pPerson, std::string& errorString)
{
	mListOfUsers.insertBeforeCurrent(new cUser(pPerson));

	return true;
}

bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{
	cUser* userInList = nullptr;
	if (GetUserWithId(pPerson->getSnotifyUniqueUserID(), userInList, errorString))
	{
		if (userInList->mPerson->SIN == pPerson->SIN)
		{
			delete userInList->mPerson;

			userInList->mPerson = pPerson;

			return true;
		}
	}

	return false;
}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	cUser* userInList = nullptr;
	if (GetUserWithId(SnotifyUserID, userInList, errorString))
	{
		mListOfUsers.deleteAtCurrent();
		return true;
	}

	return false;
}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{

	mListOfSongs.insertBeforeCurrent(pSong);
	return true;
}

bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString)
{
	cSong* songInList = nullptr;
	if (GetSongWithId(pSong->getUniqueID(), songInList, errorString))
	{
		mListOfSongs.updateCurrent(pSong);
		return true;

	}

	return false;
}

bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString)
{
	cSong* songInList = nullptr;
	if (GetSongWithId(UniqueSongID, songInList, errorString))
	{
		mListOfSongs.deleteAtCurrent();
		return true;

	}

	return false;

}

bool cSnotify::AddSongToUserLibrary(unsigned int snotifyUserID, cSong* pNewSong, std::string& errorString)
{
	cUser* userInList = nullptr;
	if (GetUserWithId(snotifyUserID, userInList, errorString))
	{
		if(userInList->AddSong(pNewSong))
		{
			return true;
		}
		else
		{
			errorString = "Can't add song. It already exists in playlist.";
		}
	}

	return false;
}

bool cSnotify::RemoveSongFromUserLibrary(unsigned int snotifyUserID, unsigned int SnotifySongID, std::string& errorString)
{
	cUser* userInList = nullptr;
	if (GetUserWithId(snotifyUserID, userInList, errorString))
	{
		if (userInList->RemoveSong(SnotifySongID))
		{
			return true;
		}
		else
		{
			errorString = "Can't remove song. It doesn't exist in playlist.";
		}
	}

	return false;
}

bool cSnotify::UpdateRatingOnSong(unsigned int SnotifyUserID, unsigned int songUniqueID, unsigned int newRating)
{
	cUser* userInList = nullptr;
	std::string errorString;

	if (GetUserWithId(SnotifyUserID, userInList, errorString))
	{
		cUserSong* userSong = nullptr;
		unsigned int index;

		if (userInList->FindSong(songUniqueID, userSong, index))
		{
			userSong->rating = newRating;
			return true;
		}
	
		std::cout << "Can't update rating. Song not found in playlist." << std::endl;
	}

	return false;
}

bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	sizeOfUserArray = mListOfUsers.getSize();

	if (sizeOfUserArray == 0) return false;

	pAllTheUsers = new cPerson[sizeOfUserArray];

	mListOfUsers.moveToLast();

	unsigned int index = 0;

	do
	{
		pAllTheUsers[index] = *mListOfUsers.getCurrent()->mPerson;

		index++;

	} while (mListOfUsers.movePrevious());


	return true;
}

bool cSnotify::GetUserWithId(unsigned int uniqueId, cUser*& outUser, std::string& errorString)
{
	if (mListOfUsers.getSize() == 0) return false;

	cUser* iteratedUser;
	mListOfUsers.moveToFirst();

	do
	{
		iteratedUser = mListOfUsers.getCurrent();

		if (iteratedUser->mPerson->getSnotifyUniqueUserID() == uniqueId)
		{
			outUser = iteratedUser;

			return true;
		}

	} while (mListOfUsers.moveNext());

	errorString = "Matching User not found";

	return false;
}

bool cSnotify::GetSongWithId(unsigned int uniqueId, cSong*& outSong, std::string& errorString)
{
	if (mListOfSongs.getSize() == 0) return false;

	cSong* iteratedSong;
	mListOfSongs.moveToFirst();

	do
	{
		iteratedSong = mListOfSongs.getCurrent();

		if (iteratedSong->getUniqueID() == uniqueId)
		{
			outSong = iteratedSong;

			return true;
		}

	} while (mListOfSongs.moveNext());

	errorString = "Matching Song not found";

	return false;
}
