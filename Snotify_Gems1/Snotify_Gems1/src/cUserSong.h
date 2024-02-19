#pragma once

#include "cSong.h"

class cUserSong
{

public:
	cUserSong() = default;
	cUserSong(unsigned int id) : mSongUniqueId{ id } {}

	unsigned int mSongUniqueId;
	//cSong* mSong;
	int rating = 0;
	int numberOfTimesPlayed = 0;
};

