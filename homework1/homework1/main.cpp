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

		cout << "Your cards:" << endl;
		you.draw_card();


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