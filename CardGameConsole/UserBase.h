#pragma once
#include "pch.h"
#include "Card.h"

class UserBase
{
public:
	//******************Base Game function initalisation******************

	UserBase(string);
	// Add and remove points from a player
	void addPoints(int);
	void takePoints(int);

	//player points either to clear or cheat
	void setPoints(int);

	//Returns points
	int getPoints();

	//Take a card from deck vector and place it into hand vector
	void takeCardFromDeck();

	//Base Cards that are required for the main assignment

	//Add base cards to deck
	void addPowerPlus();
	void addPowerDown();
	void addStealCard();

	//Add base cards to hand meant for stealing
	void handAddPowerPlus();
	void handAddPowerDown();
	void handAddStealCard();

	//Special Wild Cards

	//Clears the board to prevent stealing or used to gain extra points from steal
	void addClearBoard();
	void handAddClearBoard();

	//Returns a random card from the board (opposite from stealing)
	void addCardReturnCard();
	void handAddCardReturnCard();

	//Wild Wild Card - Gambling card that will either add 5 points to the player/take 5 points/Steal a card or clear board from the player with a 25 chance.
	void addWildCard();
	void handAddWildCard();

	//Removes card from hand or the top of deck
	void removeHandCard();
	void removeTopDeck();

	//Returns string to allow for other classes to read the top deck
	string checkTopDeck();
	//Checks everthing from points to the entire hand/deck
	void checkPoints();
	void checkHand();
	//Checks the players entire deck (not intented as the deck is generated randomly like a shuffle), can also be used on opponents
	void checkDeck();


	//Returns total cards in Deck/Hand or Board
	int getDeckSize();
	int getHandSize();
	int getBoardSize();

	//Displays the decksize without reutrning anything;
	void checkDeckSize();

	//Mostly used for cleaning up hands and decks when the game is over however, it can be used as a cheat to instantly win/lose aginst an opponent
	void clearHand();
	void clearDeck();
	void clearAll();

	//Board functions
	void checkBoard();
	string getPlacedBoardCard();
	void botBoy();
	void placeCardOnBoard();
	void removeCardFromBoard();
	void returnCardFromBoard();
	void clearBoard();

private:
	//******************Initalise private variables******************

	//Individual player or object
	const string name;

	//Vectors for both hand and deck for each player
	vector<string> deck;
	vector<string> hand;

	//Vectors board - Can also be called sets since this stores each players board side
	vector<string> board;

	//Individual player points that usually starts at 0
	int points = 0;
};
