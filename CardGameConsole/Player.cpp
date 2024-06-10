#include <iostream>
#include <fstream>

#include "UserBase.h"
#include "pch.h"

using namespace std;

//Constructor that takes a String name using n
UserBase::UserBase(string n)
	:name(n)
{

}

// Add and remove points from a player
void UserBase::addPoints(int amount)
{
	UserBase::points += amount;
}

void UserBase::takePoints(int amount)
{
	UserBase::points -= amount;
}

//player points either to clear or cheat
void UserBase::setPoints(int amount)
{
	UserBase::points = amount;
}

//Returns points
int UserBase::getPoints()
{
	return UserBase::points;
}

//Takes a card from deck and places it into the hand
void UserBase::takeCardFromDeck()
{
		UserBase::hand.push_back(UserBase::deck[0]);
		UserBase::deck.erase(UserBase::deck.begin());
}

//Add a specifc card type into deck
void UserBase::addPowerPlus()
{
	UserBase::deck.push_back("Power Plus");
}

void UserBase::addPowerDown()
{
	UserBase::deck.push_back("Power Down");
}

void UserBase::addStealCard()
{
	UserBase::deck.push_back("Steal");
}

//Add a specifc card type into hand (Only used for card effects like steal)
void UserBase::handAddPowerPlus()
{
	UserBase::hand.push_back("Power Plus");
}

void UserBase::handAddPowerDown()
{
	UserBase::hand.push_back("Power Down");
}

void UserBase::handAddStealCard()
{
	UserBase::hand.push_back("Steal");
}

//Clears the entire board to prevent stealing or used to gain extra points from steal
void UserBase::addClearBoard()
{
	UserBase::deck.push_back("Clear Board");
}

void UserBase::handAddClearBoard()
{
	UserBase::hand.push_back("Clear Board");
}

//Returns a random card from the board (opposite from stealing)
void UserBase::addCardReturnCard()
{
	UserBase::deck.push_back("Return Card");
}

void UserBase::handAddCardReturnCard()
{
	UserBase::hand.push_back("Return Card");
}

//Wild Wild Card - Gambling card that will either add 5 points to the player/take 5 points/Steal a card or clear board from the player with a 25 chance.
void UserBase::addWildCard()
{
	UserBase::deck.push_back("Wild Card");
}

void UserBase::handAddWildCard()
{
	UserBase::hand.push_back("Wild Card");
}

//Removes card from hand or the top of deck
void UserBase::removeHandCard()
{
	UserBase::hand.erase(UserBase::hand.begin());
}

void UserBase::removeTopDeck()
{
	UserBase::deck.erase(UserBase::deck.begin());
}

//Returns string to allow for other classes to read the top deck
string UserBase::checkTopDeck()
{
	return UserBase::deck[0];
}

//Checks everthing from points to the entire hand/deck
void UserBase::checkPoints()
{
	cout << name << " points: " << UserBase::points << endl;
}

void UserBase::checkHand()
{
	cout << UserBase::name << "'s hand: ";
	for (int i = 0; i < UserBase::hand.size(); i++) cout << endl << i << " " << UserBase::hand[i];
	cout << endl;
}

//Checks the players entire deck (not intented as the deck is generated randomly like a shuffle), can also be used on opponents
void UserBase::checkDeck()
{
	for (int i = 0; i < UserBase::deck.size(); i++) cout << endl << i << " " << UserBase::deck[i];
	cout << endl;
}

//Returns total cards in Deck/Hand or Board
int UserBase::getDeckSize()
{
	return UserBase::deck.size();
}

int UserBase::getHandSize()
{
	return UserBase::hand.size();
}

int UserBase::getBoardSize()
{
	return UserBase::board.size();
}

//Displays the decksize without reutrning anything;
void UserBase::checkDeckSize()
{
	cout << name << " " << "Deck Size: " << UserBase::deck.size() << endl;
}

//Mostly used for cleaning up hands and decks when the game is over however, it can be used as a cheat to instantly win/lose aginst an opponent
void UserBase::clearHand()
{
	UserBase::hand.clear();
}

void UserBase::clearDeck()
{
	UserBase::deck.clear();
}

void UserBase::clearAll()
{
	UserBase::deck.clear();
	UserBase::hand.clear();
}

//Board Functions

//Displays the entire board of a player
void UserBase::checkBoard()
{
	for (int i = 0; i < UserBase::board.size(); i++) cout << endl << i << " " << UserBase::board[i];
	cout << endl;
}

//Gets the most recent placed card on board
string UserBase::getPlacedBoardCard()
{
	if (UserBase::board.size() < 1) return "Empty board";
	else return UserBase::board[UserBase::board.size() - 1];
}

//Take a card off the hand vector and add that value into the board vector
void UserBase::placeCardOnBoard()
{
	int cardNumber;
	cout << name << " select card to place of board from 0 to 4" << endl;
	cin >> cardNumber;
	
	//CIN validation to make sure that when ever anything that isnt an int would 
	//print out Invalid input and proceed to do nothing However it would default
	//to using "Card 0" when inputting a string and int together.
	while (1)
	{
		if (cin.fail())
		{
			//Clear the input
			cin.clear();
			//Clearing any buffers before a new line
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid Input" << endl;
			//Redo the input until a valid inpit has been used
			cin >> cardNumber;
		}
		//Once a valid input has been used break the while loop
		else if (!cin.fail()) break;
	}
	if (UserBase::hand.size() < 1)
	{
		cout << "Empty hand turn skipped" << endl;
	}
	else
	{
		while (cardNumber < 0 || cardNumber >= UserBase::hand.size())
		{
			cout << "Card not in hand" << endl;
			cin >> cardNumber;
		}
		UserBase::board.push_back(UserBase::hand[cardNumber]);
		UserBase::hand.erase(UserBase::hand.begin() + cardNumber);
	}
}

//Primitive Bot to play with, it always selects card a random card to clear hand. However it can be improved upon. The bot can still win, lose and DRAW with this function
void UserBase::botBoy()
{
	int cardNumber = 0;
	if (UserBase::hand.size() < 1)
	{
		cout << "Empty hand turn skipped" << endl;
	}
	else
	{
		cardNumber = rand() % UserBase::hand.size();
		while (cardNumber < 0 || cardNumber >= UserBase::hand.size())
		{
			cout << "Card not in hand" << endl;
			cin >> cardNumber;
		}
		UserBase::board.push_back(UserBase::hand[cardNumber]);
		UserBase::hand.erase(UserBase::hand.begin() + cardNumber);
	}
}

//Removes the most recent card on the board
void UserBase::removeCardFromBoard()
{
	if (UserBase::board.size() < 1) cout << "Empty board" << endl;
	UserBase::board.pop_back();
}

//Return most recent card from board to hand
void UserBase::returnCardFromBoard()
{
	if (UserBase::board.size() == 0)cout << "Cannot steal an empty set" << endl;
	else
	{
		UserBase::hand.push_back(UserBase::board[UserBase::board.size() - 1]);
		UserBase::board.pop_back();
	}
}

//Clear the board for the next game
void UserBase::clearBoard()
{
	UserBase::board.clear();
}