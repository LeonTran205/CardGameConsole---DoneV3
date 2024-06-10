#pragma once

#include "pch.h"

using namespace std;

class Card {
public:
	Card();

	//General functions for Vector card game
	void generateDeck(int);
	void fillPlayer1Hand();
	void fillPlayer2Hand();
	void fillBotHand();
	void placeGenericCard(int);
	int allDeckTotal(int);
	int allHandTotal(int);
	int allTotal(int);

	int handTotal(int);
	int deckTotal(int);

	void displayBoard(int);

	void endGame(int);

	void testPlayer();

};
