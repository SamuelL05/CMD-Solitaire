#include <iostream> // Output
#include <vector> // Used for the creation of the deck.
#include <algorithm> // Used for the creation of the deck.
#include <random> // Used for the creation of the deck.
#include <chrono> // Used for the creation of the deck.
#include<iomanip> // Used for diaply of game field.
#include"DrawPileHeader.h" // DrawPile Header
#include"TargetPileHeader.h" // TargetPile Header
#include"HandPileHeader.h" // HandPile Header
using namespace std;


void setDeck(stack<Card> & deck); // Creates 52 randomized values between 1 - 52 used for the deck of cards.
int menu(stack<Card> & deck, DrawPile & drawPile, TargetPile * targetPile, HandPile * handPile); // Switch statement for menu.

// Card movement Functions _START_
void movementDecision(stack<Card> & deck, DrawPile & drawPile, TargetPile * targetPile, HandPile * handPile); // Gathers movement choice.
void handToHand(HandPile * handPile, int currPileNumber, int destPileNumber, int cardCount); // Attempt to complete hand to hand move.
void handToTarget(HandPile * handPile, TargetPile * targetPile, int currPileNumber, int destPileNumber); // Attempt to complete hand to target move.
void drawPiletoTarget(DrawPile & drawPile, TargetPile * targetPile, int destPileNumber); // Attempt to complete drawPile to target move.
void drawPileToHand(DrawPile & drawPile, HandPile * handPile, int destPileNumber); // Attempt to complete drawPile to hand move.
void targetToHand(TargetPile * targetPile, HandPile * handPile, int currPileNumber, int destPileNumber); // Attempt to complete targetPile to hand move.
bool validateToHandMove(int buriedCard, int topCard); // Checks the validity of a users card movements (Hand to Hand).
bool validateToTargetMove(int buriedCard, int topCard); // Checks the validity of a users card movements ((Hand / Draw) to Target).
// Card movement Functions _END_

void displayPlayingField(stack<Card> & deck, DrawPile & drawPile, TargetPile * targetPile, HandPile * handPile); // Display the game field.
void cardConvert(Card card); // Used for converting numeric value of card to suite and value. (Used by displayPlayingField).

int main() {

	cout << "Solitaire brought to you by Samuel R Leach II\n\n\n";

	stack<Card> deck; // Original deck of cards that will be used during execution of program.
	DrawPile drawPile; // Draw Pile 
	TargetPile * targetPile = new TargetPile[4]; // Target Pile
	HandPile * handPile = new HandPile[7]; // Hand Pile

	int exit = 0;
	int endOfGameCount = 0;

	setDeck(deck); // Acquire cards and shuffle.
	int count = 1;
	for (int x = 0; x < 7; x++) { // Utilizing cards from deck, build hand piles.
		handPile[x].setHandPile(deck, count); // Each handPile stack will be responsible for adding cards from the
		count++;							  // deck in accordance to the integer value sent.
	}
	drawPile.putCard(deck.top()); // Flip the first card onto the draw pile.
	deck.pop();

	displayPlayingField(deck, drawPile, targetPile, handPile); // Display the current status of the field.

	while (exit == 0 && endOfGameCount < 4) { // Lock user in loop until game is won, or user decides to quit.

		for (int x = 0; x < 4; x++) { // Check the target piles for Kings of each suite.
			if (targetPile[x].endOfGame() == true)
				endOfGameCount++; // If a king exists in that pile, one suite is complete.
		}
		exit = menu(deck, drawPile, targetPile, handPile); // Determine users decision.
		endOfGameCount = 0; // Reset end of game counter. 
	}

	char dummy;
	if (endOfGameCount > 3) {

		cout << "Congratulations, You WON.";
		cin.get(dummy);
	}
	return 0;
}

void setDeck(stack<Card> & deck) {

	// PRE: Program has just started. First Action to be preformed.

	// POST: A deck 52 cards will have been created and shuffled into a stack container.

	mt19937 mt;
	int count = 2;
	vector<int> randomNumbers;

	auto current_time = chrono::system_clock::now();
	auto epoch = current_time.time_since_epoch();
	auto time_in_millisecs = chrono::duration_cast<chrono::milliseconds>(epoch);
	long int milliseconds = time_in_millisecs.count();

	// Use milliseconds since epoch as seed of random number generator
	mt.seed(milliseconds);

	// Generate first random number and put in vector
	unsigned int randomNumber = (mt() % 52) + 1;
	randomNumbers.push_back(randomNumber);

	// Start loop to generate 51 more unique random numbers
	vector<int>::iterator iter = randomNumbers.begin();
	while (count <= 52)
	{
		// Generate a random number
		randomNumber = (mt() % 52) + 1;

		// Check if random number is already in vector
		iter = find(randomNumbers.begin(), randomNumbers.end(), randomNumber);

		// If not in vector, put the number in vector
		if (iter == randomNumbers.end())
		{
			randomNumbers.push_back(randomNumber);
			count++;
		}
	}

	Card card;
	// Copy randomly generated numbers over to deck.
	for (int x = 0; x < 52; x++) {
		card.value = randomNumbers[x];
		deck.push(card);
	}
}

int menu(stack<Card> & deck, DrawPile & drawPile, TargetPile * targetPile, HandPile * handPile) {

	// PRE: The deck has been created, and all seven handPiles have acquired their start up cards.

	// POST: The user will have been given five different options, and depending on the users choice
	//		 the program will respond accordingly. The user can either decide to draw a card, move a card,
	//		 display the game field, reset the game, or exit the game. The program will execute in accordance
	//		 with whatever decision the user makes. After choice has been executed in full the program will return
	//		 to this function, unless the end of game criteria has been met or the user selected to exit the program.

	Card card;
	int choice;

	cout << "What is your next move?" << endl;
	cout << "Draw card = '1', Move card = '2', Display Field = '3', Reset = '5', Exit = '6' " << endl;
	do {
		cout << "Enter Here: "; // Acquire users choice.
		cin >> choice;
		if (!cin.good()) {
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while ((choice > 6 || choice < 1) && choice == 4);
	cout << endl;

	switch (choice) {

		case 1:
			// Check if there are still cards to be flipped from deck.
			if (deck.size() == 0) {
				if (drawPile.isFull() == 0)
					cout << "Out of cards." << endl;
				else { // Refill cards from drawPile back into deck.
					while (!drawPile.isEmpty())
						deck.push(drawPile.getCard());
				}
			}
			else
				;
			if (deck.size() != 0) { // Acquire top card of deck and display.
				card = deck.top();
				deck.pop();
				drawPile.putCard(card);
				cout << "New Card: "; cardConvert(card); cout << "\n\n";
			}
			break;

		case 2:
			movementDecision(deck, drawPile, targetPile, handPile); // Move card
			break;

		case 3:
			displayPlayingField(deck, drawPile, targetPile, handPile); // Display field
			break;

		case 5:
			main();	// Reset		
			break;

		case 6:
			cout << endl; // Exit
			return 1;
	}
	return 0;
}

void movementDecision(stack<Card> & deck, DrawPile & drawPile, TargetPile * targetPile, HandPile * handPile) {

	// PRE: Deck has been created, handPiles made and menu has been called at least once. 

	// POST: Program will have passed information pertaining to the users movement desires to appropiate
	//		 functions that will attempt to complete the users move. 

	char currPileType = 'a';
	int currPileNumber = 0;
	char destPileType = 'a';
	int destPileNumber = 0;
	int cardCount = 0;

	cout << "I need to know what pile type the card is currently located in." << endl;
	cout << "Draw Pile = 'D', Hand Pile = 'H', and Target Pile = 'T'" << endl;
	do {
		cout << "Enter Here: ";
		cin >> currPileType; // Acquire pile type.

		if (int(currPileType) == 104)
			currPileType = int(currPileType) - 32; // Adjust the ASCII value of the character entered to capital.

		else if (int(currPileType) == 116)
			currPileType = int(currPileType) - 32; // Adjust the ASCII value of the character entered to capital.

		else if (int(currPileType) == 100)
			currPileType = int(currPileType) - 32; // Adjust the ASCII value of the character entered to capital.

		else if (!cin.good()) {
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (currPileType != 'H' && currPileType != 'T' && currPileType != 'D');
	cout << endl;

	// Acquire which pile number the card is currently located in that is to be moved.
	if (currPileType == 'H') {

		cout << "Enter hand pile card(s) is currently in." << endl;

		do {
			cout << "(1 - 7): ";
			cin >> currPileNumber; // Acquire handPile number to place card in.

			if (!cin.good()) {
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (currPileNumber < 1 || currPileNumber > 7);
		cout << endl;
	}
	else if (currPileType == 'T') {

		cout << "Enter target pile card is currently in." << endl;

		do {
			cout << "(1 - 4): ";
			cin >> currPileNumber; // Acquire targetPile number to place card in. 

			if (!cin.good()) {
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (currPileNumber < 1 || currPileNumber > 4);
		cout << endl;
	}
	else
		;

	cout << "Would you like to move your card to your hand or a target pile?" << endl;
	cout << "Hand pile = 'H' and Target Pile = 'T'" << endl;
	do {
		cout << "Enter Here: ";
		cin >> destPileType; // Acquire destination pile type.

		if (int(destPileType) == 104)
			destPileType = int(destPileType) - 32; // Adjust the ASCII value of the character entered to capital.

		else if (int(destPileType) == 116)
			destPileType = int(destPileType) - 32; // Adjust the ASCII value of the character entered to capital.

		else if (!cin.good()) {
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (destPileType != 'H' && destPileType != 'T');
	cout << endl;

	// Acquire which pile number the card is to be moved to.
	if (destPileType == 'H') {

		cout << "Enter hand pile to place card(s) in." << endl;

		do {
			cout << "(1 - 7): ";
			cin >> destPileNumber; // Acquire destination pile number for handPile.

			if (!cin.good()) {
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (destPileNumber < 1 || destPileNumber > 7);
		cout << endl;
	}
	else {

		cout << "Enter target pile to place card in." << endl;

		do {
			cout << "(1 - 4): ";
			cin >> destPileNumber; // Acquire destination pile number for targetPile.

			if (!cin.good()) {
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (destPileNumber < 1 || destPileNumber > 4);
		cout << endl;
	}

	// If the user has selected a move that can be done within the handfield 
	// a multi card move is possible. Determine the amount of cards that the user wants to move.
	if (currPileType == 'H' && destPileType == 'H') {

		cout << "How many cards to move?" << endl;

		do {
			cout << "Enter here: ";
			cin >> cardCount; // Acquire total cards to move. (Will only prompt if the user has selected a hand to hand move)
			if (!cin.good()) {
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (cardCount < 1 || cardCount > handPile[currPileNumber -1].isFull()); // Can not enter value less than zero or greater then 
		cout << endl;															  // the current quantity of cards in the stack.
	}
	else
		;

	// Alter value in variables to account for array logic.
	currPileNumber -= 1;
	destPileNumber -= 1;

	if (currPileType == 'H' && destPileType == 'H')  // Multi card move will only take place in users hand field.

		handToHand(handPile, currPileNumber, destPileNumber, cardCount); // Attempt to complete move.

	else if (currPileType == 'D' && destPileType == 'H')  // Move card from drawPile to handPile.

		drawPileToHand(drawPile, handPile, destPileNumber); // Attempt to complete move.

	else if (currPileType == 'D' && destPileType == 'T')  // Move card from drawPile to targetPile.

		drawPiletoTarget(drawPile, targetPile, destPileNumber); // Attempt to complete move.

	else if (currPileType == 'H' && destPileType == 'T') // Move card from handPile to targetPile.

		handToTarget(handPile, targetPile, currPileNumber, destPileNumber); // Attempt to complete move.

	else // Move card from targetPile to handPile.

		targetToHand(targetPile, handPile, currPileNumber, destPileNumber);
}

void drawPileToHand(DrawPile & drawPile, HandPile * handPile, int destPileNumber) {

	// PRE: Deck has been created, handPiles made and menu has been called at least once. User provided information
	//		that suggested an intent to move a card currently in the drawPile to the users hand.

	// POST: Program will attempt to complete the intentions of the user with the help of one of two verification functions that will
	//		 be passed the card(s) moving and the cards the moving cards will be going to. If the verification function deems the cards
	//		 to be a match a boolean value will be returned and the this function will complete the movement process.

	bool validMove = true;
	Card topCard;
	Card movingCard;

	if (!drawPile.isEmpty()) // Check if the drawPile is empty
		movingCard = drawPile.getCard(); // Acquire card from drawPile if able.
	else
		validMove = false; // User has attempted to move a nonexistant card. 

	if (!handPile[destPileNumber].isEmpty()) // Check if the destination handPile is empty.
		topCard = handPile[destPileNumber].getCard(); // Acquire the topCard of the pile the cards will be moved to.
	else
		topCard.value = 0; // If destination pile is empty assign topCard the value of zero.

	if (validateToHandMove(movingCard.value, topCard.value) && validMove == true) { // validate moving card from drawPile to handPile.
		movingCard.visible = true; // Alter visibility.
		handPile[destPileNumber].putCard(topCard); // Return the card that was originally first in the stack back to its place.
		handPile[destPileNumber].putCard(movingCard); // Add card being moved to destination pile.
	}
	else { // Move is invalid.
		cout << "Invalid Move." << endl;
		drawPile.putCard(movingCard); // Return card to drawPile.
		handPile[destPileNumber].putCard(topCard); // Return card to handPile.
	}

}

void drawPiletoTarget(DrawPile & drawPile, TargetPile * targetPile, int destPileNumber) {

	// PRE: Deck has been created, handPiles made and menu has been called at least once. User provided information
	//		that suggested an intent to move a card currently in the drawPile to a target pile.

	// POST: Program will attempt to complete the intentions of the user with the help of one of two verification functions that will
	//		 be passed the card(s) moving and the cards the moving cards will be going to. If the verification function deems the cards
	//		 to be a match a boolean value will be returned and the this function will complete the movement process.

	bool validMove = true;
	Card topCard;
	Card movingCard;

	if (!drawPile.isEmpty()) // Check if the drawPile is empty
		movingCard = drawPile.getCard(); // Acquire card from drawPile if able.
	else
		validMove = false; // User has attempted to move a nonexistant card. 

	if (!targetPile[destPileNumber].isEmpty()) // Check if the destination handPile is empty.
		topCard = targetPile[destPileNumber].getCard(); // Acquire the topCard of the pile the cards will be moved to.
	else
		topCard.value = 0; // If destination pile is empty assign topCard the value of zero.

	if (validateToTargetMove(movingCard.value, topCard.value) && validMove == true) { // validate moving card from drawPile to targetPile.
		movingCard.visible = true; // Alter visibility.
		targetPile[destPileNumber].putCard(topCard); // Return the card that was originally first in the stack back to its place.
		targetPile[destPileNumber].putCard(movingCard); // Add card being moved to destination pile. 
	}
	else { // Invalid move.
		cout << "Invalid Move." << endl;
		drawPile.putCard(movingCard); // Return card to drawPile.
		targetPile[destPileNumber].putCard(topCard); // Return card to targetPile.
	}
}

void handToTarget(HandPile * handPile, TargetPile * targetPile, int currPileNumber, int destPileNumber) {

	// PRE: Deck has been created, handPiles made and menu has been called at least once. User provided information
	//		that suggested an intent to move a card currently in the handPile to a target pile.

	// POST: Program will attempt to complete the intentions of the user with the help of one of two verification functions that will
	//		 be passed the card(s) moving and the cards the moving cards will be going to. If the verification function deems the cards
	//		 to be a match a boolean value will be returned and the this function will complete the movement process.

	bool validMove = true;
	Card topCard;
	Card movingCard;

	if (!targetPile[destPileNumber].isEmpty()) // Check if the destination targetPile is empty.
		topCard = targetPile[destPileNumber].getCard(); // Acquire the topCard of the pile the cards will be moved to.
	else
		topCard.value = 0; // If destination pile is empty assign topCard the value of zero.

	if (!handPile[currPileNumber].isEmpty()) // Check if the handPile is empty
		movingCard = handPile[currPileNumber].getCard(); // Acquire the card that will be moved.
	else
		validMove = false; // User is attempting to move nonexistant card.

	if (validateToTargetMove(movingCard.value, topCard.value) && validMove == true) { // validate moving card from handPile to targetPile.
		targetPile[destPileNumber].putCard(topCard); // Return the card that was originally first in the stack back to its place.
		targetPile[destPileNumber].putCard(movingCard); // Add card being moved to destination pile.
		Card temp = handPile[currPileNumber].getCard(); // Adjust visibility of the card now at the top of the stack.
		temp.visible = true;
		handPile[currPileNumber].putCard(temp);
	}
	else { // Invalid move.
		cout << "Invalid Move." << endl;
		validMove = false;
		handPile[currPileNumber].putCard(movingCard); // Return card to handPile.
		targetPile[destPileNumber].putCard(topCard); // Return card to targetPile.
	}
}

void handToHand(HandPile * handPile, int currPileNumber, int destPileNumber, int cardCount) {

	// PRE: Deck has been created, handPiles made and menu has been called at least once. User provided information
	//		that suggested an intent to move a card currently in the handPile to another handPile.

	// POST: Program will attempt to complete the intentions of the user with the help of one of two verification functions that will
	//		 be passed the card(s) moving and the cards the moving cards will be going to. If the verification function deems the cards
	//		 to be a match a boolean value will be returned and the this function will complete the movement process.

	bool validMove = true;
	Card topCard;
	Card movingCard;

	// Acquire all cards that will be moved in current movement.
	Card * handPileBuffer = new Card[cardCount];
	for (int y = 0; y < cardCount; y++) {
		if (!handPile[currPileNumber].isEmpty()) {
			handPileBuffer[y] = handPile[currPileNumber].getCard();

			if (handPileBuffer[y].visible == false) // If any of the cards are not currently visible. Move is not valid.
				validMove = false;
		}
		else
			validMove = false;
	}
	if (!handPile[destPileNumber].isEmpty()) // Check if the destination handPile is empty.
		topCard = handPile[destPileNumber].getCard(); // Acquire the topCard of the pile the cards will be moved to.
	else
		topCard.value = 0; // If destination pile is empty assign topCard the value of zero.

	movingCard = handPileBuffer[cardCount - 1];	// Acquire the buriedCard that will be moved.

	if (validateToHandMove(movingCard.value, topCard.value) && validMove == true) {
		// Move is valid. Alter stacks to reflect users movement desire.
		// Adjust visibility of cards in handPile.
		if (topCard.value != 0)
			handPile[destPileNumber].putCard(topCard); // Return the card that was originally first in the stack back to its place.

		for (int y = cardCount; y > 0; y--) {
			handPileBuffer[y - 1].visible = true; // Alter visibility.
			handPile[destPileNumber].putCard(handPileBuffer[y - 1]); // Add card being moved to destination pile.
		}
		Card temp = handPile[currPileNumber].getCard(); // Adjust visibility of the now top card in handPile.
		temp.visible = true;
		handPile[currPileNumber].putCard(temp);
	}
	else { // Invalid move. Return cards to original handPile.
		for (int y = cardCount; y > 0; y--)
			handPile[currPileNumber].putCard(handPileBuffer[y - 1]);

		handPile[destPileNumber].putCard(topCard);
		cout << "Invalid Move." << endl;
	}
	delete[] handPileBuffer; // Delete dynamic handPileBuffer Array. 
}

void targetToHand(TargetPile * targetPile, HandPile * handPile, int currPileNumber, int destPileNumber) {

	// PRE: Deck has been created, handPiles made and menu has been called at least once. User provided information
	//		that suggested an intent to move a card currently in the targetPile to a hand pile.

	// POST: Program will attempt to complete the intentions of the user with the help of one of two verification functions that will
	//		 be passed the card(s) moving and the cards the moving cards will be going to. If the verification function deems the cards
	//		 to be a match a boolean value will be returned and the this function will complete the movement process.

	bool validMove = true;
	Card topCard;
	Card movingCard;

	if (!handPile[destPileNumber].isEmpty()) // Check if the destination handPile is empty.
		topCard = handPile[destPileNumber].getCard(); // Acquire the topCard of the pile the cards will be moved to.
	else
		topCard.value = 0; // If destination pile is empty assign topCard the value of zero.

	if (!targetPile[currPileNumber].isEmpty()) // Check if the targetPile is empty
		movingCard = targetPile[currPileNumber].getCard(); // Acquire the card that will be moved.
	else
		validMove = false; // User is attempting to move nonexistant card.

	if (validateToHandMove(movingCard.value, topCard.value) && validMove == true) { // validate moving card from handPile to targetPile.
		handPile[destPileNumber].putCard(topCard); // Return the card that was originally first in the stack back to its place.
		handPile[destPileNumber].putCard(movingCard); // Add card being moved to destination pile.
	}
	else { // Invalid move.
		cout << "Invalid Move." << endl;
		validMove = false;
		targetPile[currPileNumber].putCard(movingCard); // Return card to targetPile.
		handPile[destPileNumber].putCard(topCard); // Return card to handPile.
	}
}

bool validateToHandMove(int buriedCard, int topCard) {

	// PRE: Deck has been created, handPiles made and menu has been called at least once. moveCard function executed
	//		and user chose to move a card to one of their handPiles. Function is sent a copy of the integer value pertaining
	//		to the card that is moving, and the card that the moving card is moving to.

	// POST: Function will return a boolean value relating to the legality of the move suggested by the user. The boolean 
	//		 value is then tested by the moveCard function to either continue with the move or return the cards to their
	//		 original piles prior to the users attempted illegal move. 

	bool validMove = false;

	if (topCard == 0) // Destination pile is currently empty. All moves possible.
		validMove = true;

	else if (topCard > 0 && topCard <= 13) { // TopCard is of suite Spades.

		if ((buriedCard - 26) == (topCard - 1))
			validMove = true;	// buriedCard is Hearts and one less than topCard.

		else if ((buriedCard - 39) == (topCard - 1))
			validMove = true;	// buriedCard is Diamonds and one less than topCard
		else
			validMove = false;
	}	
	else if (topCard > 13 && topCard <= 26) { // TopCard is of suite Clubs.

		if ((buriedCard - 26) == (topCard - 14))
			validMove = true;	// buriedCard is Hearts and one less than topCard.

		else if ((buriedCard - 39) == (topCard - 14))
			validMove = true;	// buriedCard is Diamonds and one less than topCard
		else
			validMove = false;

	}	
	else if (topCard > 26 && topCard <= 39) { // TopCard is of suite Hearts.

		if ((buriedCard) == (topCard - 27))
			validMove = true;	// buriedCard is of Spades and one less than topCard.

		else if ((buriedCard - 13) == (topCard - 27))
			validMove = true;	// buriedCard is of Clubs and one less than topCard.
		else
			validMove = false;
	}
	else { // TopCard is of suite Diamonds.
		if ((buriedCard) == (topCard - 40))
			validMove = true;	// buriedCard is of Spades and one less than topCard.

		else if ((buriedCard - 13) == (topCard - 40))
			validMove = true;	// buriedCard is of Clubs and one less than topCard.
		else
			validMove = false;
	}
	// Return result of move validation.
	return validMove;
}

bool validateToTargetMove(int buriedCard, int topCard) {

	// PRE: Deck has been created, handPiles made and menu has been called at least once. moveCard function executed
	//		and user chose to move a card to one of their targetPiles. Function is sent a copy of the integer value pertaining
	//		to the card that is moving, and the card that the moving card is moving to.

	// POST: Function will return a boolean value relating to the legality of the move suggested by the user. The boolean 
	//		 value is then tested by the moveCard function to either continue with the move or return the cards to their
	//		 original piles prior to the users attempted illegal move. 

	bool validMove = false;

	// If there is currently no card in targetPile, ensure card moving to pile is an ace of any suite.
	if (topCard == 0 && (buriedCard == 1 || buriedCard == 14 || buriedCard == 27 || buriedCard == 40))
		validMove = true;

	// All other cards moving to a specific targetPile must share the same suite, and ascend numerically.
	else if (topCard >= 1 && topCard < 14) { // TopCard of suite Spades.
		if (buriedCard == (topCard + 1)) // Ensure card moving to targetPile is one greater in value.
			validMove = true;
	}
	else if (topCard >= 14 && topCard < 27) { // TopCard of suite Clubs.
		if (buriedCard == (topCard + 1)) // Ensure card moving to targetPile is one greater in value.
			validMove = true;
	}
	else if (topCard >= 27 && topCard < 40) { // TopCard of suite Hearts.
		if (buriedCard == (topCard + 1)) // Ensure card moving to targetPile is one greater in value.
			validMove = true;
	}
	else if (topCard >= 40 && topCard < 53) { // TopCard of suite Diamonds.
		if (buriedCard == (topCard + 1)) // Ensure card moving to targetPile is one greater in value.
			validMove = true;
	}
	else
		validMove = false;
	return validMove; // Return result.
}

void displayPlayingField(stack<Card> & deck, DrawPile & drawPile, TargetPile * targetPile, HandPile * handPile) {

	// PRE: Deck has been created, handPiles made and menu has been called at least once. 

	// POST: With the help of a small external non STL library this function will display the current status
	//		 of the game field. 

	// Acquire the size of the largest handPile.
	int handPileMaxSize = handPile[0].isFull();
	for (int x = 0; x < 7; x++) {
		if (handPile[x].isFull() > handPileMaxSize) 
			handPileMaxSize = handPile[x].isFull();
	}

	// Acquire cards currently in hand piles. This will remove cards from the actual handPile stacks.
	// Thus, they will need to be replaced at the end of this function call.
	Card ** handField = new Card*[7];
	for (int x = 0; x < 7; x++) {
		handField[x] = new Card[handPileMaxSize];
		for (int y = handPile[x].isFull(); y > 0; y--)
			handField[x][y - 1] = handPile[x].getCard();
	}

	// Similar operation to the above for handPile, except for targetPile.
	Card * targetField = new Card[4];
	for (int x = 0; x < 4; x++) {
		if (!targetPile[x].isEmpty())
			targetField[x] = targetPile[x].getCard();
		else
			targetField[x].value = 0;
	}

	Card drawPileTemp = drawPile.getCard();

	// Game field
	cout << left << setw(10) << "\nDeck" << setw(20) << "Draw Pile" << setw(10)
		<< "TPile 1" << setw(10) << "TPile 2" << setw(10) << "TPile 3" << setw(10) << "TPile 4" << endl;
	cout << "---------------------------------------------------------------------" << endl;

	// Display card on top of deck and card at draw pile.
	cout << left << '#' << setw(9) << deck.size();
	cardConvert(drawPileTemp); 
	cout << "          ";
	
	// Display cards in targetPile using targetField array to avoid pulling cards from empty stacks.
	for (int x = 0; x < 4; x++) 
		cardConvert(targetField[x]);

	cout << left << setw(12) << "\n\nH1" << setw(10) << "H2" << setw(10) << "H3" << setw(10) << "H4"
		<< setw(10) << "H5" << setw(10) << "H6" << setw(10) << "H7" << endl;
	cout << "---------------------------------------------------------------------" << endl;

	// Similar operation as the above with targetField, except for handField. (Display)
	for (int y = 0; y < handPileMaxSize; y++) {
		for (int x = 0; x < 7; x++) {

			if (handField[x][y].value > 0 && handField[x][y].value < 53 && handField[x][y].visible == true)
				cardConvert(handField[x][y]); // Display value of card if card is currently visible.
			else if (handField[x][y].value > 0 && handField[x][y].value < 53 && handField[x][y].visible == false)
				cout << left << setw(10) << "0         "; // Display 0 if card value is currently not visible.
			else
				cout << left << setw(10) << "          ";
		}
		cout << endl;
	}
	// End of game field code

	// Placing the displayed handPile cards back into their piles
	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < handPileMaxSize; y++) {
			if (handField[x][y].value > 0 && handField[x][y].value < 53)
				handPile[x].putCard(handField[x][y]);
		}
	}	
	// Return targetPile cards to their stacks.
	for (int x = 0; x < 4; x++) {
		if (targetField[x].value != 0)
			targetPile[x].putCard(targetField[x]);
	}
	// Return drawPile card to its pile.
	drawPile.putCard(drawPileTemp);

	// delete 2D dynamic handField array
	for (int x = 0; x < 7; x++) 
		delete[] handField[x];
	delete[] handField;

	// delete targetField array
	delete[] targetField;

	cout << endl;
}

void cardConvert(Card card) {

	// PRE: Deck has been created, handPiles made, menu has been called at least once and user decided to display the playing field.

	// POST: Output will be displayed to the commandline depending on the card that was sent by the diplayField function.

	if (card.value > 0 && card.value <= 13) // Card is of suite Clubs.

		cout << left << "S" << setw(9) << card.value; // Display suite identifier alongside value of card.

	else if (card.value > 13 && card.value <= 26) // Card is of suite Spades.

		cout << left << "C" << setw(9) << (card.value - 13); // Display suite identifier alongside value of card.

	else if (card.value > 26 && card.value <= 39) // Card is of suite Hearts.

		cout << left <<  "H" << setw(9) << (card.value - 26); // Display suite identifier alongside value of card.

	else if (card.value > 39 && card.value <= 52) // Card is of suite Diamonds.

		cout << left << "D" << setw(9) << (card.value - 39); // Display suite identifier alongside value of card.

	else // Card is nonexistant
		cout << left << setw(10) <<  "0";
}