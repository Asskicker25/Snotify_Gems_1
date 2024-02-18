#ifndef _cMusicGenerator_HG_
#define _cMusicGenerator_HG_

#include <string>
#include "cSong.h"

#include "Containers/SmartArray.h"

using namespace Containers;

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
	
	SmartArray<cSong*> mListOfSongs;

};

#endif
