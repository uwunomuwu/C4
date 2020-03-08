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

bool Board::operator==(const Board& other) const
{
	for (z index = 0; index < 42; index++)
	{
		if (b[index] != other.b[index])
		{
			return false;
		}
	}
	return true;
}

char Board::At(z index) const
{
	return b[index];
}

Board::z Board::Doubles(char c) const
{
	z count = 0;
	for (z index = 0; index < 42; index++)
	{
		if (b[41 - index] == c)
		{
			if ((41 - index) % 7 > 0 &&
				b[41 - index - 1] == c)
			{
				if ((41 - index) % 7 > 2 &&
					b[41 - index - 2] == ' ' &&
					b[41 - index - 3] == ' ')
				{
					count++;
				}
				else if ((41 - index) % 7 > 1 &&
					(41 - index) % 7 < 6 &&
					b[41 - index + 1] == ' ' &&
					b[41 - index - 2] == ' ')
				{
					count++;
				}
				else if ((41 - index) % 7 < 5 &&
					b[41 - index + 1] == ' ' &&
					b[41 - index + 2] == ' ')
				{
					count++;
				}
			}
			if ((41 - index) > 20 &&
				b[41 - index - 7] == c)
			{
				if (b[41 - index - 14] == ' ' &&
					b[41 - index - 21] == ' ')
				{
					count++;
				}
			}
			if ((41 - index) > 7 &&
				(41 - index) % 7 > 0 &&
				b[41 - index - 8] == c)
			{
				if ((41 - index) > 23 &&
					(41 - index) % 7 > 2 &&
					b[41 - index - 16] == ' ' &&
					b[41 - index - 24] == ' ')
				{
					count++;
				}
				else if ((41 - index) > 16 &&
					(41 - index) < 34 &&
					(41 - index) % 7 > 1 &&
					(41 - index) % 7 < 6 &&
					b[41 - index - 16] == ' ' &&
					b[41 - index + 8] == ' ')
				{
					count++;
				}
				else if ((41 - index) < 26 &&
					(41 - index) % 7 < 5 &&
					b[41 - index + 8] == ' ' &&
					b[41 - index + 16] == ' ')
				{
					count++;
				}
			}
			if ((41 - index) > 8 &&
				(41 - index) < 39 &&
				(41 - index) % 7 < 6 &&
				b[41 - index - 6] == c)
			{
				if ((41 - index) > 20 &&
					(41 - index) % 7 < 4 &&
					b[41 - index - 12] == ' ' &&
					b[41 - index - 18] == ' ')
				{
					count++;
				}
				else if ((41 - index) > 14 &&
					(41 - index) < 33 &&
					(41 - index) % 7 > 0 &&
					(41 - index) % 7 < 5 &&
					b[41 - index - 12] == ' ' &&
					b[41 - index + 6] == ' ')
				{
					count++;
				}
				else if ((41 - index) < 27 &&
					(41 - index) % 7 > 1 &&
					b[41 - index + 6] == ' ' &&
					b[41 - index + 12] == ' ')
				{
					count++;
				}
			}
		}
	}
	return count;
}

Board::z Board::Triples(char c) const
{
	z count = 0;
	for (z index = 0; index < 42; index++)
	{
		if (b[41 - index] == c)
		{
			if ((41 - index) % 7 > 1 &&
				b[41 - index - 1] == c &&
				b[41 - index - 2] == c)
			{
				if ((41 - index) % 7 > 2 &&
					b[41 - index - 3] == ' ')
				{
					count++;
				}
				else if ((41 - index) % 7 < 6 &&
					b[41 - index + 1] == ' ')
				{
					count++;
				}
			}
			if ((41 - index) > 20 &&
				b[41 - index - 7] == c &&
				b[41 - index - 14] == c)
			{
				if (b[41 - index - 21] == ' ')
				{
					count++;
				}
			}
			if ((41 - index) > 15 &&
				(41 - index) % 7 > 1 &&
				b[41 - index - 8] == c &&
				b[41 - index - 16] == c)
			{
				if ((41 - index) > 23 &&
					(41 - index) % 7 > 2 &&
					b[41 - index - 24] == ' ')
				{
					count++;
				}
				else if ((41 - index) < 34 &&
					(41 - index) % 7 < 6 &&
					b[41 - index + 8] == ' ')
				{
					count++;
				}
			}
			if ((41 - index) > 14 &&
				(41 - index) < 39 &&
				(41 - index) % 7 < 5 &&
				b[41 - index - 6] == c &&
				b[41 - index - 12] == c)
			{
				if ((41 - index) > 20 &&
					(41 - index) % 7 < 4 &&
					b[41 - index - 18] == ' ')
				{
					count++;
				}
				else if ((41 - index) < 33 &&
					(41 - index) % 7 > 0 &&
					b[41 - index + 6] == ' ')
				{
					count++;
				}
			}
		}
	}
	return count;
}

Board::z Board::SpaceDoubles(char c) const
{
	z counter = 0;
	for (z column = 0; column < 7; column++)
	{
		for (z row = 0; row < 6; row++)
		{
			if (row < 3)
			{
				if (IsSpaceDouble(c, b[column + 7 * row], b[column + 7 * row + 7], b[column + 7 * row + 14], b[column + 7 * row + 21]))
				{
					counter++;
				}
			}
			if (column < 4)
			{
				if (IsSpaceDouble(c, b[column + 7 * row], b[column + 7 * row + 1], b[column + 7 * row + 2], b[column + 7 * row + 3]))
				{
					counter++;
				}
				if (row < 3)
				{
					if (IsSpaceDouble(c, b[column + 7 * row], b[column + 7 * row + 8], b[column + 7 * row + 16], b[column + 7 * row + 24]))
					{
						counter++;
					}
				}
				else
				{
					if (IsSpaceDouble(c, b[column + 7 * row], b[column + 7 * row - 6], b[column + 7 * row - 12], b[column + 7 * row - 18]))
					{
						counter++;
					}
				}
			}
		}
	}
	return counter;
}

Board::z Board::SpaceTriples(char c) const
{
	z counter = 0;
	for (z column = 0; column < 7; column++)
	{
		for (z row = 0; row < 6; row++)
		{
			if (row < 3)
			{
				if (IsSpaceTriple(c, b[column + 7 * row], b[column + 7 * row + 7], b[column + 7 * row + 14], b[column + 7 * row + 21]))
				{
					counter++;
				}
			}
			if (column < 4)
			{
				if (IsSpaceTriple(c, b[column + 7 * row], b[column + 7 * row + 1], b[column + 7 * row + 2], b[column + 7 * row + 3]))
				{
					counter++;
				}
				if (row < 3)
				{
					if (IsSpaceTriple(c, b[column + 7 * row], b[column + 7 * row + 8], b[column + 7 * row + 16], b[column + 7 * row + 24]))
					{
						counter++;
					}
				}
				else
				{
					if (IsSpaceTriple(c, b[column + 7 * row], b[column + 7 * row - 6], b[column + 7 * row - 12], b[column + 7 * row - 18]))
					{
						counter++;
					}
				}
			}
		}
	}
	return counter;
}

Board::z Board::PenultimateTriples(char c) const
{
	z counter = 0;
	for (z column = 0; column < 7; column++)
	{
		for (z row = 0; row < 6; row++)
		{
			if (row < 3)
			{
				if (IsPenultimateTriple(c, column + 7 * row, column + 7 * row + 7, column + 7 * row + 14, column + 7 * row + 21))
				{
					counter++;
				}
			}
			if (column < 4)
			{
				if (IsPenultimateTriple(c, column + 7 * row, column + 7 * row + 1, column + 7 * row + 2, column + 7 * row + 3))
				{
					counter++;
				}
				if (row < 3)
				{
					if (IsPenultimateTriple(c, column + 7 * row, column + 7 * row + 8, column + 7 * row + 16, column + 7 * row + 24))
					{
						counter++;
					}
				}
				else
				{
					if (IsPenultimateTriple(c, column + 7 * row, column + 7 * row - 6, column + 7 * row - 12, column + 7 * row - 18))
					{
						counter++;
					}
				}
			}
		}
	}
	return counter;
}

Board::z Board::AntepenultimateTriples(char c) const
{
	z counter = 0;
	for (z column = 0; column < 7; column++)
	{
		for (z row = 0; row < 6; row++)
		{
			if (row < 3)
			{
				if (IsAntepenultimateTriple(c, column + 7 * row, column + 7 * row + 7, column + 7 * row + 14, column + 7 * row + 21))
				{
					counter++;
				}
			}
			if (column < 4)
			{
				if (IsAntepenultimateTriple(c, column + 7 * row, column + 7 * row + 1, column + 7 * row + 2, column + 7 * row + 3))
				{
					counter++;
				}
				if (row < 3)
				{
					if (IsAntepenultimateTriple(c, column + 7 * row, column + 7 * row + 8, column + 7 * row + 16, column + 7 * row + 24))
					{
						counter++;
					}
				}
				else
				{
					if (IsAntepenultimateTriple(c, column + 7 * row, column + 7 * row - 6, column + 7 * row - 12, column + 7 * row - 18))
					{
						counter++;
					}
				}
			}
		}
	}
	return counter;
}

vector<pair<Board, Board::z>> Board::Successors() const
{
	vector<pair<Board, z>> successors;

	char nextPiece = PositionsLeft() % 2 ? 'o' : 'x';

	if (Winner() == ' ')
	{
		Board copy;
		for (Board::z column = 1; column < 8; column++)
		{
			if (!IsFullColumn(column))
			{
				copy = *this;
				successors.emplace_back(make_pair(copy.Place(nextPiece, column), column));
			}
		}
	}

	return successors;
}

bool Board::ValidIndex(z index) const
{
	return 0 <= index && index < 42;
}

bool Board::IsSpaceDouble(char check, char c1, char c2, char c3, char c4)
{
	z letters = 0;
	z spaces = 0;
	if (c1 == check)
	{
		letters++;
	}
	else if (c1 == ' ')
	{
		spaces++;
	}
	if (c2 == check)
	{
		letters++;
	}
	else if (c2 == ' ')
	{
		spaces++;
	}
	if (c3 == check)
	{
		letters++;
	}
	else if (c3 == ' ')
	{
		spaces++;
	}
	if (c4 == check)
	{
		letters++;
	}
	else if (c4 == ' ')
	{
		spaces++;
	}
	return (letters == 2 && spaces == 2);
}

bool Board::IsSpaceTriple(char check, char c1, char c2, char c3, char c4)
{
	z letters = 0;
	z spaces = 0;
	if (c1 == check)
	{
		letters++;
	}
	else if (c1 == ' ')
	{
		spaces++;
	}
	if (c2 == check)
	{
		letters++;
	}
	else if (c2 == ' ')
	{
		spaces++;
	}
	if (c3 == check)
	{
		letters++;
	}
	else if (c3 == ' ')
	{
		spaces++;
	}
	if (c4 == check)
	{
		letters++;
	}
	else if (c4 == ' ')
	{
		spaces++;
	}
	return (letters == 3 && spaces == 1);
}

bool Board::IsPenultimateTriple(char check, z index1, z index2, z index3, z index4) const
{
	z letters = 0;
	z spaces = 0;
	z spaceIndex = 42;
	if (b[index1] == check)
	{
		letters++;
	}
	else if (b[index1] == ' ')
	{
		spaces++;
		spaceIndex = index1;
	}
	if (b[index2] == check)
	{
		letters++;
	}
	else if (b[index2] == ' ')
	{
		spaces++;
		spaceIndex = index2;
	}
	if (b[index3] == check)
	{
		letters++;
	}
	else if (b[index3] == ' ')
	{
		spaces++;
		spaceIndex = index3;
	}
	if (b[index4] == check)
	{
		letters++;
	}
	else if (b[index4] == ' ')
	{
		spaces++;
		spaceIndex = index4;
	}
	if (letters == 3 && spaces == 1)
	{
		if (ValidIndex(spaceIndex + 7))
		{
			return b[spaceIndex + 7] != ' ';
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool Board::IsAntepenultimateTriple(char check, z index1, z index2, z index3, z index4) const
{
	z letters = 0;
	z spaces = 0;
	z spaceIndex = 42;
	if (b[index1] == check)
	{
		letters++;
	}
	else if (b[index1] == ' ')
	{
		spaces++;
		spaceIndex = index1;
	}
	if (b[index2] == check)
	{
		letters++;
	}
	else if (b[index2] == ' ')
	{
		spaces++;
		spaceIndex = index2;
	}
	if (b[index3] == check)
	{
		letters++;
	}
	else if (b[index3] == ' ')
	{
		spaces++;
		spaceIndex = index3;
	}
	if (b[index4] == check)
	{
		letters++;
	}
	else if (b[index4] == ' ')
	{
		spaces++;
		spaceIndex = index4;
	}
	if (letters == 3 && spaces == 1 && ValidIndex(spaceIndex + 7) && b[spaceIndex + 7] == ' ')
	{
		if (ValidIndex(spaceIndex + 14))
		{
			return b[spaceIndex + 14] != ' ';
		}
		else
		{
			return true;
		}
	}
	return false;
}
