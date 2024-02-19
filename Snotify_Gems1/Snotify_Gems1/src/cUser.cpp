#include "cUser.h"

bool cUser::AddSong(cSong* song)
{
	cUserSong* songInList;
	unsigned int index;

	if (!FindSong(song->getUniqueID(), songInList, index))
	{
		mPlaylist.addAtEnd(new cUserSong(song));
		return true;
	}

	return false;
}

bool cUser::RemoveSong(unsigned int songUniqueId)
{
	cUserSong* songInList;
	unsigned int index;

	if (FindSong(songUniqueId, songInList, index))
	{
		mPlaylist.removeAt(index);
		return true;
	}

	return false;
}

bool cUser::FindSong(unsigned int songUniqueId, cUserSong*& song, unsigned int& index)
{
	for (int i = 0; i < mPlaylist.getSize(); i++)
	{
		song = mPlaylist.getAt(i);

		if (song->mSong->getUniqueID() == songUniqueId)
		{
			index = i;
			return true;
		}
	}

	song = nullptr;

	return false;
}
