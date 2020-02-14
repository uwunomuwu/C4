#include "random.h"
#include <vector>

using namespace std;

Random::Random()
{
	random_device seeder;
	rng.seed(seeder());
}

Board::z Random::TakeTurn(const Board& b) noexcept
{
	vector<unsigned short> availableColumns;
	for (unsigned short column = 1; column < 8; column++)
	{
		if (!b.IsFullColumn(column))
		{
			availableColumns.push_back(column);
		}
	}
	return availableColumns[rng() % availableColumns.size()];
}
