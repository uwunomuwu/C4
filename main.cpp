#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "board.h"
#include "connectfour.h"
#include "rpo.h"
#include "random.h"

using namespace std;

void GenerateStateSpace();
vector<Board> GetSuccessors(Board);

int main()
{
	Board b;
	Random caprice;

	for (int i = 0; i < 10; i++)
	{
		b.Place('x', caprice.TakeTurn(b));
		//b.Place('o', caprice.TakeTurn(b));
	}
	
	cout << b << endl;
	cout << "x: " << b.Triples('x') << endl;
	cout << "o: " << b.Triples('o') << endl;

	// Don't try this unless have supercomputer.
	// GenerateStateSpace();

	system("pause");
	return EXIT_SUCCESS;
}

void GenerateStateSpace()
{
	ofstream outputFile("statespace.c4", ios::out);
	size_t statesSearched = 0;
	using namespace chrono;
	system_clock::time_point start = system_clock::now();
	
	vector<pair<Board, Board::z>> fringe;
	Board empty;
	Board board;
	Board::z depth;
	fringe.push_back(make_pair(empty, 0));
	while (!fringe.empty())
	{
		board = fringe.back().first;
		depth = fringe.back().second;

		if (!(statesSearched % 100000))
		{
			cout << "States Searched:\t\t" << statesSearched << endl
				<< "Fringe Size:\t\t\t" << fringe.size() << endl
				<< "Current Depth:\t\t\t" << depth << endl
				<< "Depth 1 States in Fringe:\t" << count_if(fringe.cbegin(), fringe.cend(), [](pair<Board, Board::z> item) {return item.second == 1; }) << endl
				<< "Time Elapsed (s):\t\t" << duration_cast<duration<double>>(system_clock::now() - start).count() << endl
				<< endl;
		}

		fringe.pop_back();

		for (unsigned short count = 0; count < depth; count++)
		{
			outputFile << '#';
		}
		outputFile << board << endl;
		statesSearched++;

		for (Board b : GetSuccessors(board))
		{
			fringe.push_back(make_pair(b, depth + 1));
		}
	}
	
	outputFile.close();
}
vector<Board> GetSuccessors(Board b)
{
	vector<Board> successors;

	char nextPiece = b.PositionsLeft() % 2 ? 'o' : 'x';

	if (b.Winner() == ' ')
	{
		Board copy(b);
		for (Board::z column = 1; column < 8; column++)
		{
			if (!b.IsFullColumn(column))
			{
				copy = b;
				successors.emplace_back(copy.Place(nextPiece, column));
			}
		}
	}

	return successors;
}
