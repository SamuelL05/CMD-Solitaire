#pragma once
#include <stack> // Used for drawPile
#include "Card.h"
using namespace std;


class DrawPile { // Will be a total of one DrawPile object.

private:
		 
	stack<Card> drawPile; // Draw pile stack that will contain all cards cycled in from deck.

public:

	bool putCard(Card card); // Ability to add cards to the stack.
	Card getCard(); // Removal of card from a stack.

	int isFull(); // Checking current quantity of cards in stacks.
	bool isEmpty(); // Check if stack is empty.
};