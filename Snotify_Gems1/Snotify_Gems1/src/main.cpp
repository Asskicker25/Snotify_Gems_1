#include <iostream>

#include "Containers/SmartArray.h"
#include "Containers/LinkedList.h"
#include "cPersonGenerator.h"
#include "cMusicGenerator.h"
#include "Profiler.h"

using namespace Containers;

int main(int argc, char* argv[])
{
	cPersonGenerator personGenerator;
	cMusicGenerator musicGenerator;

	std::string errorMsg;
	
	personGenerator.LoadCensusFiles(
		"Assets/BabyName/yob2019.txt", 
		"Assets/Surname/Names_2010Census.csv",
		"Assets/StreetName/Street_Names.csv", errorMsg);


	Profiler profiler;

	profiler.StartTimer();
	musicGenerator.LoadMusicInformation("Assets/Billboard/hot_stuff_2.csv", errorMsg);
	profiler.EndTimer();

	std::cout << profiler.GetElapsedTime() << std::endl;

	/*for (int i = 0; i < 20; i++)
	{
		cSong* newSong = musicGenerator.getRandomSong();
		std::cout << "Name : " << newSong->name << std::endl;
	}*/

	return -1;
}