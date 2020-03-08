#include "minimax_defensive.h"

MinimaxDefensive::MinimaxDefensive() :
	Minimax(
		1,
		1, 1, 1, 1,
		1, 1, 1, 1,
		100, 200, 300, 300,
		100, 200, 5000, 1000,
		1, 100000, 10000)
{
}
