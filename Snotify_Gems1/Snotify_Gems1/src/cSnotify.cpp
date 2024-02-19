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
	unsigned int nodeIndex = 0;

	GetSongWithId(uniqueID, songInList, nodeIndex, errorMsg);

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
	mListOfUsers.insertBeforeCurrent(pPerson);
	mListOfUserNodes.addAtEnd(mListOfUsers.getCurrentNode());

	return true;
}

bool cSnotify::UpdateUser(cPerson* pPerson, std::string& errorString)
{
	cPerson* personInList = nullptr;
	unsigned int nodeIndex = 0;

	if (GetUserWithId(pPerson->getSnotifyUniqueUserID(), personInList, nodeIndex, errorString))
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
	unsigned int nodeIndex = 0;

	if (GetUserWithId(SnotifyUserID, personInList, nodeIndex, errorString))
	{
		mListOfUserNodes.removeAt(nodeIndex);
		mListOfUsers.deleteAtCurrent();
		return true;
	}

	return false;
}

bool cSnotify::AddSong(cSong* pSong, std::string& errorString)
{

	mListOfSongs.insertBeforeCurrent(pSong);
	mListOfSongNodes.addAtEnd(mListOfSongs.getCurrentNode());

	return true;
}

bool cSnotify::UpdateSong(cSong* pSong, std::string& errorString)
{
	cSong* songInList = nullptr;
	unsigned int nodeIndex = 0;

	if (GetSongWithId(pSong->getUniqueID(), songInList, nodeIndex, errorString))
	{
		mListOfSongs.updateCurrent(pSong);
		return true;

	}

	return false;
}

bool cSnotify::DeleteSong(unsigned int UniqueSongID, std::string& errorString)
{
	cSong* songInList = nullptr;
	unsigned int nodeIndex = 0;

	if (GetSongWithId(UniqueSongID, songInList, nodeIndex, errorString))
	{
		mListOfSongNodes.removeAt(nodeIndex);
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

	for (int i = 0; i < sizeOfUserArray; i++)
	{
		pAllTheUsers[i] = *mListOfUserNodes.getAt(i)->mData;
	}

	return true;

	/*sizeOfUserArray = mListOfUsers.getSize();

	if (sizeOfUserArray == 0) return false;

	pAllTheUsers = new cPerson[sizeOfUserArray];

	mListOfUsers.moveToLast();

	unsigned int index = 0;

	do
	{
		pAllTheUsers[index] = *mListOfUsers.getCurrent();

		index++;

	} while (mListOfUsers.movePrevious());


	return true;*/
}

bool cSnotify::GetUserWithId(unsigned int uniqueId, cPerson*& outPerson, unsigned int& nodeIndex, std::string& errorString )
{
	unsigned int size = mListOfUsers.getSize();

	if (size == 0) return false;

	for (int i = 0; i < size; i++)
	{
		outPerson = mListOfUserNodes.getAt(i)->mData;

		if (outPerson->getSnotifyUniqueUserID() == uniqueId)
		{
			mListOfUsers.setCurrentNode(mListOfUserNodes.getAt(i));
			nodeIndex = i;
			return true;
		}
	}

	outPerson = nullptr;

	//cPerson* iteratedPerson;
	//mListOfUsers.moveToFirst();

	//do
	//{
	//	iteratedPerson = mListOfUsers.getCurrent();

	//	if (iteratedPerson->getSnotifyUniqueUserID() == uniqueId)
	//	{
	//		outPerson = iteratedPerson;

	//		return true;
	//	}

	//} while (mListOfUsers.moveNext());

	errorString = "Matching User not found";

	return false;
}

bool cSnotify::GetSongWithId(unsigned int uniqueId, cSong*& outSong, unsigned int& nodeIndex, std::string& errorString)
{
	unsigned int size = mListOfSongs.getSize();

	if (size == 0) return false;

	for (int i = 0; i < size; i++)
	{
		outSong = mListOfSongNodes.getAt(i)->mData;

		if (outSong->getUniqueID() == uniqueId)
		{
			mListOfSongs.setCurrentNode(mListOfSongNodes.getAt(i));
			nodeIndex = i;
			return true;
		}
	}

	outSong = nullptr;

	//cSong* iteratedSong;
	//mListOfSongs.moveToFirst();

	//do
	//{
	//	iteratedSong = mListOfSongs.getCurrent();

	//	if (iteratedSong->getUniqueID() == uniqueId)
	//	{
	//		outSong = iteratedSong;

	//		return true;
	//	}

	//} while (mListOfSongs.moveNext());

	errorString = "Matching Song not found";

	return false;
}
