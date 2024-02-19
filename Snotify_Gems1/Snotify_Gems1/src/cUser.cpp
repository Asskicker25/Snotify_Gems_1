#include "cUser.h"

bool cUser::AddSong(unsigned int songId)
{
	unsigned int index;

	if (!FindSong(songId, index))
	{
		mPlaylist.addAtEnd(new cUserSong(songId));
		return true;
	}

	return false;
}

bool cUser::RemoveSong(unsigned int songUniqueId)
{
	unsigned int index;

	if (FindSong(songUniqueId, index))
	{
		mPlaylist.removeAt(index);
		return true;
	}

	return false;
}

bool cUser::FindSong(unsigned int songUniqueId, unsigned int& index)
{
	for (int i = 0; i < mPlaylist.getSize(); i++)
	{

		if (mPlaylist.getAt(i)->mSongUniqueId == songUniqueId)
		{
			index = i;
			return true;
		}
	}

	return false;
}

bool cUser::GetPlaylist(cUserSong*& songIdArray, unsigned int& sizeOfArray)
{
	sizeOfArray = mPlaylist.getSize();

	if (sizeOfArray == 0) return false;
	
	songIdArray = new cUserSong[sizeOfArray];

	cUserSong* iteratedSong = nullptr;

	for (int i = 0; i < sizeOfArray; i++)
	{
		iteratedSong = mPlaylist.getAt(i);
		songIdArray[i] = *iteratedSong;
		/*songIdArray[i].rating = iteratedSong->rating;
		songIdArray[i].numberOfTimesPlayed = iteratedSong->numberOfTimesPlayed;*/

	}

	return true;
}
