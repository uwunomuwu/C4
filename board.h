#pragma once

#include <iostream>
#include <fstream>

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

private:
	char* b = new char[42];

};
