#include "connectfour.h"
#include "board.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void ConnectFour::Play()
{
	system("cls");
	cout << "Welcome to Connect Four!\n"
		<< "\n"
		<< "To select an option, enter the number left of the option.\n"
		<< "1) Human vs Human\n"
		<< "2) Human vs AI\n"
		<< "3) AI vs AI\n"
		<< endl;
	string input;
	getline(cin, input);
	if (input == "1")
	{
		HumanVsHuman();
	}
	else if (input == "2")
	{
		HumanVsAI();
	}
	else if (input == "3")
	{
		AIVsAI();
	}
	else
	{
		cout << "That was not a valid option." << endl;
	}
}
void ConnectFour::Train()
{

}
void ConnectFour::HumanVsHuman()
{
	system("cls");
	cout << "Loading...";
	Board b;
	string input;
	for (Board::z i = 0; b.Winner() == ' ' && !b.IsFull(); i++)
	{
		system("cls");
		cout << "Human vs Human\n"
			<< "\n"
			<< "Current Board:\n"
			<< b
			<< endl;
		cout << "Player " << i % 2 + 1 << "\'s turn (" << (i % 2 ? "o" : "x") << ").\n"
			<< "Enter a column (1-7) to place the next piece.\n"
			<< endl;
		getline(cin, input);
		while (!all_of(input.cbegin(), input.cend(), isdigit) && 0 < stoi(input) && stoi(input) << 8)
		{
			cout << "That was not a valid column.\n"
				<< "Enter a column (1-7) to place the next piece.\n"
				<< endl;
			getline(cin, input);
		}
		b.Place((i % 2 ? 'o' : 'x'), stoi(input));
	}
}
void ConnectFour::HumanVsAI()
{

}
void ConnectFour::AIVsAI()
{

}
