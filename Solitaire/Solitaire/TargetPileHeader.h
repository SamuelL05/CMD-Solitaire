#pragma once
#include <stack> // Used for targetPile.
#include "Card.h"
using namespace std;


class TargetPile { // Total of 4 TargetPile objects.

private:

	stack<Card> targetPile; // Will contain cards of one suite starting at one and ascending to King.

public:

	bool endOfGame(); // Checks if there is currently a King in the stack.

	bool putCard(Card card); // Ability to add cards to the stack.
	Card getCard(); // Removal of card from a stack.

	int isFull(); // Checking current quantity of cards in stacks.
	bool isEmpty(); // Check if stack is empty.
};