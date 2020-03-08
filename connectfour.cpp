#include "connectfour.h"
#include "board.h"
#include "agent.h"
#include "random.h"
#include "rpo.h"
#include "minimax_defensive.h"
#include "minimax_all.h"
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
void ConnectFour::TestDouble(Agent& agent1, Agent& agent2, size_t games)
{
	random_device seeder;
	minstd_rand rng(seeder());
	size_t agent1Wins = 0, agent2Wins = 0, ties = 0;
	for (size_t gameCounter = 0; gameCounter < games; gameCounter++)
	{
		if ((games / 100 != 0) && !(gameCounter % (games / 100)))
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
				b.Place(agent1First ? 'x' : 'o', agent1.TakeTurn(b));
			}
			else
			{
				b.Place(agent1First ? 'o' : 'x', agent2.TakeTurn(b));
			}
		}
		if (b.Winner() == 'x')
		{
			agent1Wins += agent1First ? 1 : 0;
			agent2Wins += agent1First ? 0 : 1;
		}
		else if (b.Winner() == 'o')
		{
			agent1Wins += agent1First ? 0 : 1;
			agent2Wins += agent1First ? 1 : 0;
		}
		else
		{
			ties++;
		}
	}
	cout << "Games Played:\t" << games << "\n"
		<< "Agent 1 Wins:\t" << (double)agent1Wins / games * 100 << "%\n"
		<< "Agent 2 Wins:\t" << (double)agent2Wins / games * 100 << "%\n"
		<< "Ties:\t\t" << (double)ties / games * 100 << "%\n"
		<< endl;
}
void ConnectFour::PlayDouble(Agent& agent1, Agent& agent2)
{
	random_device seeder;
	minstd_rand rng(seeder());
	size_t agent1Wins = 0, agent2Wins = 0, ties = 0;
	bool agent1First = true;
	Board b;
	for (unsigned short i = 0; b.Winner() == ' ' && !b.IsFull(); i++)
	{
		cout << b << endl;

		if ((bool)(i % 2) != agent1First)
		{
			b.Place(agent1First ? 'x' : 'o', agent1.TakeTurn(b));
		}
		else
		{
			b.Place(agent1First ? 'o' : 'x', agent2.TakeTurn(b));
		}
	}
	if (b.Winner() == 'x')
	{
		agent1Wins += agent1First ? 1 : 0;
		agent2Wins += agent1First ? 0 : 1;
	}
	else if (b.Winner() == 'o')
	{
		agent1Wins += agent1First ? 0 : 1;
		agent2Wins += agent1First ? 1 : 0;
	}
	else
	{
		ties++;
	}

	cout << b << endl;
}
Minimax ConnectFour::Evolve(size_t populationSize, size_t gamesPerCompetition, size_t generations, long double startingWeight, long double mixingRatio, long double mutationRate)
{
	if (populationSize < 2)
	{
		throw exception("Nothing to evolve.");
	}

	random_device seeder;
	minstd_rand rng(seeder());

	vector<Minimax> agents;
	vector<size_t> fitnesses(populationSize);
	pair<size_t, size_t> roundWins;
	vector<EvaluationFunction::utility> zygote;

	size_t maxFitness;
	size_t maxFitnessIndex = 0;
	size_t secondFitness;
	size_t secondFitnessIndex = 0;

	for (size_t populationCounter = 0; populationCounter < populationSize; populationCounter++)
	{
		agents.emplace_back(1,
			startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(),
			startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(),
			startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(),
			startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(),
			startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max(), startingWeight * rng() / rng.max());
	}

	// compete and record fitnesses as # of wins
	fitnesses.clear();
	fitnesses.resize(populationSize);
	for (size_t populationCounter = 0; populationCounter < populationSize; populationCounter++)
	{
		for (size_t opponentCounter = populationCounter + 1; opponentCounter < populationSize; opponentCounter++)
		{
			roundWins = Compete(agents[populationCounter], agents[opponentCounter], gamesPerCompetition);
			fitnesses[populationCounter] += roundWins.first;
			fitnesses[opponentCounter] += roundWins.second;
		}
	}

	// find parents for next generation
	maxFitness = secondFitness = fitnesses[0];
	maxFitnessIndex = secondFitnessIndex = 0;
	for (size_t populationCounter = 1; populationCounter < populationSize; populationCounter++)
	{
		if (fitnesses[populationCounter] > maxFitness)
		{
			if (secondFitnessIndex != maxFitnessIndex)
			{
				secondFitness = maxFitness;
				secondFitnessIndex = maxFitnessIndex;
			}
			maxFitness = fitnesses[populationCounter];
			maxFitnessIndex = populationCounter;
		}
		else if (fitnesses[populationCounter] > secondFitness)
		{
			secondFitness = fitnesses[populationCounter];
			secondFitnessIndex = populationCounter;
		}
	}

	cout << "Generation:\t\t" << 0 << "\n";
	cout << "Parent 1 Win Rate:\t" << (long double)maxFitness / (gamesPerCompetition * (populationSize - 1)) << "\n"
		<< "Parent 2 Win Rate:\t" << (long double)secondFitness / (gamesPerCompetition * (populationSize - 1)) << "\n"
		<< endl;

	for (size_t geneCounter = 0; geneCounter < agents[maxFitnessIndex].Weights().size(); geneCounter++)
	{
		cout << agents[maxFitnessIndex].Weights()[geneCounter] << ' ';
	}
	cout << "\n" << endl;

	// loop per generation
	for (size_t generationCounter = 0; generationCounter < generations; generationCounter++)
	{
		// "sexual" reproduction... but can favor 1 parent over the other, i.e. not entirely fair
		zygote = Breed(agents[maxFitnessIndex].Weights(), agents[secondFitnessIndex].Weights(), mixingRatio);

		// initalize next generation
		agents.clear();
		for (size_t populationCounter = 0; populationCounter < populationSize; populationCounter++)
		{
			agents.emplace_back(1, Mutate(zygote, mutationRate));
		}

		// compete and record fitnesses as # of wins
		fitnesses.clear();
		fitnesses.resize(populationSize);
		for (size_t populationCounter = 0; populationCounter < populationSize; populationCounter++)
		{
			for (size_t opponentCounter = populationCounter + 1; opponentCounter < populationSize; opponentCounter++)
			{
				roundWins = Compete(agents[populationCounter], agents[opponentCounter], gamesPerCompetition);
				fitnesses[populationCounter] += roundWins.first;
				fitnesses[opponentCounter] += roundWins.second;
			}
		}

		// find parents for next generation
		maxFitness = secondFitness = fitnesses[0];
		maxFitnessIndex = secondFitnessIndex = 0;
		for (size_t populationCounter = 1; populationCounter < populationSize; populationCounter++)
		{
			if (fitnesses[populationCounter] > maxFitness)
			{
				if (secondFitnessIndex != maxFitnessIndex)
				{
					secondFitness = maxFitness;
					secondFitnessIndex = maxFitnessIndex;
				}
				maxFitness = fitnesses[populationCounter];
				maxFitnessIndex = populationCounter;
			}
			else if (fitnesses[populationCounter] > secondFitness)
			{
				secondFitness = fitnesses[populationCounter];
				secondFitnessIndex = populationCounter;
			}
		}

		cout << "Generation:\t\t" << generationCounter + 1 << "\n";
		cout << "Parent 1 Win Rate:\t" << (long double)maxFitness / (gamesPerCompetition * (populationSize - 1)) << "\n"
			<< "Parent 2 Win Rate:\t" << (long double)secondFitness / (gamesPerCompetition * (populationSize - 1)) << "\n"
			<< endl;

		for (size_t geneCounter = 0; geneCounter < agents[maxFitnessIndex].Weights().size(); geneCounter++)
		{
			cout << agents[maxFitnessIndex].Weights()[geneCounter] << ' ';
		}
		cout << "\n" << endl;
	}

	return agents[maxFitnessIndex];
}
Minimax ConnectFour::EvolveAgent(const Minimax& parent, size_t populationSize, size_t gamesPerCompetition, size_t generations, long double mixingRatio, long double mutationRate)
{
	if (populationSize < 2)
	{
		throw exception("Nothing to evolve.");
	}

	random_device seeder;
	minstd_rand rng(seeder());

	vector<Minimax> agents = { parent };
	vector<size_t> fitnesses(populationSize);
	pair<size_t, size_t> roundWins;
	vector<EvaluationFunction::utility> zygote;

	size_t maxFitness;
	size_t maxFitnessIndex = 0;
	size_t secondFitness;
	size_t secondFitnessIndex = 0;

	// loop per generation
	for (size_t generationCounter = 0; generationCounter < generations; generationCounter++)
	{
		// "sexual" reproduction... but can favor 1 parent over the other, i.e. not entirely fair
		zygote = Breed(agents[maxFitnessIndex].Weights(), agents[secondFitnessIndex].Weights(), mixingRatio);

		// initalize next generation
		agents.clear();
		for (size_t populationCounter = 0; populationCounter < populationSize; populationCounter++)
		{
			agents.emplace_back(1, Mutate(zygote, mutationRate));
		}

		// compete and record fitnesses as # of wins
		fitnesses.clear();
		fitnesses.resize(populationSize);
		for (size_t populationCounter = 0; populationCounter < populationSize; populationCounter++)
		{
			for (size_t opponentCounter = populationCounter + 1; opponentCounter < populationSize; opponentCounter++)
			{
				roundWins = Compete(agents[populationCounter], agents[opponentCounter], gamesPerCompetition);
				fitnesses[populationCounter] += roundWins.first;
				fitnesses[opponentCounter] += roundWins.second;
			}
		}

		// find parents for next generation
		maxFitness = secondFitness = fitnesses[0];
		maxFitnessIndex = secondFitnessIndex = 0;
		for (size_t populationCounter = 1; populationCounter < populationSize; populationCounter++)
		{
			if (fitnesses[populationCounter] > maxFitness)
			{
				if (secondFitnessIndex != maxFitnessIndex)
				{
					secondFitness = maxFitness;
					secondFitnessIndex = maxFitnessIndex;
				}
				maxFitness = fitnesses[populationCounter];
				maxFitnessIndex = populationCounter;
			}
			else if (fitnesses[populationCounter] > secondFitness)
			{
				secondFitness = fitnesses[populationCounter];
				secondFitnessIndex = populationCounter;
			}
		}

		cout << "Generation:\t\t" << generationCounter + 1 << "\n";
		cout << "Parent 1 Win Rate:\t" << (long double)maxFitness / (gamesPerCompetition * (populationSize - 1)) << "\n"
			<< "Parent 2 Win Rate:\t" << (long double)secondFitness / (gamesPerCompetition * (populationSize - 1)) << "\n"
			<< endl;

		for (size_t geneCounter = 0; geneCounter < agents[maxFitnessIndex].Weights().size(); geneCounter++)
		{
			cout << agents[maxFitnessIndex].Weights()[geneCounter] << ' ';
		}
		cout << "\n" << endl;
	}

	return agents[maxFitnessIndex];
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
		<< "2) Dorothy\n"
		<< "3) Beatrice\n"
		<< endl;
	getline(cin, input);
	while (input.length() != 1 ||
		!isdigit(input[0]) ||
		stoi(input) < 1 || 3 < stoi(input))
	{
		cout << "\nThat was not a valid option.\n"
			<< "To select an AI, enter the number left of the AI\'s name.\n"
			<< "1) Caprice\n"
			<< "2) Dorothy\n"
			<< "3) Beatrice\n"
			<< endl;
		getline(cin, input);
	}
	switch (stoi(input))
	{
	case 1:
		agent = new Random;
		break;
	case 2:
		agent = new MinimaxDefensive;
	case 3:
		agent = new MinimaxAll;
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

pair<size_t, size_t> ConnectFour::Compete(Agent& agent1, Agent& agent2, size_t games)
{
	random_device seeder;
	minstd_rand rng(seeder());
	size_t agent1Wins = 0, agent2Wins = 0, ties = 0;
	for (size_t gameCounter = 0; gameCounter < games; gameCounter++)
	{
		bool agent1First = rng() % 2;
		Board b;
		for (unsigned short i = 0; b.Winner() == ' ' && !b.IsFull(); i++)
		{
			if ((bool)(i % 2) != agent1First)
			{
				b.Place(agent1First ? 'x' : 'o', agent1.TakeTurn(b));
			}
			else
			{
				b.Place(agent1First ? 'o' : 'x', agent2.TakeTurn(b));
			}
		}
		if (b.Winner() == 'x')
		{
			agent1Wins += agent1First ? 1 : 0;
			agent2Wins += agent1First ? 0 : 1;
		}
		else if (b.Winner() == 'o')
		{
			agent1Wins += agent1First ? 0 : 1;
			agent2Wins += agent1First ? 1 : 0;
		}
		else
		{
			ties++;
		}
	}
	return make_pair(agent1Wins, agent2Wins);
}

vector<EvaluationFunction::utility> ConnectFour::Breed(const vector<EvaluationFunction::utility>& parent1, const vector<EvaluationFunction::utility>& parent2, long double mixingRatio)
{
	if (mixingRatio < 0 || 1 < mixingRatio)
	{
		throw exception("Not a valid mixing ratio.");
	}

	random_device seeder;
	minstd_rand rng(seeder());

	vector<EvaluationFunction::utility> result(parent1);

	for (size_t geneIndex = 0; geneIndex < result.size(); geneIndex++)
	{
		if ((long double)rng() / rng.max() > mixingRatio)
		{
			result[geneIndex] = parent2[geneIndex];
		}
	}

	return result;
}

vector<EvaluationFunction::utility> ConnectFour::Mutate(const vector<EvaluationFunction::utility>& chromosome, long double mutationRate)
{
	random_device seeder;
	minstd_rand rng(seeder());

	vector<EvaluationFunction::utility> mutant(chromosome);
	for (vector<EvaluationFunction::utility>::iterator geneIterator = mutant.begin(); geneIterator < mutant.end(); geneIterator++)
	{
		*geneIterator *= (1 + (mutationRate * (2.0l * rng() / rng.max() - 1)));
	}

	return mutant;
}

long double ConnectFour::Test(Agent& agent1, size_t games)
{
	Random agent2;
	random_device seeder;
	minstd_rand rng(seeder());
	size_t agent1Wins = 0, agent2Wins = 0, ties = 0;
	for (size_t gameCounter = 0; gameCounter < games; gameCounter++)
	{
		bool agent1First = rng() % 2;
		Board b;
		for (unsigned short i = 0; b.Winner() == ' ' && !b.IsFull(); i++)
		{
			if ((bool)(i % 2) != agent1First)
			{
				b.Place(agent1First ? 'x' : 'o', agent1.TakeTurn(b));
			}
			else
			{
				b.Place(agent1First ? 'o' : 'x', agent2.TakeTurn(b));
			}
		}
		if (b.Winner() == 'x')
		{
			agent1Wins += agent1First ? 1 : 0;
			agent2Wins += agent1First ? 0 : 1;
		}
		else if (b.Winner() == 'o')
		{
			agent1Wins += agent1First ? 0 : 1;
			agent2Wins += agent1First ? 1 : 0;
		}
		else
		{
			ties++;
		}
	}
	return (long double)agent1Wins / games;
}
