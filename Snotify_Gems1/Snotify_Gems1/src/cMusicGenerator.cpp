#include "cMusicGenerator.h"

#include <iostream>
#include <fstream>
#include <sstream>		// String Stream
#include <string>
#include <random>


cMusicGenerator::cMusicGenerator()
{
}

cMusicGenerator::~cMusicGenerator()
{
}

bool cMusicGenerator::LoadMusicInformation(std::string musicFileName, std::string& errorString)
{
	std::ifstream file(musicFileName);
	if (!file.is_open())
	{
		std::cout << "Didn't open file" << std::endl;
		return false;
	}

	std::string theLine;

	unsigned int lineCount = 0;
	while (std::getline(file, theLine))
	{

		lineCount++;
		std::stringstream ssLine(theLine);

		std::string value;
		unsigned int index = 0;

		if (lineCount == 1)
		{
			continue;
		}

		std::string songName, artist;

		while (std::getline(ssLine, value, ','))
		{
			if (index == 3)
			{
				songName = value;
			}
			else if (index == 4)
			{
				artist = value;
			}

			if (index > 4) continue;
			
			index++;
		}

		if (!IsDuplicate(songName, artist))
		{
			AddSong(songName, artist);
		}

	}
	std::cout << "Line : " << lineCount << std::endl;
	return true;
}

cSong* cMusicGenerator::getRandomSong(void)
{
	return mListOfSongs.getAt(GetRandomIntNumber(0,mListOfSongs.getSize()));
}

cSong* cMusicGenerator::findSong(std::string songName, std::string artist)
{
	for (int i = 0; i < mListOfSongs.getSize(); i++)
	{
		if (mListOfSongs.getAt(i)->name == songName && mListOfSongs.getAt(i)->artist == artist)
		{
			return mListOfSongs.getAt(i);
		}
	}

	return nullptr;
}

int cMusicGenerator::GetRandomIntNumber(int minValue, int maxValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(minValue, maxValue);

	return distribution(gen);
}

bool cMusicGenerator::IsDuplicate(const std::string& songName, const std::string& artist)
{
	for (int i = 0; i < mListOfSongs.getSize(); i++)
	{
		if (mListOfSongs.getAt(i)->name == songName && mListOfSongs.getAt(i)->artist == artist)
		{
			return true;
		}
	}

	return false;
}

void cMusicGenerator::AddSong(const std::string& songName, const std::string& artist)
{
	cSong* newSong = new cSong();
	
	newSong->name = songName;
	newSong->artist = artist;

	mListOfSongs.addAtEnd(newSong);
}
