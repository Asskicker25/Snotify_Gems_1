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
	int size = mListOfUsers.getSize();

	Node<cPerson*>* currentNode;
	cPerson* personToUpdate;

	for (int i = 0; i < size; i++)
	{
		currentNode = mListOfUsers.mListOfNodes.getAt(i);
		personToUpdate = currentNode->mData;

		if (personToUpdate->getSnotifyUniqueUserID() == pPerson->getSnotifyUniqueUserID()
			&& personToUpdate->SIN == pPerson->SIN)
		{
			delete currentNode->mData;

			currentNode->mData = pPerson;
				return true;
		}
	}


	return false;
}


bool cSnotify::GetUsers(cPerson*& pAllTheUsers, unsigned int& sizeOfUserArray)
{
	if (sizeOfUserArray == 0) { return false; }

	int size = mListOfUsers.getSize();

	if(sizeOfUserArray < size) { return false; }

	pAllTheUsers = new cPerson[sizeOfUserArray];

	std::cout << "Array Iteration " << std::endl;
	TIMER_CALL(
		Node<cPerson*>*currentNode;

	for (int i = 0; i < sizeOfUserArray; i++)
	{
		currentNode = mListOfUsers.mListOfNodes.getAt(i);
		pAllTheUsers[i] = *currentNode->mData;

	}
	);


	//pAllTheUsers = new cPerson[sizeOfUserArray];

	//std::cout << "List Iteration " << std::endl;

	//TIMER_CALL(

	//	mListOfUsers.moveToFirst();

	//	int index = 0;

	//	do
	//	{
	//		pAllTheUsers[index] = *mListOfUsers.getCurrent();

	//		index++;

	//	} while (mListOfUsers.moveNext() && index < sizeOfUserArray);
	//);


	return true;
}