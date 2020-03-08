#include "minimax.h"

Minimax::Minimax(size_t d, EvaluationFunction ef) : searchDepth(d), value(ef)
{
}

Minimax::Minimax(size_t d,
	EvaluationFunction::utility w0,
	EvaluationFunction::utility w1,
	EvaluationFunction::utility w2,
	EvaluationFunction::utility w3,
	EvaluationFunction::utility w4,
	EvaluationFunction::utility w5,
	EvaluationFunction::utility w6,
	EvaluationFunction::utility w7,
	EvaluationFunction::utility w8,
	EvaluationFunction::utility w9,
	EvaluationFunction::utility w10,
	EvaluationFunction::utility w11,
	EvaluationFunction::utility w12,
	EvaluationFunction::utility w13,
	EvaluationFunction::utility w14,
	EvaluationFunction::utility w15,
	EvaluationFunction::utility w16,
	EvaluationFunction::utility w17,
	EvaluationFunction::utility w18) :
	searchDepth(d),
	value(w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15, w16, w17, w18)
{
}

Board::z Minimax::TakeTurn(const Board& b) noexcept
{
	vector<pair<Board, Board::z>> possibleMoves = b.Successors();
	vector<pair<Board, Board::z>>::const_iterator moveIterator = possibleMoves.cbegin();
	EvaluationFunction::utility moveUtility = minimax(b, moveIterator->second, searchDepth);
	EvaluationFunction::utility maxUtility = moveUtility;
	Board::z bestMove = moveIterator->second;
	moveIterator++;
	for (; moveIterator < possibleMoves.cend(); moveIterator++)
	{
		moveUtility = minimax(b, moveIterator->second, searchDepth);
		if (moveUtility > maxUtility)
		{
			maxUtility = moveUtility;
			bestMove = moveIterator->second;
		}
	}
	return bestMove;
}

EvaluationFunction::utility Minimax::minimax(const Board& b, Board::z move, size_t depth)
{
	char player = (b.PositionsLeft() % 2) ? 'o' : 'x';
	if (depth <= 1)
	{
		return value(player, b, move);
	}
	else
	{
		Board current = b;
		current.Place(player, move);
		vector<pair<Board, Board::z>> possibleMoves = current.Successors();
		if (possibleMoves.size() == 0)
		{
			return value(player, current);
		}
		vector<pair<Board, Board::z>>::const_iterator moveIterator = possibleMoves.cbegin();
		EvaluationFunction::utility moveUtility = minimax(current, moveIterator->second, depth - 1);
		EvaluationFunction::utility extremeUtility = moveUtility;
		moveIterator++;
		for (; moveIterator < possibleMoves.cend(); moveIterator++)
		{
			moveUtility = minimax(current, moveIterator->second, depth - 1);
			if (depth % 2)
			{
				if (moveUtility > extremeUtility)
				{
					extremeUtility = moveUtility;
				}
			}
			else
			{
				if (moveUtility < extremeUtility)
				{
					extremeUtility = moveUtility;
				}
			}
			
		}
		return extremeUtility;
	}
}
