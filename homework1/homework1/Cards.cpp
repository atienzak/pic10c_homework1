#include "Cards.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <iomanip>

/* *************************************************
Card class
************************************************* */

// Constructor assigns random rank & suit to card.

Card::Card() {
	srand(time(0)); // seed 

	// time delay is added so that random cards would be drawn by the computer (ie. not on the same second)
	int r = 1 + rand() % 3; 

	if (r == 1)
	{
		Sleep(1000);
	}
	else if (r == 2)
	{
		Sleep(2000);
	}
	else
	{
		Sleep(3000);
	}

	r = 1 + rand() % 4;
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

// returns the corresponding values of the cards 
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

// constructors, one with initial money
Player::Player() : myhand({}), money(0) {}

Player::Player(int m) : myhand({}), money(m) {}

/**
	computes the total of the value of the cards
	@return value of the card
*/
double Player::card_total() const
{

	double total = 0;
	for (const auto& x : myhand) // add every value of card to total
	{
		total += x->get_value();
	}
	return total;

}

/**
	adds another card into the hand by pushing back a Card*
*/
void Player::draw_card()
{
	Card* newcard = new Card(); 
	myhand.push_back(newcard);
	return;
}

/**
	checks if player loses the round (ie. card total is more than 7.5)
	@return true if lost, false if not
*/
bool Player::check_lose() const
{
	if (card_total() > 7.5)
		return true;
	else
		return false;
}

/**
	checks if the game has reached its end (ie. money == 0)
	@return true if game is finished, false if not
*/
bool Player::check_end() const
{
	if (money == 0)
		return true;
	else
		return false;
}

/**
	compares who won between the two players based on the total value of their cards
	@param another the player with whom to compare
	@return true if rhs player has a total higher than the lhs player but lower than 7.5
*/
bool Player::operator < (const Player& another) const
{
	return (card_total() < another.card_total());
}

/**
	accessor for money
	@return the value of money the player has currently
*/
int Player::get_money() const
{
	return money;
}


/**
	sets money of the player
	@param money to be set
*/
void Player::set_money(const int& a)
{
	money = a;
	return;
}

/**
	adds bet to the money
	@param a amount of bet won
*/
void Player::win_bet(const int& a)
{
	money += a;
	return;
}

/**
	subtracts bet from money
	@param b amount of money lost
*/
void Player::lose_bet(const int& b)
{
	money -= b;
	return;
}

/**
	list cards into the console using cout
*/
void Player::list_cards() const // list cards in their names in spanish and english
{
	string line_up = "";

	for (const auto& x : myhand) // for every card, cout
	{
		line_up = x->get_spanish_rank() + " de " + x->get_spanish_suit(); // i want the setw to apply to this whole string

		cout << "\t" << left << setw(20) << line_up << "(" << x->get_english_rank() << " of " << x->get_english_suit() << ")" << endl;
	}
	return;
}

/**
	list cards into an ostream object to be used when logging into a txt file
	@param ost ostream object to write into the txt file
*/
void Player::log_cards(ostream& ost) const
{
	string line_up = "";

	for (const auto& x : myhand) // for every card, put into ost
	{
		line_up = x->get_spanish_rank() + " de " + x->get_spanish_suit(); // i want the setw to apply to this whole string
		ost << "\t" << left << setw(20) << line_up << "(" << x->get_english_rank() << " of " << x->get_english_suit() << ")" << endl;
	}

	return;
}

/**
	deletes all cards that have been added
	used after the end of each round
*/
void Player::reset_cards()
{
	for (vector<Card*>::iterator itr = myhand.begin(); itr != myhand.end(); ++itr)
		delete *itr;
	myhand = {};

	return;
}

/*************************************
	Functions needed to play the game
**************************************/


/**
	sets the bet to 0, and "do you want another card (y/n)?" back to y
	@bet amount of bet to be reset to 0
	@another_card sets y/n to y
*/
void reset_round(int& bet, char& another_card)
{
	bet = 0;
	another_card = 'y';
}

/**
	writes into the text file the information about the game
	@param you the main player
	@param dealer the dealer against whom the player is playing
	@param ost the ostream object that would be used to log the files into
	@bet the amount of bet in that round
	@round_number the round number
*/
void log_file(const Player& you, const Player& dealer, ofstream& ost, const int& bet, int& round_number)
{
	ost.open("log_file.txt", ios::app);

	ost << "---------------------------------------------\n\nRound number: " << round_number
		<< "\tMoney left: $" << you.get_money() + bet << "\nBet: $" << bet
		<< "\n\nYour cards: \n";

	you.log_cards(ost);

	ost << "Your total: " << you.card_total() << ".\n\n";

	if (dealer.card_total() != 0) // if the player went over 7.5 at the start of the round, then dealer wouldn't have any cards 
	{
		ost << "Dealer's cards: \n";

		dealer.log_cards(ost);

		ost << "Dealer's total: " << dealer.card_total() << ".\n";
	}

	ost.close();

}

/**
	the main function that executes the game
	@param you the main player
	@param dealer the dealer against whom the player is playing
*/
void play_game(Player& you, Player& dealer)
{
	int starting_money = 0;
	int bet = 0;
	char another_card = 'y';
	int round_number = 0; 
	ofstream ost; // used for logging into file; declared here so that it wouldn't create ostream onject repeatedly when log_file function is called

	cout << "Welcome to Siete y Medio!\n" << endl
		<< "Enter your starting money: ";
	cin >> starting_money;
	cout << "\n";

	you.set_money(starting_money);

	do
	{
		cout << "You have $" << you.get_money() << ". Enter bet: ";
		cin >> bet;
		cout << "\n";

		// if bet is higher than amount of money, prompt player for a valid input
		while (bet > you.get_money() || bet == 0)
		{
			cout << "Enter a valid bet: ";
			cin >> bet;
		}

		// player adds card to his hands
		while (another_card == 'y')
		{
			cout << "Your cards: " << endl;
			you.draw_card();
			you.list_cards();

			cout << "Your total is " << you.card_total() << ". ";

			if (you.check_lose()) // if player went over 7.5, end the round before dealer draws cards  
			{
				cout << "You lost the round. You lose $" << bet << "." << "\n\n";
				you.lose_bet(bet);
				break;
			}

			cout << "Do you want another card (y/n)? ";
			cin >> another_card;
			cout << "\n";

			if (another_card == 'n') // player doesn't want another card
				break;
		}

		while (!you.check_lose() && dealer.card_total() <= you.card_total()) // if the player hasn't gone over 7.5 yet and
																			 // the dealer's card hasn't gone over the player's total,
																			 // then draw more cards
		{
			cout << "Dealer's cards:" << endl;
			dealer.draw_card();
			dealer.list_cards();
			cout << "The dealer's total is " << dealer.card_total() << ".\n\n";

			if (dealer.check_lose())
			{
				cout << "Congratulations! You won $" << bet << "." << "\n\n";
				you.win_bet(bet);
				break;
			}

			else if (you.card_total() < dealer.card_total())
			{
				cout << "You lost the round. You lose $" << bet << "." << "\n\n";
				you.lose_bet(bet);
				break;
			}

			else if (you.card_total() == dealer.card_total())
			{
				cout << "It's a tie!\n\n";
				break;
			}

			cout << "The dealer is drawing another card...\n\n";
		}

		if (you.check_end())
		{
			cout << "You are out of money. Goodbye!\n\n";
		}

		round_number++;
		log_file(you, dealer, ost, bet, round_number);

		reset_round(bet, another_card);
		you.reset_cards(); // reset rounds 
		dealer.reset_cards();

	} while (!you.check_end());


}