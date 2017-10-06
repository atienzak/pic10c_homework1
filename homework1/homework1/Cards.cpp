#include "Cards.h"
#include <cstdlib>
#include <iostream>

/*
You might or might not need these two extra libraries
#include <iomanip>
#include <algorithm>
*/


/* *************************************************
Card class
************************************************* */

/*
Default constructor for the Card class.
It could give repeated cards. This is OK.
Most variations of Blackjack are played with
several decks of cards at the same time.
*/
Card::Card() {
	int r = 1 + rand() % 4;
	switch (r) {
	case 1: suit = OROS; break;
	case 2: suit = COPAS; break;
	case 3: suit = ESPADAS; break;
	case 4: suit = BASTOS; break;
	default: break;
	}

	r = 1 + rand() % 10;
	switch (r) {
	case  1: rank = AS; break;
	case  2: rank = DOS; break;
	case  3: rank = TRES; break;
	case  4: rank = CUATRO; break;
	case  5: rank = CINCO; break;
	case  6: rank = SEIS; break;
	case  7: rank = SIETE; break;
	case  8: rank = SOTA; break;
	case  9: rank = CABALLO; break;
	case 10: rank = REY; break;
	default: break;
	}
}

// Accessor: returns a string with the suit of the card in Spanish 
string Card::get_spanish_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "oros";
		break;
	case COPAS:
		suitName = "copas";
		break;
	case ESPADAS:
		suitName = "espadas";
		break;
	case BASTOS:
		suitName = "bastos";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in Spanish 
string Card::get_spanish_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "As";
		break;
	case DOS:
		rankName = "Dos";
		break;
	case TRES:
		rankName = "Tres";
		break;
	case CUATRO:
		rankName = "Cuatro";
		break;
	case CINCO:
		rankName = "Cinco";
		break;
	case SEIS:
		rankName = "Seis";
		break;
	case SIETE:
		rankName = "Siete";
		break;
	case SOTA:
		rankName = "Sota";
		break;
	case CABALLO:
		rankName = "Caballo";
		break;
	case REY:
		rankName = "Rey";
		break;
	default: break;
	}
	return rankName;
}


// Accessor: returns a string with the suit of the card in English 

string Card::get_english_suit() const 
{
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "Coins";
		break;
	case COPAS:
		suitName = "Cups";
		break;
	case ESPADAS:
		suitName = "Swords";
		break;
	case BASTOS:
		suitName = "Clubs";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in English 

string Card::get_english_rank() const 
{
	string rankName;
	switch (rank) {
	case AS:
		rankName = "Ace";
		break;
	case DOS:
		rankName = "Two";
		break;
	case TRES:
		rankName = "Three";
		break;
	case CUATRO:
		rankName = "Four";
		break;
	case CINCO:
		rankName = "Five";
		break;
	case SEIS:
		rankName = "Six";
		break;
	case SIETE:
		rankName = "Seven";
		break;
	case SOTA:
		rankName = "Jack";
		break;
	case CABALLO:
		rankName = "Knight";
		break;
	case REY:
		rankName = "King";
		break;
	default: break;
	}
	return rankName;
}

double Card::get_value() const
{
	double value = 0;

	switch (rank) {
	case AS:
		value = 1;
		break;
	case DOS:
		value = 2;
		break;
	case TRES:
		value = 3;
		break;
	case CUATRO:
		value = 4;
		break;
	case CINCO:
		value = 5;
		break;
	case SEIS:
		value = 6;
		break;
	case SIETE:
		value = 7;
		break;
	case SOTA:
		value = 0.5;
		break;
	case CABALLO:
		value = 0.5;
		break;
	case REY:
		value = 0.5;
		break;
	default: break;
	}
	return value;
}

// Assigns a numerical value to card based on rank.
// AS=1, DOS=2, ..., SIETE=7, SOTA=10, CABALLO=11, REY=12
int Card::get_rank() const {
	return static_cast<int>(rank) + 1;
}

// Comparison operator for cards
// Returns TRUE if card1 < card2
bool Card::operator < (Card card2) const {
	return rank < card2.rank;
}




/* *************************************************
Player class
************************************************* */

Player::Player() : myhand({}), money(0) {}

Player::Player(int m) : myhand({}), money(m) {}

double Player::card_total()
{

	double total = 0;
	for (const auto& x : myhand)
	{
		total = x->get_value();
	}
	return total;

}


void Player::draw_card()
{
	Card* newcard = new Card(); 
	myhand.push_back(newcard);
	cout << "\t" << newcard->get_spanish_rank() << " de " << newcard->get_spanish_suit() << "\t ("
		<< newcard->get_english_rank() << " of " << newcard->get_english_suit() << ")" << endl;
	
}

bool Player::check_lose()
{
	if (card_total() > 7.5)
		return true;
	else
		return false;
}

bool Player::check_end()
{
	if (money == 0)
		return true;
	else
		return false;
}

bool Player::operator < (Player another)
{
	return (card_total() < another.card_total());
}

int Player::get_money()
{
	return money;
}
void Player::win_bet(int a)
{
	money -= a;
}
void Player::lose_bet(int b)
{
	money += b;
}

void Player::list_cards() // list cards in their names in spanish and english
{
	for (const auto& x : myhand)
	{
		cout << x->get_spanish_rank() << " de " << x->get_spanish_suit() << "\t (" 
			<< x->get_english_rank() << " of " << x->get_english_suit() << ")" << endl;
	}
}

void play_game()
{
	int starting_money = 0;
	int bet = 0;
	cout << "Welcome to Siete y Medio!" << endl
		<< "Enter your starting money: ";
	cin >> starting_money;
	
	Player you (starting_money);  
	Player dealer;
	
	do
	{ 
		cout << "You have $" << you.get_money() << ". Enter bet: ";
		cin >> bet;
		while (bet > you.get_money())
		{
			cout << "Enter a valid bet: ";
			cin >> bet;
		}

		cout << "Your card:"  << endl;
		you.draw_card();
		


	} while (you.check_end());
}


