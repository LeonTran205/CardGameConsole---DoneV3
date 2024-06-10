#include <iostream>
#include <fstream>

#include "Card.h"
#include "pch.h"
#include "UserBase.h"

using namespace std;

//Player types that would be used in the game

//Player 1 is the main player that is able to play against a bot or another player
UserBase player1("Player One");
//The bot that is used to play against the player
UserBase botPlayer("Bot");
//Player 2 is only used in vs mode where the player is against another player. However, due to a shared screen both players will see each others hand.
UserBase player2("Player Two");

//Initialise card class
Card::Card()
{
}

//Allows for testing of base game to see if game functionality is working (Currently displaying what was last tested 16/04/2020)
//Testing adding cards boards and the winning and losing feature as well as clearing everything for the next match.
void Card::testPlayer()
{
	player1.addPowerPlus();
	player1.addPowerDown();
	player1.addStealCard();
	player1.addPowerPlus();
	player1.addPowerDown();
	player1.addStealCard();

	player2.addPowerPlus();
	player2.addStealCard();

	player1.checkDeckSize();

	player1.takeCardFromDeck();
	player1.takeCardFromDeck();
	player1.takeCardFromDeck();

	cout << endl << "Player 1 hand:";
	player1.checkHand();
	cout << endl << "Player 1 deck:";
	player1.checkDeck();
	cout << endl << "Player 2 deck size:";
	player2.checkDeck();

	player1.placeCardOnBoard();
	cout << "Player 1 board side:";
	if (player1.getPlacedBoardCard() == "Power Plus") player1.addPoints(1);
	if (player1.getPlacedBoardCard() == "Power Down") player2.takePoints(1);
	if (player1.getPlacedBoardCard() == "Steal")
	{
		if (player2.checkTopDeck() == "Power Plus") player1.addPoints(1);
		if (player2.checkTopDeck() == "Power Down") player2.takePoints(1);
		//If steal card gets another steal card player gains extra points
		if (player2.checkTopDeck() == "Steal")player1.addPoints(2);
		player2.removeTopDeck();
	}
	player1.checkBoard();
	player1.checkPoints();

	player2.checkPoints();
	cout << endl << "Player 2 deck size:";
	player2.checkDeck();

	player1.clearAll();
	player1.clearBoard();
	player1.setPoints(0);
	player2.clearAll();
	player2.clearBoard();
	player2.setPoints(0);
}

//Generates a fresh deck with all cards completely random and the amount can change depending on the for loop.
//Originally the for loop is to loop 25 times for 20 cards in deck and 5 in hand but due to new cards being added to game
//Deck of 35/30 in deck and 5 cards in hand would provide for more chaos and randomness to game (no balance reguarded).
void Card::generateDeck(int player)
{
	//Initalise random counter
	int randomCardNumber;

	//For loop to give cards to player
	for (int i = 0; i < 35; i++)
	{

		randomCardNumber = rand() % 6;
		switch (randomCardNumber)
		{
			//If randomCardNumber is 0 then give the player a Power plus card
		case(0):
		{
			switch (player)
			{
			case(1):
			{
				player1.addPowerPlus();
				break;
			}

			case(2):
			{
				player2.addPowerPlus();
				break;
			}

			case(3):
			{
				botPlayer.addPowerPlus();
				break;
			}
			break;
			}
			break;
		}
		//If randomCardNumber is 1 then give the player a Power down card
		case(1):
		{
			switch (player)
			{
			case(1):
			{
				player1.addPowerDown();
				break;
			}

			case(2):
			{
				player2.addPowerDown();
				break;
			}

			case(3):
			{
				botPlayer.addPowerDown();
				break;
			}
			break;
			}
			break;

		}
		//If randomCardNumber is 2 then give the player a Steal card
		case(2):
		{

			switch (player)
			{
			case(1):
			{
				if (player == 1) player1.addStealCard();
			}

			case(2):
			{
				if (player == 2) player2.addStealCard();
			}

			case(3):
			{
				if (player == 3) botPlayer.addStealCard();
			}
			}
			break;
		}
		//If randomCardNumber is 2 then give the player a Steal card
		case(3):
		{

			switch (player)
			{
			case(1):
			{
				if (player == 1) player1.addClearBoard();
			}

			case(2):
			{
				if (player == 2) player2.addClearBoard();
			}

			case(3):
			{
				if (player == 3) botPlayer.addClearBoard();
			}
			}
			break;
		}
		//If randomCardNumber is 2 then give the player a Steal card
		case(4):
		{

			switch (player)
			{
			case(1):
			{
				if (player == 1) player1.addCardReturnCard();
			}

			case(2):
			{
				if (player == 2) player2.addCardReturnCard();
			}

			case(3):
			{
				if (player == 3) botPlayer.addCardReturnCard();
			}
			}
			break;
		}
		//If randomCardNumber is 2 then give the player a Steal card
		case(5):
		{

			switch (player)
			{
			case(1):
			{
				if (player == 1) player1.addWildCard();
			}

			case(2):
			{
				if (player == 2) player2.addWildCard();
			}

			case(3):
			{
				if (player == 3) botPlayer.addWildCard();
			}
			}
			break;
		}
		}
	}
}

//Fill the player hand when there's no cards in hand
void Card::fillPlayer1Hand()
{

	//If the deck is empty do nothing and print out "empty deck" instead of crashing and giving an error message
	if (player1.getDeckSize() < 1)
	{
		cout << "Player One Empty deck: Skipping Draw\n";
	}
	//Hand out the player 5 cards each time a hand is cleared
	else if (player1.getDeckSize() > 4 && player1.getHandSize() < 1)
	{
		player1.takeCardFromDeck();
		player1.takeCardFromDeck();
		player1.takeCardFromDeck();
		player1.takeCardFromDeck();
		player1.takeCardFromDeck();

	}
	//If there are less than 5 cards in deck give the player a single card each time
	else if (player1.getDeckSize() < 5 && player1.getHandSize() < 1)
	{
		player1.takeCardFromDeck();
	}
}

//Both the fillPlayer2Hand and fillBotHand() uses the same code as player 1 except the function works for the bot and player2.
void Card::fillPlayer2Hand()
{
	if (player2.getDeckSize() < 1)
	{
		cout << "\nPlayer Two Empty deck: Skipping Draw\n" << endl;
	}

	else if (player2.getDeckSize() > 4 && player2.getHandSize() < 1)
	{
		player2.takeCardFromDeck();
		player2.takeCardFromDeck();
		player2.takeCardFromDeck();
		player2.takeCardFromDeck();
		player2.takeCardFromDeck();
	}
	else if (player2.getDeckSize() < 5 && player2.getHandSize() < 1)
	{
		player2.takeCardFromDeck();
	}
}

void Card::fillBotHand()
{
	if (botPlayer.getDeckSize() < 1)
	{
		cout << "\nBot Empty deck: Skipping Draw\n" << endl;
	}

	else if (botPlayer.getDeckSize() > 4 && botPlayer.getHandSize() < 1)
	{
		botPlayer.takeCardFromDeck();
		botPlayer.takeCardFromDeck();
		botPlayer.takeCardFromDeck();
		botPlayer.takeCardFromDeck();
		botPlayer.takeCardFromDeck();
	}
	else if (botPlayer.getDeckSize() < 5 && botPlayer.getHandSize() < 1)
	{
		botPlayer.takeCardFromDeck();
	}
}

//Places assignment required cards down for play. (Main part of the game changes to this would affect the game heavily)
void Card::placeGenericCard(int mode)
{
	//Switch mode switches from Player vs Bot or Player vs player
	switch (mode)
	{
		//Player VS Bot
	case(1):
	{
		//Output the game into text file (WIP does not work correctly)
		ofstream gameOutcome;
		gameOutcome.open("Game Outcome.txt");

		//Player 1 places card
		cout << "Player One's Turn: " << endl, gameOutcome << "Player One's Turn" << endl;
		player1.checkDeckSize();
		player1.checkHand();
		player1.placeCardOnBoard();
		cout << flush;
		system("CLS");
		//Checks what card is placed down before determining what points to add to the player
		cout << "Outcome: " << endl;
		if (player1.getPlacedBoardCard() == "Power Plus") player1.addPoints(1), cout << "Power Plus placed\n\n", gameOutcome << "Power Plus placed\n\n";
		if (player1.getPlacedBoardCard() == "Power Down") botPlayer.takePoints(1), cout << "Power Down placed\n\n", gameOutcome << "Power Down placed\n\n";
		if (player1.getPlacedBoardCard() == "Steal")
		{
			cout << "Steal Card placed\n\n", gameOutcome << "Steal Card placed\n\n";
			if (botPlayer.getBoardSize() < 1)
			{
				cout << "Empty set, adding point to player\n\n", gameOutcome << "Empty set, adding point to player\n\n";
				player1.addPoints(1);
			}
			else
			{
				//Steal Normal Cards
				if (botPlayer.getPlacedBoardCard() == "Power Plus") player1.handAddPowerPlus(), cout << "Power Plus Stolen\n" << endl, gameOutcome << "Power Plus Stolen\n" << endl;
				if (botPlayer.getPlacedBoardCard() == "Power Down") player1.handAddPowerDown(), cout << "Power Down Stolen\n" << endl, gameOutcome << "Power Down Stolen\n" << endl;
				if (botPlayer.getPlacedBoardCard() == "Steal")player1.addPoints(1), cout << "Steal Card Stolen  - SAME CARD adding point to player\n" << endl, gameOutcome << "Steal Card Stolen  - SAME CARD adding point to player" << endl;

				//Steal Special Cards
				if (botPlayer.getPlacedBoardCard() == "Clear Board")player1.handAddClearBoard(), cout << "Clear Board Stolen\n" << endl, gameOutcome << "Clear Board Stolen\n" << endl;
				if (botPlayer.getPlacedBoardCard() == "Return Card")player1.handAddCardReturnCard(), cout << "Return Card Stolen\n" << endl, gameOutcome << "Return Card Stolen\n" << endl;
				if (botPlayer.getPlacedBoardCard() == "Wild Card")player1.handAddWildCard(), cout << "Wild Card Stolen\n" << endl, gameOutcome << "Wild Card Stolen\n" << endl;
				botPlayer.removeCardFromBoard();
			}
		}

		//Special Cards
		//Clears the entire board
		if (player1.getPlacedBoardCard() == "Clear Board") player1.clearBoard(), botPlayer.clearBoard(), cout << "CLEAR BOARD! placed\n\n", gameOutcome << "CLEAR BOARD! placed\n\n";
		//Returns the latest card back to player can be used multiple times to stall time
		if (player1.getPlacedBoardCard() == "Return Card")
		{
			if (player1.getPlacedBoardCard() == "Return Card")player1.addPoints(1), cout << "RETURN CARD! SAME CARD adding point to player\n" << endl, gameOutcome << "SAME CARD adding point to player\n" << endl;
			else player1.returnCardFromBoard(), cout << "Return Card placed\n\n", gameOutcome << "Return Card placed\n\n";
		}

		//Wild Card - will have a random effect on the game
		if (player1.getPlacedBoardCard() == "Wild Card")
		{
			//Random number from 0-3 (4 numbers in total)
			int wildRandom = rand() % 4;
			cout << "WILD CARD! placed\n\n", gameOutcome << "WILD CARD! placed\n\n";

			//If board is empty 50/50 chance to gain or lose 5 points
			if (botPlayer.getBoardSize() < 1)
			{
				if (wildRandom > 1) player1.addPoints(5), cout << "Gained 5 points!" << endl;
				else player1.takePoints(5), cout << "LOST 5 points!" << endl;
			}
			//Else give the player a 25% change to gain 5 points/lose 5 points/clear board or steal a card
			else
			{
				switch (wildRandom)
				{
				case(0):
				{
					//Steal Normal Cards
					if (botPlayer.getPlacedBoardCard() == "Power Plus") player1.handAddPowerPlus(), cout << "Power Plus Stolen\n" << endl, gameOutcome << "Power Plus Stolen\n" << endl;
					if (botPlayer.getPlacedBoardCard() == "Power Down") player1.handAddPowerDown(), cout << "Power Down Stolen\n" << endl, gameOutcome << "Power Plus Stolen\n" << endl;
					if (botPlayer.getPlacedBoardCard() == "Steal")player1.handAddStealCard(), cout << "Steal Card Stolen\n" << endl, gameOutcome << "Power Plus Stolen\n" << endl;

					//Steal Special Cards
					if (botPlayer.getPlacedBoardCard() == "Clear Board")player1.handAddClearBoard(), cout << "Clear Board Stolen\n" << endl, gameOutcome << "Clear Board Stolen\n" << endl;
					if (botPlayer.getPlacedBoardCard() == "Return Card")player1.handAddCardReturnCard(), cout << "Return Card Stolen\n" << endl, gameOutcome << "Return Card Stolen\n" << endl;
					if (botPlayer.getPlacedBoardCard() == "Wild Card")player1.handAddWildCard(), cout << "Wild Card Stolen\n" << endl, gameOutcome << "Wild Card Stolen\n" << endl;
					botPlayer.removeCardFromBoard();
					break;
				}
				case(1):
				{
					player1.addPoints(5), cout << "Gained 5 points!" << endl;
					break;
				}
				case(2):
				{
					player1.takePoints(5), cout << "LOST 5 points!" << endl;
					break;
				}
				case(3):
				{
					cout << "WILD CLEAR BOARD!" << endl;
					player1.clearBoard();
					botPlayer.clearBoard();
					break;
				}
				default:
					break;
				}
			}
		}

		player1.checkPoints();
		botPlayer.checkPoints();
		cout << "\n \n";


		//Bot places card
		cout << "Bot's Turn: " << endl, gameOutcome << "Power Plus placed\n\n";
		botPlayer.checkDeckSize();
		botPlayer.botBoy();
		if (botPlayer.getPlacedBoardCard() == "Power Plus") botPlayer.addPoints(1), cout << "Power Plus placed\n\n", gameOutcome << "Power Plus placed\n\n";
		if (botPlayer.getPlacedBoardCard() == "Power Down") player1.takePoints(1), cout << "Power Down placed\n\n", gameOutcome << "Power Down placed\n\n";
		if (botPlayer.getPlacedBoardCard() == "Steal")
		{
			cout << "Steal Card placed\n\n", gameOutcome << "Steal Card placed\n\n";
			if (player1.getBoardSize() < 1)
			{
				cout << "Empty set, adding point to player\n\n", gameOutcome << "Empty set, adding point to player\n\n";
				botPlayer.addPoints(1);
			}
			else
			{
				//Steal Normal Cards
				if (player1.getPlacedBoardCard() == "Power Plus") botPlayer.handAddPowerPlus(), cout << "Power Plus Stolen\n" << endl, gameOutcome << "Power Plus Stolen" << endl;
				if (player1.getPlacedBoardCard() == "Power Down") botPlayer.handAddPowerDown(), cout << "Power Down Stolen\n" << endl, gameOutcome << "Power Down Stolen" << endl;
				if (player1.getPlacedBoardCard() == "Steal")botPlayer.addPoints(1), cout << "Steal Card Stolen  - SAME CARD adding point to player\n" << endl, gameOutcome << "Steal Card Stolen  - SAME CARD adding point to player" << endl;

				//Steal Special Cards
				if (botPlayer.getPlacedBoardCard() == "Clear Board")player1.handAddStealCard(), cout << "Clear Board Stolen\n" << endl, gameOutcome << "Clear Board Stolen\n" << endl;
				if (botPlayer.getPlacedBoardCard() == "Return Card")player1.handAddStealCard(), cout << "Return Card Stolen\n" << endl, gameOutcome << "Return Card Stolen\n" << endl;
				if (botPlayer.getPlacedBoardCard() == "Wild Card")player1.handAddStealCard(), cout << "Wild Card Stolen\n" << endl, gameOutcome << "Wild Card Stolen\n" << endl;
				player1.removeCardFromBoard();
			}
		}

		//Special Cards
		//Clears the entire board
		if (botPlayer.getPlacedBoardCard() == "Clear Board") botPlayer.clearBoard(), player1.clearBoard(), cout << "CLEAR BOARD! placed\n\n", gameOutcome << "CLEAR BOARD! placed\n\n";
		//Returns the latest card back to player can be used multiple times to stall time
		if (botPlayer.getPlacedBoardCard() == "Return Card")
		{
			if (botPlayer.getPlacedBoardCard() == "Return Card")botPlayer.addPoints(1), cout << "RETURN CARD! SAME CARD adding point to player\n" << endl, gameOutcome << "SAME CARD adding point to player\n" << endl;
			else botPlayer.returnCardFromBoard(), cout << "Return Card placed\n\n", gameOutcome << "Return Card placed\n\n";
		}
		//Wild Card - will have a random effect on the game
		if (botPlayer.getPlacedBoardCard() == "Wild Card")
		{
			//Random number from 0-3 (4 numbers in total)
			int wildRandom = rand() % 4;
			cout << "WILD CARD! placed\n\n", gameOutcome << "WILD CARD! placed\n\n";

			//If board is empty 50/50 chance to gain or lose 5 points
			if (player1.getBoardSize() < 1)
			{
				if (wildRandom > 1) botPlayer.addPoints(5), cout << "Gained 5 points!" << endl;
				else botPlayer.takePoints(5), cout << "LOST 5 points!" << endl;
			}
			//Else give the player a 25% change to gain 5 points/lose 5 points/clear board or steal a card
			else
			{
				switch (wildRandom)
				{
				case(0):
				{
					//Steal Normal Cards
					if (player1.getPlacedBoardCard() == "Power Plus") botPlayer.handAddPowerPlus(), cout << "Power Plus Stolen\n" << endl, gameOutcome << "Power Plus Stolen" << endl;
					if (player1.getPlacedBoardCard() == "Power Down") botPlayer.handAddPowerDown(), cout << "Power Down Stolen\n" << endl, gameOutcome << "Power Down Stolen" << endl;
					if (player1.getPlacedBoardCard() == "Steal")botPlayer.handAddStealCard(), cout << "Steal Card Stolen\n" << endl, gameOutcome << "Steal Card Stolen" << endl;

					//Steal Special Cards
					if (botPlayer.getPlacedBoardCard() == "Clear Board")player1.handAddStealCard(), cout << "Clear Board Stolen\n" << endl, gameOutcome << "Clear Board Stolen\n" << endl;
					if (botPlayer.getPlacedBoardCard() == "Return Card")player1.handAddStealCard(), cout << "Return Card Stolen\n" << endl, gameOutcome << "Return Card Stolen\n" << endl;
					if (botPlayer.getPlacedBoardCard() == "Wild Card")player1.handAddStealCard(), cout << "Wild Card Stolen\n" << endl, gameOutcome << "Wild Card Stolen\n" << endl;
					player1.removeCardFromBoard();
					break;
				}
				case(1):
				{
					botPlayer.addPoints(5), cout << "Gained 5 points!" << endl;
					break;
				}
				case(2):
				{
					botPlayer.takePoints(5), cout << "LOST 5 points!" << endl;
					break;
				}
				case(3):
				{
					cout << "WILD CLEAR BOARD!" << endl;
					botPlayer.clearBoard();
					player1.clearBoard();
					break;
				}
				default:
					break;
				}
			}
		}
		player1.checkPoints();
		botPlayer.checkPoints();
		cout << "\n \n";
		gameOutcome.close();
		break;
	}

	//Player Vs Player
	case (2):
	{
		//Player 1 places card
		cout << "Player One's Turn: " << endl;
		player1.checkDeckSize();
		player1.checkHand();
		player1.placeCardOnBoard();
		cout << flush;
		system("CLS");
		cout << "Player One Outcome: " << endl;
		if (player1.getDeckSize() < 1 && player1.getHandSize() < 1)
		{
			cout << "\nNothing in Hand or Deck turn skipped!\n" << endl;
		}
		else
		{
			if (player1.getPlacedBoardCard() == "Power Plus") player1.addPoints(1), cout << "Power Plus placed" << "\n\n";
			if (player1.getPlacedBoardCard() == "Power Down") player2.takePoints(1), cout << "Power Down placed" << "\n\n";
			if (player1.getPlacedBoardCard() == "Steal")
			{
				cout << "Steal Card placed" << "\n\n";
				if (player2.getBoardSize() < 1)
				{
					cout << "Empty set, adding point to player" << "\n\n";
					player1.addPoints(1);
				}
				else
				{
					//Steal Normal Cards
					if (player2.getPlacedBoardCard() == "Power Plus") player1.handAddPowerPlus(), cout << "Power Plus Stolen\n" << endl;
					if (player2.getPlacedBoardCard() == "Power Down") player1.handAddPowerDown(), cout << "Power Plus Stolen\n" << endl;
					if (player2.getPlacedBoardCard() == "Steal")player1.addPoints(1), cout << "Steal Card Stolen  - SAME CARD adding point to player\n" << endl;
					//Steal Special Cards
					if (player2.getPlacedBoardCard() == "Clear Board")player1.handAddStealCard(), cout << "Clear Board Stolen\n" << endl;
					if (player2.getPlacedBoardCard() == "Return Card")player1.handAddStealCard(), cout << "Return Card Stolen\n" << endl;
					if (player2.getPlacedBoardCard() == "Wild Card")player1.handAddStealCard(), cout << "Wild Card Stolen\n" << endl;
					player2.removeCardFromBoard();
				}
			}
		}

		//Special Cards
		//Clears the entire board
		if (player1.getPlacedBoardCard() == "Clear Board") player1.clearBoard(), player2.clearBoard(), cout << "CLEAR BOARD! placed\n\n";

		//Returns the latest card back to player or add point if it's another return card
		if (player1.getPlacedBoardCard() == "Return Card")
		{
			if (player1.getPlacedBoardCard() == "Return Card")player1.addPoints(1), cout << "RETURN CARD! SAME CARD adding point to player\n";
			else player1.returnCardFromBoard(), cout << "Return Card placed\n\n";
		}

		//Wild Card - will have a random effect on the game
		if (player1.getPlacedBoardCard() == "Wild Card")
		{
			//Random number from 0-3 (4 numbers in total)
			int wildRandom = rand() % 4;
			cout << "WILD CARD! placed\n\n";

			//If board is empty 50/50 chance to gain or lose 5 points
			if (player2.getBoardSize() < 1)
			{
				if (wildRandom > 1) player1.addPoints(5), cout << "Gained 5 points!" << endl;
				else player1.takePoints(5), cout << "LOST 5 points!" << endl;
			}
			//Else give the player a 25% change to gain 5 points/lose 5 points/clear board or steal a card
			else
			{
				switch (wildRandom)
				{
				case(0):
				{
					//Steal Normal Cards
					if (player2.getPlacedBoardCard() == "Power Plus") player1.handAddPowerPlus(), cout << "Power Plus Stolen\n" << endl;
					if (player2.getPlacedBoardCard() == "Power Down") player1.handAddPowerDown(), cout << "Power Down Stolen\n" << endl;
					if (player2.getPlacedBoardCard() == "Steal")player1.handAddStealCard(), cout << "Steal Card Stolen\n" << endl;

					//Steal Special Cards
					if (player2.getPlacedBoardCard() == "Clear Board")player1.handAddStealCard(), cout << "Clear Board Stolen\n" << endl;
					if (player2.getPlacedBoardCard() == "Return Card")player1.handAddStealCard(), cout << "Return Card Stolen\n" << endl;
					if (player2.getPlacedBoardCard() == "Wild Card")player1.handAddStealCard(), cout << "Wild Card Stolen\n" << endl;
					player2.removeCardFromBoard();
					break;
				}
				case(1):
				{
					player1.addPoints(5), cout << "Gained 5 points!" << endl;
					break;
				}
				case(2):
				{
					player1.takePoints(5), cout << "LOST 5 points!" << endl;
					break;
				}
				case(3):
				{
					cout << "WILD CLEAR BOARD!" << endl;
					player1.clearBoard();
					player2.clearBoard();
					break;
				}
				default:
					break;
				}
			}
		}
		player1.checkPoints();
		player2.checkPoints();
		cout << "\n \n";

		//Player 2 places card
		cout << "Player Two's Turn: " << endl;
		player2.checkDeckSize();
		player2.checkHand();
		player2.placeCardOnBoard();
		cout << flush;
		system("CLS");
		cout << "Player Two Outcome: " << endl;
		if (player2.getDeckSize() < 1 && player2.getHandSize() < 1)
		{
			cout << "\nNothing in Hand or Deck turn skipped!\n" << endl;
		}
		else
		{
			if (player2.getPlacedBoardCard() == "Power Plus") player2.addPoints(1), cout << "Power Plus placed" << "\n\n";
			if (player2.getPlacedBoardCard() == "Power Down") player1.takePoints(1), cout << "Power Down placed" << "\n\n";
			if (player2.getPlacedBoardCard() == "Steal")
			{
				cout << "Steal Card placed" << "\n\n";
				if (player1.getBoardSize() < 1)
				{
					cout << "Empty set, adding point to player" << "\n\n";
					player2.addPoints(1);
				}
				else
				{
					if (player1.getPlacedBoardCard() == "Power Plus") player2.handAddPowerPlus(), cout << "Power Plus Stolen\n" << endl;
					if (player1.getPlacedBoardCard() == "Power Down") player2.handAddPowerDown(), cout << "Power Plus Stolen\n" << endl;
					//If steal card gets another steal card player gains extra points
					if (player2.getPlacedBoardCard() == "Steal")player2.addPoints(1), cout << "Steal Card Stolen  - SAME CARD adding point to player\n" << endl;
					//Steal Special Cards
					if (player1.getPlacedBoardCard() == "Clear Board")player2.handAddStealCard(), cout << "Clear Board Stolen\n" << endl;
					if (player1.getPlacedBoardCard() == "Return Card")player2.handAddStealCard(), cout << "Return Card Stolen\n" << endl;
					if (player1.getPlacedBoardCard() == "Wild Card")player2.handAddStealCard(), cout << "Wild Card Stolen\n" << endl;
					player1.removeCardFromBoard();
				}
			}
		}

		//Special Cards
//Clears the entire board
		if (player2.getPlacedBoardCard() == "Clear Board") player2.clearBoard(), player1.clearBoard(), cout << "CLEAR BOARD! placed\n\n";

		//Returns the latest card back to player or add point if it's another return card
		if (player2.getPlacedBoardCard() == "Return Card")
		{
			if (player2.getPlacedBoardCard() == "Return Card")player2.addPoints(1), cout << "RETURN CARD! SAME CARD adding point to player\n";
			else player2.returnCardFromBoard(), cout << "Return Card placed\n\n";
		}

		//Wild Card - will have a random effect on the game
		if (player2.getPlacedBoardCard() == "Wild Card")
		{
			//Random number from 0-3 (4 numbers in total)
			int wildRandom = rand() % 4;
			cout << "WILD CARD! placed\n\n";

			//If board is empty 50/50 chance to gain or lose 5 points
			if (player1.getBoardSize() < 1)
			{
				if (wildRandom > 1) player2.addPoints(5), cout << "Gained 5 points!" << endl;
				else player2.takePoints(5), cout << "LOST 5 points!" << endl;
			}
			//Else give the player a 25% change to gain 5 points/lose 5 points/clear board or steal a card
			else
			{
				switch (wildRandom)
				{
				case(0):
				{
					//Steal Normal Cards
					if (player1.getPlacedBoardCard() == "Power Plus") player2.handAddPowerPlus(), cout << "Power Plus Stolen\n" << endl;
					if (player1.getPlacedBoardCard() == "Power Down") player2.handAddPowerDown(), cout << "Power Down Stolen\n" << endl;
					if (player1.getPlacedBoardCard() == "Steal")player2.handAddStealCard(), cout << "Steal Card Stolen\n" << endl;

					//Steal Special Cards
					if (player1.getPlacedBoardCard() == "Clear Board")player2.handAddStealCard(), cout << "Clear Board Stolen\n" << endl;
					if (player1.getPlacedBoardCard() == "Return Card")player2.handAddStealCard(), cout << "Return Card Stolen\n" << endl;
					if (player1.getPlacedBoardCard() == "Wild Card")player2.handAddStealCard(), cout << "Wild Card Stolen\n" << endl;
					player1.removeCardFromBoard();
					break;
				}
				case(1):
				{
					player2.addPoints(5), cout << "Gained 5 points!" << endl;
					break;
				}
				case(2):
				{
					player2.takePoints(5), cout << "LOST 5 points!" << endl;
					break;
				}
				case(3):
				{
					cout << "WILD CLEAR BOARD!" << endl;
					player2.clearBoard();
					player1.clearBoard();
					break;
				}
				default:
					break;
				}
			}
		}

		player1.checkPoints();
		player2.checkPoints();
		cout << "\n \n";
		break;
	}
	}
}

//Returns the deck total of both players 
int Card::allDeckTotal(int mode)
{
	int dTotal = 0;
	switch (mode)
	{
	case(1):
	{
		dTotal = (player1.getDeckSize() + botPlayer.getDeckSize());
		return dTotal;
		break;
	}
	case(2):
	{
		dTotal = (player1.getDeckSize() + player2.getDeckSize());
		return dTotal;
		break;
	}
	default:
		break;
	}

}

//Returns hand total of both players
int Card::allHandTotal(int mode)
{
	int dTotal = 0;
	switch (mode)
	{
	case(1):
	{
		dTotal = (player1.getHandSize() + botPlayer.getHandSize());
		return dTotal;
		break;
	}
	case(2):
	{
		dTotal = (player1.getHandSize() + player2.getHandSize());
		return dTotal;
		break;
	}
	default:
		break;
	}
}

int Card::allTotal(int mode)
{
	int dTotal = 0;
	switch (mode)
	{
	case(1):
	{
		dTotal = (player1.getDeckSize() + player1.getHandSize() + botPlayer.getDeckSize() + botPlayer.getHandSize());
		return dTotal;
		break;
	}
	case(2):
	{
		dTotal = (player1.getDeckSize() + player1.getDeckSize() + player2.getDeckSize() + player2.getHandSize());
		return dTotal;
		break;
	}
	default:
		break;
	}
}

int Card::handTotal(int player)
{
	if (player == 1)
	{
		return player1.getHandSize();
	}

	if (player == 2)
	{
		return player2.getHandSize();
	}

	if (player == 3)
	{
		return botPlayer.getHandSize();
	}
}

int Card::deckTotal(int player)
{
	if (player == 1)
	{
		return player1.getDeckSize();
	}

	if (player == 2)
	{
		return player2.getDeckSize();
	}

	if (player == 3)
	{
		return botPlayer.getDeckSize();
	}
}

void displayBoard(int player)
{
	if (player == 1)
	{
		player1.checkBoard();
	}

	if (player == 2)
	{
		player2.checkBoard();
	}

	if (player == 3)
	{
		botPlayer.checkBoard();
	}
}

void Card::endGame(int mode)
{
	switch (mode)
	{
	case(1):
	{
		if (player1.getPoints() > botPlayer.getPoints())
		{
			cout << "You win!" << endl;
		}

		else if (player1.getPoints() < botPlayer.getPoints())
		{
			cout << "You lose!" << endl;
		}

		else if (player1.getPoints() == botPlayer.getPoints())
		{
			cout << "DRAW!" << endl;
		}
		player1.clearAll();
		player1.clearBoard();
		player1.setPoints(0);
		botPlayer.clearAll();
		botPlayer.clearBoard();
		botPlayer.setPoints(0);
		break;
	}

	case(2):
	{
		if (player1.getPoints() > player2.getPoints())
		{
			cout << "Player One Wins!" << endl;
		}

		//Minor bug, when player 2 wins it does not display anything just the main menu
		else if (player1.getPoints() < player2.getPoints())
		{
			cout << "Player Two Wins!" << endl;
		}

		else if (player1.getPoints() == botPlayer.getPoints())
		{
			cout << "DRAW!" << endl;
		}
		player1.clearAll();
		player1.clearBoard();
		player1.setPoints(0);
		player2.clearAll();
		player2.clearBoard();
		player2.setPoints(0);
		break;
	}
	}
}