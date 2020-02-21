#include "connectfour.h"
#include "board.h"
#include "agent.h"
#include "random.h"
#include "rpo.h"
#include <iostream>
#include <string>
#include <random>

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
	while (input.length() != 1 ||
		!isdigit(input[0]) ||
		stoi(input) < 1 || 3 < stoi(input))
	{
		cout << "\nThat was not a valid option.\n"
			<< "To select an option, enter the number left of the option.\n"
			<< "1) Human vs Human\n"
			<< "2) Human vs AI\n"
			<< "3) AI vs AI\n"
			<< endl;
		getline(cin, input);
	}
	switch (stoi(input))
	{
	case 1:
		HumanVsHuman();
		break;
	case 2:
		HumanVsAI();
		break;
	case 3:
		AIVsAI();
		break;
	default:
		break;
	}
}
void ConnectFour::TrainDouble(ASRLC4& agent1, ASRLC4& agent2, size_t games)
{
	vector<pair<Board, Board::z>> moveset1, moveset2;
	random_device seeder;
	minstd_rand rng(seeder());
	size_t agent1Wins = 0, agent2Wins = 0, ties = 0;
	for (size_t gameCounter = 0; gameCounter < games; gameCounter++)
	{
		if (!(gameCounter % (games / 100)))
		{
			cout << "Games Played:\t" << gameCounter << "\n"
				<< "Agent 1 Wins:\t" << (double)agent1Wins / gameCounter * 100 << "%\n"
				<< "Agent 2 Wins:\t" << (double)agent2Wins / gameCounter * 100 << "%\n"
				<< "Ties:\t\t" << (double)ties / gameCounter * 100 << "%\n"
				<< endl;
		}
		bool agent1First = rng() % 2;
		Board b;
		for (unsigned short i = 0; b.Winner() == ' ' && !b.IsFull(); i++)
		{
			if ((bool)(i % 2) != agent1First)
			{
				moveset1.push_back(make_pair(b, agent1.TakeTurn(b)));
				b.Place(agent1First ? 'x' : 'o', moveset1.back().second);
			}
			else
			{
				moveset2.push_back(make_pair(b, agent2.TakeTurn(b)));
				b.Place(agent1First ? 'o' : 'x', moveset2.back().second);
			}
		}
		if (b.Winner() == 'x')
		{
			agent1.Learn(moveset1, agent1First ? ASRLC4::Result::win : ASRLC4::Result::loss);
			agent1Wins += agent1First ? 1 : 0;
			agent2.Learn(moveset2, agent1First ? ASRLC4::Result::loss : ASRLC4::Result::win);
			agent2Wins += agent1First ? 0 : 1;
		}
		else if (b.Winner() == 'o')
		{
			agent1.Learn(moveset1, agent1First ? ASRLC4::Result::loss : ASRLC4::Result::win);
			agent1Wins += agent1First ? 0 : 1;
			agent2.Learn(moveset2, agent1First ? ASRLC4::Result::win : ASRLC4::Result::loss);
			agent2Wins += agent1First ? 1 : 0;
		}
		else
		{
			agent1.Learn(moveset1, ASRLC4::Result::tie);
			agent2.Learn(moveset2, ASRLC4::Result::tie);
			ties++;
		}
	}
}
void ConnectFour::TrainSingle(ASRLC4& agent1, Agent& agent2, size_t games)
{
	vector<pair<Board, Board::z>> moveset1;
	random_device seeder;
	minstd_rand rng(seeder());
	size_t agent1Wins = 0, agent2Wins = 0, ties = 0;
	for (size_t gameCounter = 0; gameCounter < games; gameCounter++)
	{
		if (!(gameCounter % (games / 100)))
		{
			cout << "Games Played:\t" << gameCounter << "\n"
				<< "Agent 1 Wins:\t" << (double)agent1Wins / gameCounter * 100 << "%\n"
				<< "Agent 2 Wins:\t" << (double)agent2Wins / gameCounter * 100 << "%\n"
				<< "Ties:\t\t" << (double)ties / gameCounter * 100 << "%\n"
				<< endl;
		}
		bool agent1First = rng() % 2;
		Board b;
		for (unsigned short i = 0; b.Winner() == ' ' && !b.IsFull(); i++)
		{
			if ((bool)(i % 2) != agent1First)
			{
				moveset1.push_back(make_pair(b, agent1.TakeTurn(b)));
				b.Place(agent1First ? 'x' : 'o', moveset1.back().second);
			}
			else
			{
				b.Place(agent1First ? 'o' : 'x', agent2.TakeTurn(b));
			}
		}
		if (b.Winner() == 'x')
		{
			agent1.Learn(moveset1, agent1First ? ASRLC4::Result::win : ASRLC4::Result::loss);
			agent1Wins += agent1First ? 1 : 0;
			agent2Wins += agent1First ? 0 : 1;
		}
		else if (b.Winner() == 'o')
		{
			agent1.Learn(moveset1, agent1First ? ASRLC4::Result::loss : ASRLC4::Result::win);
			agent1Wins += agent1First ? 0 : 1;
			agent2Wins += agent1First ? 1 : 0;
		}
		else
		{
			agent1.Learn(moveset1, ASRLC4::Result::tie);
			ties++;
		}
	}
}
void ConnectFour::HumanVsHuman()
{
	system("cls");
	cout << "Loading...";
	Board b;
	string input;
	for (unsigned short i = 0; b.Winner() == ' ' && !b.IsFull(); i++)
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
		while (input.length() != 1 ||
			!isdigit(input[0]) ||
			stoi(input) < 1 || 7 < stoi(input) ||
			b.IsFullColumn(stoi(input)))
		{
			cout << "\nThat was not a valid column.\n"
				<< "Enter a column (1-7) to place the next piece.\n"
				<< endl;
			getline(cin, input);
		}
		b.Place((i % 2 ? 'o' : 'x'), stoi(input));
	}
	system("cls");
	if (b.Winner() != ' ')
	{
		cout << "The winner is " << (b.MarkWinner() == 'x' ? "Player 1 (x)" : "Player 2 (o)") << "!\n";
	}
	else
	{
		cout << "It is a tie!\n";
	}
	cout << "\n"
		<< "Final Board:\n"
		<< b
		<< endl;
}
void ConnectFour::HumanVsAI()
{
	system("cls");
	cout << "Loading...";
	Board b;
	string input;
	Agent* agent = nullptr;
	bool playerFirst = true;
	system("cls");
	cout << "Human vs AI\n"
		<< "\n"
		<< "To select an AI, enter the number left of the AI\'s name.\n"
		<< "1) Caprice\n"
		<< "2) Eclair\n"
		<< endl;
	getline(cin, input);
	while (input.length() != 1 ||
		!isdigit(input[0]) ||
		stoi(input) < 1 || 2 < stoi(input))
	{
		cout << "\nThat was not a valid option.\n"
			<< "To select an AI, enter the number left of the AI\'s name.\n"
			<< "1) Caprice\n"
			<< "2) Eclair\n"
			<< endl;
		getline(cin, input);
	}
	switch (stoi(input))
	{
	case 1:
		agent = new Random;
		break;
	case 2:
		agent = new RpO;
	}
	system("cls");
	cout << "Human vs AI\n"
		<< "\n"
		<< "To select a turn order, enter the number left of the option.\n"
		<< "1) Human is Player 1 and goes first.\n"
		<< "2) AI is Player 1 and goes first.\n"
		<< "3) Player 1 is randomly selected.\n"
		<< endl;
	getline(cin, input);
	while (input.length() != 1 ||
		!isdigit(input[0]) ||
		stoi(input) < 1 || 3 < stoi(input))
	{
		cout << "\nThat was not a valid option.\n"
			<< "To select a turn order, enter the number left of the option.\n"
			<< "1) Human is Player 1 and goes first.\n"
			<< "2) AI is Player 1 and goes first.\n"
			<< "3) Player 1 is randomly selected.\n"
			<< endl;
		getline(cin, input);
	}
	switch (stoi(input))
	{
	case 1:
		playerFirst = true;
		break;
	case 2:
		playerFirst = false;
		break;
	case 3:
		random_device rng;
		playerFirst = (bool)(rng() % 2);
	}
	for (unsigned short i = 0; b.Winner() == ' ' && !b.IsFull(); i++)
	{
		if ((bool)(i % 2) != playerFirst)
		{
			system("cls");
			cout << "Human vs AI\n"
				<< "\n"
				<< "Current Board:\n"
				<< b
				<< endl;
			cout << "Player " << (playerFirst ? 1 : 2) << "\'s turn (" << (playerFirst ? "x" : "o") << ").\n"
				<< "Enter a column (1-7) to place the next piece.\n"
				<< endl;
			getline(cin, input);
			while (input.length() != 1 ||
				!isdigit(input[0]) ||
				stoi(input) < 1 || 7 < stoi(input) ||
				b.IsFullColumn(stoi(input)))
			{
				cout << "\nThat was not a valid column.\n"
					<< "Enter a column (1-7) to place the next piece.\n"
					<< endl;
				getline(cin, input);
			}
			b.Place((playerFirst ? 'x' : 'o'), stoi(input));
		}
		else
		{
			b.Place(playerFirst ? 'o' : 'x', agent->TakeTurn(b));
		}
	}
	system("cls");
	if (b.Winner() != ' ')
	{
		cout << "The winner is " << (b.MarkWinner() == 'x' ? "Player 1 (x)" : "Player 2 (o)") << "!\n";
	}
	else
	{
		cout << "It is a tie!\n";
	}
	cout << "\n"
		<< "Final Board:\n"
		<< b
		<< endl;
	delete agent;
}
void ConnectFour::AIVsAI()
{

}
