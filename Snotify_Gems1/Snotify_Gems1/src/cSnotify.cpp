#include <iostream>
#include "Profiler.h"
#include "cSnotify.h"
#include "cMusicGenerator.h"
#include "Containers/SortUtils.h"

bool AscendingSongName(cSong a, cSong b)
{
	char lhs = a.name.c_str()[0];
	char rhs = b.name.c_str()[0];

	return lhs < rhs;
}

bool AscendingArtistName(cSong a, cSong b)
{
	char lhs = a.artist.c_str()[0];
	char rhs = b.artist.c_str()[0];

	return lhs < rhs;
}



cSnotify::cSnotify()
{
}

cSnotify::~cSnotify()
{
}

cSong* cSnotify::FindSong(std::string title, std::string artist)
{
	unsigned int hashId = cMusicGenerator::Hashing((title + artist).c_str());

	return FindSong(hashId);
}

cSong* cSnotify::FindSong(unsigned int uniqueID)
{
	cSong* songInList = nullptr;
	std::string errorMsg;

	GetSongWithId(uniqueID, songInList, errorMsg);

	return songInList;
}

bool cSnotify::GetUsersSongLibrary(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	cUser* user = nullptr;
	std::string errorMsg;

	if (GetUserWithId(snotifyUserID, user, errorMsg))
	{
		user->GetPlaylist(pLibraryArray, sizeOfLibary);

		return true;
	}
	return false;
}

bool cSnotify::GetUsersSongLibraryAscendingByTitle(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	if (GetUsersSongLibrary(snotifyUserID, pLibraryArray, sizeOfLibary))
	{
		Sorting::QuickSort<cSong>(&pLibraryArray[0], 0, sizeOfLibary - 1, AscendingSongName);
		return true;
	}
	return false;
}

bool cSnotify::GetUsersSongLibraryAscendingByArtist(unsigned int snotifyUserID, cSong*& pLibraryArray, unsigned int& sizeOfLibary)
{
	if (GetUsersSongLibrary(snotifyUserID, pLibraryArray, sizeOfLibary))
	{
		Sorting::QuickSort<cSong>(&pLibraryArray[0], 0, sizeOfLibary - 1, AscendingArtistName);
		return true;
	}
	return false;
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
		if (userInList->AddSong(pNewSong))
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
	cUserSong* userSong = nullptr;
	if (GetUserSongWithId(SnotifyUserID, songUniqueID, userSong))
	{
		userSong->rating = newRating;
		return true;
	}

	return false;
}

cSong* cSnotify::GetSong(unsigned int SnotifyUserID, unsigned int songUniqueID, std::string& errorString)
{
	cUserSong* userSong = nullptr;
	if (GetUserSongWithId(SnotifyUserID, songUniqueID, userSong))
	{
		userSong->numberOfTimesPlayed++;
		return userSong->mSong;
	}

	errorString = "Song not found in playlist.";

	return nullptr;

}

bool cSnotify::GetCurrentSongRating(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& songRating)
{

	cUserSong* userSong = nullptr;
	if (GetUserSongWithId(snotifyUserID, songUniqueID, userSong))
	{
		songRating = userSong->rating;
		return true;
	}

	return false;

}

bool cSnotify::GetCurrentSongNumberOfPlays(unsigned int snotifyUserID, unsigned int songUniqueID, unsigned int& numberOfPlays)
{

	cUserSong* userSong = nullptr;
	if (GetUserSongWithId(snotifyUserID, songUniqueID, userSong))
	{
		numberOfPlays = userSong->numberOfTimesPlayed;
		return true;
	}

	return false;
}

cPerson* cSnotify::FindUserBySIN(unsigned int SIN)
{
	if (mListOfUsers.getSize() == 0) return nullptr;

	cUser* iteratedUser;
	mListOfUsers.moveToFirst();

	do
	{
		iteratedUser = mListOfUsers.getCurrent();

		if (iteratedUser->mPerson->SIN == SIN)
		{
			return iteratedUser->mPerson;
		}

	} while (mListOfUsers.moveNext());


	return nullptr;
}

cPerson* cSnotify::FindUserBySnotifyID(unsigned int SnotifyID)
{
	cUser* user = nullptr;
	std::string errorMssg;

	if (GetUserWithId(SnotifyID, user, errorMssg))
	{
		return user->mPerson;
	}

	return nullptr;
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

bool cSnotify::GetUserSongWithId(unsigned int userID, unsigned int songID, cUserSong*& userSong)
{
	cUser* userInList = nullptr;
	std::string errorString;

	if (GetUserWithId(userID, userInList, errorString))
	{
		unsigned int index;
		if (userInList->FindSong(songID, userSong, index))
		{
			return true;
		}

		std::cout << "Song not found in user playlist." << std::endl;
	}

	return false;
}
