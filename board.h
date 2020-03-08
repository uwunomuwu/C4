#pragma once

#include <iostream>
#include <fstream>
#include <cstdarg>
#include <vector>

using namespace std;

class Board
{
public:
	using z = unsigned short;

	class bad_column : public exception
	{
	public:
		virtual const char* what() const noexcept override
		{
			return "The selected column does not exist.";
		}
	};
	class full_column : public exception
	{
	public:
		virtual const char* what() const noexcept override
		{
			return "The selected column is full.";
		}
	};

	Board();
	Board(const Board&);
	Board(Board&&) noexcept;
	Board& operator=(const Board&);
	Board& operator=(Board&&) noexcept;
	~Board();
	friend fstream& operator<<(fstream&, const Board&);
	friend fstream& operator>>(fstream&, Board&);
	friend ofstream& operator<<(ofstream&, const Board&);
	friend ifstream& operator>>(ifstream&, Board&);
	friend ostream& operator<<(ostream&, const Board&);
	Board& Place(char, z);
	char Winner() const noexcept;
	char MarkWinner() noexcept;
	bool IsFullColumn(z) const;
	bool IsFull() const noexcept;
	z PositionsLeft() const noexcept;
	bool operator==(const Board&) const;
	char At(z) const;
	z Doubles(char) const;
	z Triples(char) const;
	z SpaceDoubles(char) const;
	z SpaceTriples(char) const;
	z PenultimateTriples(char) const;
	z AntepenultimateTriples(char) const;
	vector<pair<Board, z>> Successors() const;

private:
	char* b = new char[42];
	bool ValidIndex(z) const;
	static bool IsSpaceDouble(char, char, char, char, char);
	static bool IsSpaceTriple(char, char, char, char, char);
	bool IsPenultimateTriple(char, z, z, z, z) const;
	bool IsAntepenultimateTriple(char, z, z, z, z) const;

};

template<>
struct hash<Board>
{
	size_t operator()(const Board& b) const
	{
		size_t result = 0;
		size_t letter = 0;
		for (Board::z index = 0; index < 42; index++)
		{
			switch (b.At(index))
			{
			case ' ':
				letter = 0;
				break;
			case 'x':
				letter = 1;
				break;
			case 'o':
				letter = 2;
				break;
			}
			result += (letter << (2 * index));
		}
		return result;
	}
};
