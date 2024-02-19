#include <iostream>
#include "cSnotify.h"


#include "cPersonGenerator.h"
#include "cMusicGenerator.h"

using namespace Containers;

void PrintMainMenu();
void PrintUserHandling();
void PrintSongHandling();
void PrintUserPlaylistHandling();
void PrintPersonInfo(cPerson& person);
void PrintErrorMessage(std::string& errorMsg);

unsigned int input;
unsigned int sizeOfArray;
std::string errorMsg;
std::string inputString;
cPerson* person;

cSnotify snotify;
cPersonGenerator personGenerator;
cMusicGenerator musicGenerator;

int main(int argc, char* argv[])
{

	personGenerator.LoadCensusFiles(
		"Assets/BabyName/yob2019.txt",
		"Assets/Surname/Names_2010Census.csv",
		"Assets/StreetName/Street_Names.csv", errorMsg);

	musicGenerator.LoadMusicInformation("Assets/Billboard/hot_stuff_2 - Copy.csv", errorMsg);

	do
	{
		PrintMainMenu();

		switch (input)
		{
		case 1:
			PrintUserHandling();
			break;
		case 2:
			PrintSongHandling();
			break;
		case 3:
			PrintUserPlaylistHandling();
			break;
		}



	} while (true);
}

void PrintMainMenu()
{

	do
	{
		printf("\n**** Main Menu ****\n\n");

		printf("1. User Handling\n");
		printf("2. Song Handling\n");
		printf("3. User Playlist Handling\n\n");
		printf("Enter Selection : ");

		std::cin >> input;

		printf("\n");

	} while (input < 1 && input > 3);

}



void PrintUserHandling()
{
	do
	{

		printf("**** User Handling ****\n\n");

		printf("1. Add Random User\n");
		printf("2. Update User\n");
		printf("3. Delete User\n");
		printf("4. Find User By SIN\n");
		printf("5. Find User By SnotifyID\n");
		printf("6. Get All Users\n");
		printf("7. Get All Users Ascending by SnotifyID\n");
		printf("8. Find Users With First Name\n");
		printf("9. Find Users With Last Name\n");
		printf("10. Find Users With Last and Last Name\n");

		printf("\nEnter Selection : ");

		std::cin >> input;

		printf("\n");

	} while (input < 1 && input > 10);


	switch (input)
	{
	case 1:
		printf("Number of Users To Add : ");
		std::cin >> input;
		printf("\n");

		for (int i = 0; i < input; i++)
		{
			person = personGenerator.generateRandomPerson();
			snotify.AddUser(person, errorMsg);
			PrintPersonInfo(*person);
			printf("\n");
		}

		break;
	case 2:
		person = personGenerator.generateRandomPerson();

		printf("User Snotify ID To Update  : ");
		std::cin >> input;
		//printf("\n");

		person->setSpotifyUniqueUserId(input);

		printf("User SIN To Update  : ");
		std::cin >> input;
		printf("\n");

		person->SIN = input;

		if (!snotify.UpdateUser(person, errorMsg))
		{
			PrintErrorMessage(errorMsg);
		}
		else
		{
			printf("Person Updated Successfully !!!\n ");

			PrintPersonInfo(*person);
		}

		break;
	case 3:

		printf("User Snotify ID To Delete  : ");
		std::cin >> input;
		printf("\n");

		if (snotify.DeleteUser(input, errorMsg))
		{
			printf("User Deleted Successfully !!!\n");
		}
		else
		{
			PrintErrorMessage(errorMsg);
		}

		break;
	case 4:

		printf("Find User By SIN : ");
		std::cin >> input;
		printf("\n");

		person = snotify.FindUserBySIN(input);
		if (person != nullptr)
		{
			PrintPersonInfo(*person);
		}
		else
		{
			printf("No User Found With the SIN\n");
		}

		break;
	case 5:
		printf("Find User By Snotify ID : ");
		std::cin >> input;
		printf("\n");

		person = snotify.FindUserBySnotifyID(input);
		if (person != nullptr)
		{
			PrintPersonInfo(*person);
		}
		else
		{
			printf("No User Found With the Snotify ID\n");
		}

		break;
	case 6:

		if (snotify.GetUsers(person, sizeOfArray))
		{
			for (int i = 0; i < sizeOfArray; i++)
			{
				PrintPersonInfo(person[i]);
				printf("\n");
			}
		}
		else
		{
			printf("No Users added.\n");
		}

		break;

	case 7:

		if (snotify.GetUsersByID(person, sizeOfArray))
		{
			for (int i = 0; i < sizeOfArray; i++)
			{
				PrintPersonInfo(person[i]);
				printf("\n");
			}
		}
		else
		{
			printf("No Users added.\n");
		}

		break;
	case 8:

		printf("Find User By First Name : ");
		std::cin >> inputString;
		printf("\n");

		if (snotify.FindUsersFirstName(inputString, person, sizeOfArray))
		{
			for (int i = 0; i < sizeOfArray; i++)
			{
				PrintPersonInfo(person[i]);
				printf("\n");
			}
		}
		else
		{
			printf("No Users added.\n");
		}

		break;
	case 9:+

		printf("Find User By Last Name : ");
		std::cin >> inputString;
		printf("\n");

		if (snotify.FindUsersLastName(inputString, person, sizeOfArray))
		{
			for (int i = 0; i < sizeOfArray; i++)
			{
				PrintPersonInfo(person[i]);
				printf("\n");
			}
		}
		else
		{
			printf("No Users added.\n");
		}
		break;
	case 10:
		printf("Find User By First Name : ");
		std::cin >> inputString;

		printf("Find User By Last Name : ");
		std::cin >> errorMsg;
		printf("\n");


		if (snotify.FindUsersFirstLastNames(inputString,errorMsg, person, sizeOfArray))
		{
			for (int i = 0; i < sizeOfArray; i++)
			{
				PrintPersonInfo(person[i]);
				printf("\n");
			}
		}
		else
		{
			printf("No Users added.\n");
		}

		break;
	}
}

void PrintSongHandling()
{
}

void PrintUserPlaylistHandling()
{
}

void PrintPersonInfo(cPerson& person)
{
	std::string fullName = (person.first + " " + person.middle + " " + person.last);
	unsigned int snotifyId = person.getSnotifyUniqueUserID();
	unsigned int SIN = person.SIN;

	printf("Name : %s\n", fullName.c_str());
	printf("Snotify ID : %d\n", snotifyId);
	printf("SIN : %d\n", SIN);

}

void PrintErrorMessage(std::string& errorMsg)
{
	printf("ERROR : %s\n", errorMsg.c_str());

}
