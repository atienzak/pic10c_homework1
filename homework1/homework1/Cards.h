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


class Hand 
{
public:
	
	Hand();
	double card_total();
	void add_card(Card* newcard);

private:
	vector<Card*> myhand;
};


class Player 
{
public:
	// default constructor
	Player();
	//constructor, assigns initial value of money
	Player(int m);
	void draw_card();
	bool check_lose(); // check if lost round (ie. card total is more than 7.5)
	bool check_end(); // check if end whole game
	bool operator < (Player another); // compare who won between two players based on value of cards
	int get_money();
	void win_bet(int a);
	void lose_bet(int b);

private:
	int money;
	Hand all_cards;
};




#endif
