#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Cards.h"
using namespace std;



void play_game()

{
	int starting_money = 0;
	int bet = 0;
	char another_card = 'y';

	cout << "Welcome to Siete y Medio!" << endl
		<< "Enter your starting money: ";
	cin >> starting_money;

	Player you(starting_money);
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

		cout << "Your card:" << endl;
		you.draw_card();

		while (another_card == 'y')
		{

			cout << "Your total is " << you.card_total() << endl << ". Do you want another card (y/n)? ";
			cin >> another_card;
			if (another_card == 'n')
				return;
			else
			{
				cout << "New card: " << endl;
				you.draw_card();
				cout << "Your cards:" << endl;
				you.list_cards();
			}

			if (you.check_lose())
			{
				cout << "Your total is " << you.card_total() << "You lost the round.";
				you.lose_bet(bet);
			}
		}



	} while (you.check_end());
}
int main() 

{	
	//test

	play_game();

	/*Player you;
	you.draw_card();
	you.draw_card();
	you.draw_card();

	you.list_cards();
	return 0;*/
}