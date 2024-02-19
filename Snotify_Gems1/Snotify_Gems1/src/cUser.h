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

	bool AddSong(cSong* song);
	bool RemoveSong(unsigned int songUniqueId);
	bool FindSong(unsigned int songUniqueId, cUserSong*& song, unsigned int& index);

	cPerson* mPerson;

private:
	SmartArray<cUserSong*> mPlaylist;

	 
};

