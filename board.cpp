#include "board.h"

using namespace std;

ostream& operator<<(ostream& stream, const Board& b)
{
	for (Board::z i = 0; i < 42; i++)
	{
		cout << '|' << b.b[i];
		if ((i + 1) % 7 == 0)
		{
			cout << "|\n";
		}
	}
	return stream;
}
void Board::Place(char c, z column)
{
	if (column < 1 || 7 < column)
	{
		throw bad_column();
	}
	else
	{
		bool placed = false;
		for (z i = 0; i < 6; i++)
		{
			if (b[35 - 7 * i + column - 1] == ' ')
			{
				b[35 - 7 * i + column - 1] = c;
				placed = true;
				break;
			}
		}
		if (!placed)
		{
			throw full_column();
		}
	}
}
char Board::Winner() const noexcept
{
	for (z i = 0; i < 7; i++)
	{
		for (z j = 0; j < 6; j++)
		{
			if (j < 3)
			{
				if (b[i + 7 * j] != ' ' && b[i + 7 * j] == b[i + 7 * j + 7] && b[i + 7 * j] == b[i + 7 * j + 14] && b[i + 7 * j] == b[i + 7 * j + 21])
				{
					return b[i + 7 * j];
				}
			}
			if (i < 4)
			{
				if (b[i + 7 * j] != ' ' && b[i + 7 * j] == b[i + 7 * j + 1] && b[i + 7 * j] == b[i + 7 * j + 2] && b[i + 7 * j] == b[i + 7 * j + 3])
				{
					return b[i + 7 * j];
				}
				if (j < 3)
				{
					if (b[i + 7 * j] != ' ' && b[i + 7 * j] == b[i + 7 * j + 8] && b[i + 7 * j] == b[i + 7 * j + 16] && b[i + 7 * j] == b[i + 7 * j + 24])
					{
						return b[i + 7 * j];
					}
				}
				else
				{
					if (b[i + 7 * j] != ' ' && b[i + 7 * j] == b[i + 7 * j - 6] && b[i + 7 * j] == b[i + 7 * j - 12] && b[i + 7 * j] == b[i + 7 * j - 18])
					{
						return b[i + 7 * j];
					}
				}
			}
		}
	}
	return ' ';
}
bool Board::IsFull() const noexcept
{
	for (z i = 0; i < 42; i++)
	{
		if (b[i] == ' ')
		{
			return false;
		}
	}
	return true;
}
bool Board::IsFullColumn(z column) const
{
	if (column < 1 || 7 < column)
	{
		throw bad_column();
	}
	else
	{
		return b[0 + column - 1] != ' ' &&
			b[7 + column - 1] != ' ' &&
			b[14 + column - 1] != ' ' &&
			b[21 + column - 1] != ' ' &&
			b[28 + column - 1] != ' ' &&
			b[35 + column - 1] != ' ';
	}
}
