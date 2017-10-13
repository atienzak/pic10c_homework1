#include <string>
#include <vector>
#include <fstream>

#ifndef CARDS_H
#define CARDS_H

using namespace std;

enum suit_t { OROS, COPAS, ESPADAS, BASTOS };

/*
The values for this type start at 0 and increase by one
afterwards until they get to SIETE.
The rank reported by the function Card::get_rank() below is
the value listed here plus one.
E.g:
The rank of AS is reported as    static_cast<int>(AS) + 1   = 0 + 1 =  1
The rank of SOTA is reported as  static_cast<int>(SOTA) + 1 = 9 + 1 = 10
*/
enum rank_t { AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA = 9, CABALLO = 10, REY = 11 };

class Card {
public:
	// Constructor assigns random rank & suit to card.
	Card();

	// Accessors 
	string get_spanish_suit() const;
	string get_spanish_rank() const;

	// Accessors (returns suit and rank in English)
	string get_english_suit() const;
	string get_english_rank() const;

	// Converts card rank to number.
	// The possible returns are: 1, 2, 3, 4, 5, 6, 7, 10, 11 and 12
	int get_rank() const;

	double get_value() const;

	// Compare rank of two cards. E.g: Eight<Jack is true.
	// Assume Ace is always 1. 
	// Useful if you want to sort the cards.
	bool operator < (Card card2) const;

private:
	suit_t suit;
	rank_t rank;
};

//consolidated Hand class into Player because it only contains a vector of Card* as a private member 

class Player 
{
public:
	// default constructor
	Player();

	/*
		constructor, assigns initial value of money
		@param m initial amount of money
	*/
	Player(int m);

	/**
		computes the total of the value of the cards 
		@return value of the card
	*/
	double card_total() const;

	/**
		adds another card into the hand by pushing back a Card*
	*/
	void draw_card();

	/**
		deletes all cards that have been added
		used after the end of each round
	*/
	void reset_cards();

	/**
		checks if player loses the round (ie. card total is more than 7.5)
		@return true if lost, false if not
	*/
	bool check_lose() const;

	/**
		checks if the game has reached its end (ie. money == 0)
		@return true if game is finished, false if not
	*/
	bool check_end() const;

	/**
		compares who won between the two players based on the total value of their cards
		@param another the player with whom to compare
		@return true if rhs player has a total higher than the lhs player but lower than 7.5
	*/
	bool operator < (const Player& another) const;

	/**
		accessor for money
		@return the value of money the player has currently
	*/
	int get_money() const;

	/**
		sets money of the player
		@param money to be set
	*/
	void set_money(const int& a);

	/**
		adds bet to the money
		@param a amount of bet won
	*/
	void win_bet(const int& a);

	/**
		subtracts bet from money
		@param b amount of money lost
	*/
	void lose_bet(const int& b);

	/**
		list cards into the console using cout
	*/
	void list_cards() const;

	/**
		list cards into an ostream object to be used when logging into a txt file
		@param ost ostream object to write into the txt file
	*/
	void log_cards(ostream& ost) const;
	

private:
	
	//player's money, set by constructors
	int money;

	//cards by the player 
	vector<Card*> myhand;
};

//functions needed to play the game

/**
	sets the bet to 0, and "do you want another card (y/n)?" back to y
	@bet amount of bet to be reset to 0
	@another_card sets y/n to y
*/
void reset_round(int& bet, char& another_card);

/**
	writes into the text file the information about the game
	@param you the main player
	@param dealer the dealer against whom the player is playing 
	@param ost the ostream object that would be used to log the files into
	@bet the amount of bet in that round
	@round_number the round number 
*/
void log_file(const Player& you, const Player& dealer, ofstream& ost, const int& bet, int& round_number);

/**
	the main function that executes the game
	@param you the main player
	@param dealer the dealer against whom the player is playing
*/
void play_game(Player& you, Player& dealer);

#endif
