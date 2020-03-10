#include "minimax_ace.h"

MinimaxAce::MinimaxAce() :
	Minimax(
		1,
		1, 1, 1, 100,
		1, 1, 1, 10000,
		1, 1, 1000000, 1,
		1, 1, 100000000, 1,
		99999999999999, 99999999999999, 1
	)
{
}
