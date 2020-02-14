#include "board.h"

using namespace std;

ostream& operator<<(ostream& stream, const Board& b)
{
	stream << "  1 2 3 4 5 6 7 \n";
	for (Board::z index = 0; index < 42; index++)
	{
		if (index % 7 == 0)
		{
			stream << (char)('a' + index / 7);
		}
		stream << '|' << b.b[index];
		if ((index + 1) % 7 == 0)
		{
			stream << "|\n";
		}
	}
	return stream;
}
fstream& operator<<(fstream& filestream, const Board& b)
{
	for (Board::z index = 0; index < 42; index++)
	{
		filestream << b.b[index];
	}
	return filestream;
}
fstream& operator>>(fstream& filestream, Board& b)
{
	for (Board::z index = 0; index < 42; index++)
	{
		filestream.get(b.b[index]);
	}
	return filestream;
}
ofstream& operator<<(ofstream& filestream, const Board& b)
{
	for (Board::z index = 0; index < 42; index++)
	{
		filestream << b.b[index];
	}
	return filestream;
}
ifstream& operator>>(ifstream& filestream, Board& b)
{
	for (Board::z index = 0; index < 42; index++)
	{
		filestream.get(b.b[index]);
	}
	return filestream;
}
Board::Board()
{
	for (z index = 0; index < 42; index++)
	{
		b[index] = ' ';
	}
}
Board::Board(const Board& other)
{
	for (z index = 0; index < 42; index++)
	{
		b[index] = other.b[index];
	}
}
Board::Board(Board&& other) noexcept
{
	b = other.b;
	other.b = nullptr;
}
Board& Board::operator=(const Board& other)
{
	for (z index = 0; index < 42; index++)
	{
		b[index] = other.b[index];
	}
	return *this;
}
Board& Board::operator=(Board&& other) noexcept
{
	b = other.b;
	other.b = nullptr;
	return *this;
}
Board::~Board()
{
	delete[] b;
}
Board& Board::Place(char c, z column)
{
	if (column < 1 || 7 < column)
	{
		throw bad_column();
	}
	else
	{
		bool placed = false;
		for (z row = 0; row < 6; row++)
		{
			if (b[35 - 7 * row + column - 1] == ' ')
			{
				b[35 - 7 * row + column - 1] = c;
				placed = true;
				break;
			}
		}
		if (!placed)
		{
			throw full_column();
		}
	}
	return *this;
}
char Board::Winner() const noexcept
{
	for (z column = 0; column < 7; column++)
	{
		for (z row = 0; row < 6; row++)
		{
			if (row < 3)
			{
				if (b[column + 7 * row] != ' ' && b[column + 7 * row] == b[column + 7 * row + 7] && b[column + 7 * row] == b[column + 7 * row + 14] && b[column + 7 * row] == b[column + 7 * row + 21])
				{
					return b[column + 7 * row];
				}
			}
			if (column < 4)
			{
				if (b[column + 7 * row] != ' ' && b[column + 7 * row] == b[column + 7 * row + 1] && b[column + 7 * row] == b[column + 7 * row + 2] && b[column + 7 * row] == b[column + 7 * row + 3])
				{
					return b[column + 7 * row];
				}
				if (row < 3)
				{
					if (b[column + 7 * row] != ' ' && b[column + 7 * row] == b[column + 7 * row + 8] && b[column + 7 * row] == b[column + 7 * row + 16] && b[column + 7 * row] == b[column + 7 * row + 24])
					{
						return b[column + 7 * row];
					}
				}
				else
				{
					if (b[column + 7 * row] != ' ' && b[column + 7 * row] == b[column + 7 * row - 6] && b[column + 7 * row] == b[column + 7 * row - 12] && b[column + 7 * row] == b[column + 7 * row - 18])
					{
						return b[column + 7 * row];
					}
				}
			}
		}
	}
	return ' ';
}
char Board::MarkWinner() noexcept
{
	char c = ' ';
	for (z column = 0; column < 7; column++)
	{
		for (z row = 0; row < 6; row++)
		{
			if (row < 3)
			{
				if (b[column + 7 * row] != ' ' && b[column + 7 * row] == b[column + 7 * row + 7] && b[column + 7 * row] == b[column + 7 * row + 14] && b[column + 7 * row] == b[column + 7 * row + 21])
				{
					c = b[column + 7 * row];
					b[column + 7 * row] = b[column + 7 * row + 7] = b[column + 7 * row + 14] = b[column + 7 * row + 21] = toupper(c);
					return c;
				}
			}
			if (column < 4)
			{
				if (b[column + 7 * row] != ' ' && b[column + 7 * row] == b[column + 7 * row + 1] && b[column + 7 * row] == b[column + 7 * row + 2] && b[column + 7 * row] == b[column + 7 * row + 3])
				{
					c = b[column + 7 * row];
					b[column + 7 * row] = b[column + 7 * row + 1] = b[column + 7 * row + 2] = b[column + 7 * row + 3] = toupper(c);
					return c;
				}
				if (row < 3)
				{
					if (b[column + 7 * row] != ' ' && b[column + 7 * row] == b[column + 7 * row + 8] && b[column + 7 * row] == b[column + 7 * row + 16] && b[column + 7 * row] == b[column + 7 * row + 24])
					{
						c = b[column + 7 * row];
						b[column + 7 * row] = b[column + 7 * row + 8] = b[column + 7 * row + 16] = b[column + 7 * row + 24] = toupper(c);
						return c;
					}
				}
				else
				{
					if (b[column + 7 * row] != ' ' && b[column + 7 * row] == b[column + 7 * row - 6] && b[column + 7 * row] == b[column + 7 * row - 12] && b[column + 7 * row] == b[column + 7 * row - 18])
					{
						c = b[column + 7 * row];
						b[column + 7 * row] = b[column + 7 * row - 6] = b[column + 7 * row - 12] = b[column + 7 * row - 18] = toupper(c);
						return c;
					}
				}
			}
		}
	}
	return c;
}
bool Board::IsFull() const noexcept
{
	for (z index = 0; index < 42; index++)
	{
		if (b[index] == ' ')
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
Board::z Board::PositionsLeft() const noexcept
{
	z count = 0;
	for (z index = 0; index < 42; index++)
	{
		if (b[index] == ' ')
		{
			count++;
		}
	}
	return count;
}
