#ifndef _cMusicGenerator_HG_
#define _cMusicGenerator_HG_

#include <string>
#include "cSong.h"

#include "Containers/SmartArray.h"
#include "HashMap.h"

using namespace Containers;

struct MyKeyHash {
	unsigned long operator()(const std::string& k) const
	{
		unsigned int hash = 5381;
		int c;
		const char* str = k.c_str();

		while ((c = *str++)) {
			hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		}

		return hash;
	}
};


class cMusicGenerator
{
public:
	cMusicGenerator();
	~cMusicGenerator();

	bool LoadMusicInformation(std::string musicFileName, std::string& errorString);

	cSong* getRandomSong(void);
	
	// Returns 0, NULL, or nullptr if no song is found
	// This must be an EXACT MATCH for what's in the billboard100 file. 
	// So case sensitive, etc. 
	cSong* findSong(std::string songName, std::string artist);

private:

	void AddSong(const std::string& songName, const std::string& artist);
	int GetRandomIntNumber(int minValue, int maxValue);
	bool IsDuplicate(const std::string& songName,const  std::string& artist);
	unsigned int Hashing(const char* str);
	
	//SmartArray<cSong*> mListOfSongs;
	HashMap<std::string, cSong*, MyKeyHash> mListOfSongs;
};

#endif
