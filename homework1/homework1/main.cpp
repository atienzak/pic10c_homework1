#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Cards.h"
using namespace std;

void reset_round(int& bet, char& another_card)
{
	bet = 0;
	another_card = 0;
}

void log_file(const Player& you, const Player& dealer, ofstream& ost, const int& bet, int& round_number)
{
	ost.open("log_file.txt", ios::app);

	ost << "---------------------------------------------\n\nRound number: " << round_number
		<< "\tMoney left: $" << you.get_money() + bet << "\nBet: $" << bet
		<< "\n\nYour cards: \n";

	you.log_cards(ost);

	ost << "Your total: " << you.card_total() << ".\n\n";

	if (dealer.card_total() != 0) // meaning that that player didn't go over 7.5
	{
		ost << "Dealer's cards: \n";

		dealer.log_cards(ost);

		ost << "Dealer's total is " << dealer.card_total() << ".\n";
	}

	ost.close();

}

void play_game()

{
	int starting_money = 0;
	int bet = 0;
	char another_card = ' ';
	int round_number = 0; // for log file 
	ofstream ost;

	cout << "Welcome to Siete y Medio!\n" << endl
		<< "Enter your starting money: ";
	cin >> starting_money;
	cout << "\n";

	Player you(starting_money);
	Player dealer;

	do
	{	
		cout << "You have $" << you.get_money() << ". Enter bet: ";
		cin >> bet;
		cout << "\n";

		another_card = 'y';

		while (bet > you.get_money() || bet == 0)
		{
			cout << "Enter a valid bet: ";
			cin >> bet;
		}

		while (another_card == 'y')
		{

			cout << "Your cards: " << endl;
			you.draw_card();
			you.list_cards();

			cout << "Your total is " << you.card_total() << ". ";
				
			if (you.check_lose())
			{
				cout << "You lost the round. You lose $" << bet << "." << "\n\n";
				you.lose_bet(bet);
				break;
			}

			cout << "Do you want another card (y/n)? ";
			cin >> another_card;
			cout << "\n";

			if (another_card == 'n')
				break; 

		}

		while (!you.check_lose() && dealer.card_total() <= you.card_total())
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
		}

		if (you.check_end())
		{
			cout << "You are out of money. Goodbye!\n\n";
		}

		round_number++;
		log_file(you, dealer, ost, bet, round_number);

		you.reset_cards(); // reset rounds 
		dealer.reset_cards();

	} while (!you.check_end());


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