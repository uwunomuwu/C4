#pragma once

#include "board.h"

class Agent
{
public:
	virtual ~Agent() = default;
	virtual Board::z TakeTurn(const Board&) noexcept = 0;
};
