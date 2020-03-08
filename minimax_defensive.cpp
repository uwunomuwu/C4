#include "minimax_defensive.h"

MinimaxDefensive::MinimaxDefensive() :
	Minimax(
		1,
		0, 0, 0, 0,
		0, 0, 0, 0,
		10, 20, 30, 30,
		10, 20, 500, 100,
		0, 10000, 1000)
{
}
