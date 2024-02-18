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
	mListOfUsers.insertBeforeCurrent(pPerson);

	return true;
}

bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{
	cPerson* personInList = nullptr;
	if (GetUserWithId(pPerson->getSnotifyUniqueUserID(), personInList, errorString))
	{
		if (personInList->SIN == pPerson->SIN)
		{
			mListOfUsers.updateCurrent(pPerson);

			delete personInList;

			return true;
		}
	}

	return false;
}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	cPerson* personInList = nullptr;
	if (GetUserWithId(SnotifyUserID, personInList, errorString))
	{
		mListOfUsers.deleteAtCurrent();
		return true;
	}

	return false;
}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{
	//So that deleting songs from spotify won't delete them from music generator
	/*cSong* newSong = new cSong();

	*newSong = *pSong;*/

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
		pAllTheUsers[index] = *mListOfUsers.getCurrent();

		index++;

	} while (mListOfUsers.movePrevious());


	return true;
}

bool cSnotify::GetUserWithId(unsigned int uniqueId, cPerson*& outPerson, std::string& errorString)
{
	cPerson* iteratedPerson;
	mListOfUsers.moveToFirst();

	do
	{
		iteratedPerson = mListOfUsers.getCurrent();

		if (iteratedPerson->getSnotifyUniqueUserID() == uniqueId)
		{
			outPerson = iteratedPerson;

			return true;
		}

	} while (mListOfUsers.moveNext());

	errorString = "Matching User not found";

	return false;
}

bool cSnotify::GetSongWithId(unsigned int uniqueId, cSong*& outSong, std::string& errorString)
{

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
