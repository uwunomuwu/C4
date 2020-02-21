#include "rpo.h"

Board::z RpO::TakeTurn(const Board& b) noexcept
{
	if (actions.count(b) == 0)
	{
		NewAction(b);
	}

	return actions[b].Select() + 1;
}

void RpO::Learn(const vector<pair<Board, Board::z>>& moveset, ASRLC4::Result result)
{
	if (result == ASRLC4::Result::loss)
	{
		for (vector<pair<Board, Board::z>>::const_iterator moveIterator = moveset.cbegin();
			moveIterator < moveset.cend();
			moveIterator++)
		{
			Repress(moveIterator->first, moveIterator->second);
		}
	}
}

void RpO::NewAction(const Board& b) noexcept
{
	PDist dist;
	for (Board::z column = 0; column < 7; column++)
	{
		if (!b.IsFullColumn(column + 1))
		{
			dist[column] = 1;
		}
	}
	actions[b] = dist;
}

void RpO::Repress(const Board& b, Board::z column)
{
	actions[b][column - 1]--;
	if (!actions[b].Sum())
	{
		actions.erase(b);
	}
}
