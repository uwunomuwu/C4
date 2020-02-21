#pragma once

#include "asrlc4.h"

class RpO : public ASRLC4
{
public:
	virtual Board::z TakeTurn(const Board&) noexcept override;
	virtual void Learn(const vector<pair<Board, Board::z>>&, ASRLC4::Result) override;

private:
	virtual void NewAction(const Board&) noexcept override;
	void Repress(const Board&, Board::z);

};
