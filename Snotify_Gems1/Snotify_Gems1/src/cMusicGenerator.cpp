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
	if (LoadFromCSV(musicFileName, errorString))
	{
		//SortSongs();
		//DeleteDuplicates();
		std::cout << "Size : " << mListOfSongs.getSize() << std::endl;

		/*for (int i = 0; i < mListOfSongs.getSize(); i++)
		{
			std::cout << mListOfSongs.getAt(i)->name << std::endl;
		}*/

		return true;
	}
	return false;
}

cSong* cMusicGenerator::getRandomSong(void)
{
	return mListOfSongs.getAt(GetRandomIntNumber(0, mListOfSongs.getSize()));
}

cSong* cMusicGenerator::findSong(std::string songName, std::string artist)
{
	unsigned int hashValue = Hashing((songName + artist).c_str());

	for (int i = 0; i < mListOfSongs.getSize(); i++)
	{
		if (mListOfSongs.getAt(i)->getUniqueID() == hashValue)
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

bool cMusicGenerator::LoadFromCSV(std::string musicFileName, std::string& errorString)
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

		/*if (!IsDuplicate(songName, artist))
		{
		}*/
		AddSong(songName, artist);

	}
	std::cout << "Line : " << lineCount << std::endl;
	return true;
}

void cMusicGenerator::AddSong(const std::string& songName, const std::string& artist)
{
	unsigned int hashValue = Hashing((songName + artist).c_str());

	if (!IsDuplicate(hashValue))
	{
		cSong* newSong = new cSong();

		newSong->name = songName;
		newSong->artist = artist;
		newSong->uniqueID = hashValue;

		mListOfSongs.addAtEnd(newSong);
		mSongHashValues.addAtEnd(hashValue);
	}
}

unsigned int cMusicGenerator::Hashing(const char* str)
{
	unsigned int hash = 5381;
	int c;

	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash;
}

void cMusicGenerator::DeleteDuplicates()
{
	SmartArray<int> indicesToRemove;

	int n = mListOfSongs.getSize() - 1;
	for (int i = 0; i < n; i++)
	{
		if (mListOfSongs.getAt(i)->getUniqueID() == mListOfSongs.getAt(i + 1)->getUniqueID())
		{
			indicesToRemove.addAtEnd(i);
		}
	}

	for (int i = 0; i < indicesToRemove.getSize(); i++)
	{
		mListOfSongs.removeAt(indicesToRemove.getAt(i) - (i));
	}
}

bool cMusicGenerator::IsDuplicate(unsigned int hashValue)
{
	unsigned int size = mSongHashValues.getSize();

	for (int i = 0; i < size; i++)
	{
		if (mSongHashValues.getAt(i) == hashValue)
		{
			return true;
		}
	}

	return false;
}

void cMusicGenerator::SortSongs()
{
	QuickSort(mListOfSongs, 0, mListOfSongs.getSize() - 1);
}

void cMusicGenerator::QuickSort(SmartArray<cSong*>& songs, int low, int high)
{
	if (low < high)
	{
		int pivot = QuickSortPartition(songs, low, high);
		QuickSort(songs, low, pivot - 1);
		QuickSort(songs, pivot + 1, high);
	}
}


int cMusicGenerator::QuickSortPartition(SmartArray<cSong*>& songs, int low, int high)
{
	int pivot = songs.getAt(high)->getUniqueID();
	int i = low - 1;

	for (int j = low; j < high; j++)
	{
		if (songs.getAt(j)->getUniqueID() < pivot)
		{
			i++;

			cSong* temp = songs.getAt(i);
			songs.addAtIndex(i, songs.getAt(j));
			songs.addAtIndex(j, temp);
		}
	}

	cSong* temp = songs.getAt(i + 1);
	songs.addAtIndex(i + 1, songs.getAt(high));
	songs.addAtIndex(high, temp);

	return i + 1;
}