//Main class for the game board used in game.

#include "Board.h"
#include "Card.h"
#include "UserBase.h"
#include "pch.h"

//Replaces card selection with presets for upcoming match
void Board::selectCharacter()
{

}

void Board::startBotGame()
{
	cout << flush;
	system("CLS");
	Card botVs;
	botVs.generateDeck(1);
	botVs.generateDeck(3);

	while (1)
	{
		botVs.fillPlayer1Hand();
		botVs.fillBotHand();
		botVs.placeGenericCard(1);

		if (botVs.allTotal(1) < 1)
		{
			cout << flush;
			system("CLS");
			botVs.endGame(1);
			break;
		}
	}
}

//Primative Player vs Player gamemode can be improved to have the same style as player vs bot
void Board::startVSGame()
{
	cout << flush;
	system("CLS");
	Card playerVs;
	playerVs.generateDeck(1);
	playerVs.generateDeck(2);

	while (1)
	{
		playerVs.fillPlayer1Hand();
		playerVs.fillPlayer2Hand();
		playerVs.placeGenericCard(2);

		if (playerVs.allTotal(2) < 1)
		{
			cout << flush;
			system("CLS");
			playerVs.endGame(2);
			break;
		}
	}
}

void Board::testArea()
{
	Card test;
	test.testPlayer();
	test.endGame(2);
}