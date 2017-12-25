#include"DrawPileHeader.h"


int DrawPile::isFull()
{ // Acquire current quantity of cards in stack.
	return drawPile.size();
}

bool DrawPile::isEmpty() { // Determine if pile is empty.

	if (drawPile.size() == 0)
		return true;
	else
		return false;
}

bool DrawPile::putCard(Card card) { // Add card to stack.

	if (card.value > 0 && card.value < 53) // Ghost card checking.
		drawPile.push(card); 
	return true;
}

Card DrawPile::getCard() {

	Card card; 
	if (drawPile.size() > 0) { // If stack currently has cards, acquire one.
		card = drawPile.top();
		drawPile.pop();
		card.visible = true;
	}
	else { // User is pulling from an empty stack.
		card.value = 0;
		card.visible = false;
	}
	return card;
}


