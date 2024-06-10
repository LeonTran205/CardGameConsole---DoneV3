// CardGameConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This is also the main menu of the game

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "pch.h"
#include <cstdlib>

#include "UserBase.h"
#include "Board.h"

using namespace std;

int main()
{
	int command = 0;
	Board b;

	while (command != -1)
	{
		//CIN validation to make sure that when ever anything that isnt an int would 
		//print out Invalid input and proceed to do nothing. Even if an int and string
		//are together it would input an invalid command.
		cout << "Use the following options to control this program" << endl;
		cout << "type -1 to exit" << endl;
		cout << "type 0 for Help" << endl;
		cout << "type 1 to Start Bot game" << endl;
		cout << "type 2 to Start Vs game" << endl;
		cout << "Type your options now" << endl;
		cin >> command;

		while (1)
		{
			if (cin.fail())
			{
				//Clear the input
				cin.clear();
				//Clearing any buffers before a new line
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << flush;
				system("CLS");
				cout << "Use the following options to control this program" << endl;
				cout << "type -1 to exit" << endl;
				cout << "type 0 for Help" << endl;
				cout << "type 1 to Start Bot game" << endl;
				cout << "type 2 to Start Vs game" << endl;
				cout << "Type your options now\n" << endl;
				cout << "Invalid Input" << endl;
				//Redo the input until a valid inpit has been used
				cin >> command;
			}
			//Once a valid input has been used break the while loop
			else if (!cin.fail()) break;
		}

		switch (command)
		{
		case (1): //Start a game aginst a bot
		{
			b.startBotGame();
			break;
		}

		case (2): //Start a game against 2nd player
		{
			b.startVSGame();
			break;
		}

		case (0): //Displays help or can be used as a test suit for function testing/debugging
		{
			cout << flush;
			system("CLS");
			cout << "This is a card game that will allow the player to go aginst a\nbot or player to play the game you must:\ngain as many points as possible to win a match." << endl;
			cout << "The Power Plus Card will add a point to the player.\nThe Power Down Card will take a point away from the opponent\nThe Steal Card will take the opponents card from their set and place it into player hand or if there is nothing add a\npoint to the player" << endl;
			cout << "However, there are other cards with different abilities" << endl;
			cout << "To play the game a player will get a randomly generated deck, and a hand with 5 cards pressing 0 - 4 will select a\nspecific card on hand\n"<<endl;
			cout << "Typing 1 will begin a game against a bot\nTyping 2 will begin a game against a player\nTyping -1 will quit game" << endl;
			cout << "After a game has finished an external file will output information about the previous gameplayed.\nHowever starting a new game will replace this file\n\n";

			//Remove the double slash before the b.testArea to begin debugging functions in the test function
			//Also testing file output
			//ofstream testFile;
			//testFile.open("testExample.txt");
			//testFile << "UwU said the man" << endl;
			//testFile << "\nThat's gross said his wife" << endl;
			//testFile.close();
			//b.testArea();
			break;
		}

		case (-1):
		{
			command = -1;
			break;
		}
		default:
		{
			cout << flush;
			system("CLS");
			cout << "Use the following options to control this program" << endl;
			cout << "type -1 to exit" << endl;
			cout << "type 0 for Help" << endl;
			cout << "type 1 to Start Bot game" << endl;
			cout << "type 2 to Start Vs game" << endl;
			cout << "Type your options now\n" << endl;
			cout << "Invalid Input" << endl;
			break;
		}
		
		}

	}
	cout << "Quitting game" << endl;
	return 0;
}