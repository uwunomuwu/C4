#pragma once

#include <iostream>

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

	constexpr Board() = default;
	~Board() = default;
	friend ostream& operator<<(ostream&, const Board&);
	void Place(char, z);
	char Winner() const noexcept;
	bool IsFull() const noexcept;

private:
	char b[42] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				  ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				  ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				  ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				  ' ', ' ', ' ', ' ', ' ', ' ', ' ',
				  ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

	bool IsFullColumn(z) const;

};
