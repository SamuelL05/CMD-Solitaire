#include"TargetPileHeader.h"


bool TargetPile::endOfGame() {

	if (targetPile.size() > 12)  // TargetPile will only contain more then 12 cards if that 13th
								 // card is a king which would finish the suite.
		return true; // Suite complete.
	else
		return false; // No king found.
}

bool TargetPile::putCard(Card card) { // Add card to stack.

	if (card.value > 0 && card.value < 53) // Ghost card checking.
		targetPile.push(card);
	return true;
}

Card TargetPile::getCard() {

	Card card;
	if (targetPile.size() > 0) { // If stack currently has cards, acquire one.
		card = targetPile.top();
		targetPile.pop();
	}
	else { // User is pulling from an empty stack.
		card.value = 0;
		card.visible = false;
	}
	return card;
}

int TargetPile::isFull() { // Acquire current quantity of cards in stack.

	return targetPile.size();
}

bool TargetPile::isEmpty() { // Determine if pile is empty.

	if (targetPile.size() == 0)
		return true;
	else
		return false;
}
