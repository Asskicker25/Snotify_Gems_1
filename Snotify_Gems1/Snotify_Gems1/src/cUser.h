#pragma once

#include "cUserSong.h"
#include "cPerson.h"
#include "Containers/SmartArray.h"

using namespace Containers;

class cUser
{
public:
	cUser() = default;
	cUser(cPerson* person) : mPerson{ person } {}

	bool AddSong(unsigned int songId);
	bool RemoveSong(unsigned int songUniqueId);
	bool FindSong(unsigned int songUniqueId, unsigned int& index);
	bool GetPlaylist(cUserSong*& songIdArray, unsigned int& sizeOfArray);

	cPerson* mPerson;

private:
	SmartArray<cUserSong*> mPlaylist;

	 
};

