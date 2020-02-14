#pragma once

#include "agent.h"
#include <random>

using namespace std;

class Random : public Agent
{
public:
	Random();
	virtual Board::z TakeTurn(const Board&) noexcept override;
	
private:
	default_random_engine rng;

};
