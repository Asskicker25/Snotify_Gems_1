#include <iostream>

#include "Containers/SmartArray.h"
#include "Containers/LinkedList.h"

using namespace Containers;

int main(int argc, char* argv[])
{

	LinkedList<int> mListOfInts;

	for (int i = 0; i < 10; i++)
	{
		mListOfInts.insertBeforeCurrent(i);
	}

	mListOfInts.moveToFirst();
	mListOfInts.clear();

	if (!mListOfInts.isEmpty())
	{
		do
		{
			std::cout << mListOfInts.getCurrent() << std::endl;

		} while (mListOfInts.moveNext());
	}

	return -1;
}