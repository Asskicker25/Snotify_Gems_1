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
	cPerson* personToUpdate;
	mListOfUsers.moveToFirst();

	do
	{
		personToUpdate = mListOfUsers.getCurrent();

		if (personToUpdate->getSnotifyUniqueUserID() == pPerson->getSnotifyUniqueUserID()
			&& personToUpdate->SIN == pPerson->SIN)
		{
			mListOfUsers.updateCurrent(pPerson);

			delete personToUpdate;

			return true;
		}

	} while (mListOfUsers.moveNext());

	errorString = "Matching User not found";

	return false;
}

bool cSnotify::DeleteUser(unsigned int SnotifyUserID, std::string& errorString)
{
	int size = mListOfUsers.getSize();

	cPerson* personToUpdate;
	mListOfUsers.moveToFirst();

	do
	{
		personToUpdate = mListOfUsers.getCurrent();

		if (personToUpdate->getSnotifyUniqueUserID() == SnotifyUserID)
		{
			mListOfUsers.deleteElement(personToUpdate);
			return true;
		}

	} while (mListOfUsers.moveNext());

	errorString = "Matching User not found";

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