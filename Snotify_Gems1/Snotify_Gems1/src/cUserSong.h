#pragma once

#include "cSong.h"

class cUserSong
{

public:
	cUserSong() = default;
	cUserSong(cSong* song) : mSong{ song } {}

	cSong* mSong;
	int rating = 0;
	int numberOfTimesPlayed = 0;
};

