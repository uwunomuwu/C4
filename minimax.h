#pragma once

#include "agent.h"
#include "evaluation.h"

class Minimax : public Agent
{
public:
	Minimax(size_t, EvaluationFunction);
	Minimax(size_t, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility, EvaluationFunction::utility);
	virtual Board::z TakeTurn(const Board&) noexcept override;

private:
	size_t searchDepth;
	EvaluationFunction value;

	EvaluationFunction::utility minimax(const Board&, Board::z, size_t);

};
