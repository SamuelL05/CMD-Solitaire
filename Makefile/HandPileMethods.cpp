#include"HandPileHeader.h"
#include<stack> // Needed for setting hand piles
#include <deque> // Used for STL methods of altering handPile
using namespace std;


void HandPile::setHandPile(stack<Card> & deck, int count) { // Set a single hand pile.

	for (int x = 0; x < count; x++) { // Count ascends while building piles left to right.
		Card card = deck.top();
		if (x == (count - 1)) // If this is the last card to be placed in the pile. Adjust visibility.
			card.visible = true;
		handPile.push_front(card); // Add card to stack.
		deck.pop(); // Remove card from deck.
	}
}

bool HandPile::putCard(Card card) { // Add card to stack.

	if (card.value > 0 && card.value < 53) // Ghost card checking.
		handPile.push_front(card);
	return true;
}

Card HandPile::getCard() {

	Card card;
	if (handPile.size() > 0) { // If stack currently has cards, acquire one.
		card = handPile.front();
		handPile.pop_front();

	}
	else { // User is pulling from an empty stack.
		card.value = 0;
		card.visible = false;
	}
	return card;
}

int HandPile::isFull() { // Acquire current quantity of cards in stack.

	return handPile.size();
}

bool HandPile::isEmpty() { // Determine if pile is empty.

	if (handPile.size() == 0)
		return true;
	else
		return false;
}