#pragma once
#include <deque> // Used for hand piles.
#include <stack> // Used for setting hand pile.
#include "Card.h"
using namespace std;


class HandPile { // Total of 7 Hand objects.

private:

	deque<Card> handPile; // Can potentially contain all suites descending in value. 
						  // If they alter between (Spades, Clubs) and (Hearts, Diamonds).

public:

	void setHandPile(stack<Card> & deck, int count); // Building of handPile used in initial program start.

	bool putCard(Card card); // Ability to add cards to the stack.
	Card getCard(); // Removal of card from a stack.

	int isFull(); // Checking current quantity of cards in stacks.
	bool isEmpty(); // Check if stack is empty.
};