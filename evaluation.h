#pragma once

#include "board.h"
#include <map>

class EvaluationFunction
{
public:
	using utility = long double;

	enum statistics
	{
		totalDoubles = 0,
		totalTriples,
		totalPenultimateTriples,
		totalAntepenultimateTriples,
		marginalDoubles,
		marginalTriples,
		marginalPenultimateTriples,
		marginalAntepenultimateTriples,
		totalDoublesOpponent,
		totalTriplesOpponent,
		totalPenultimateTriplesOpponent,
		totalAntepenultimateTriplesOpponent,
		marginalDoublesOpponent,
		marginalTriplesOpponent,
		marginalPenultimateTriplesOpponent,
		marginalAntepenultimateTriplesOpponent,
		win,
		winOpponent,
		tie
	};

	EvaluationFunction() = delete;
	EvaluationFunction(const EvaluationFunction&);
	EvaluationFunction(EvaluationFunction&&) noexcept;
	EvaluationFunction& operator=(const EvaluationFunction&);
	EvaluationFunction& operator=(EvaluationFunction&&) noexcept;
	~EvaluationFunction() = default;
	EvaluationFunction(utility, utility, utility, utility, utility, utility, utility, utility, utility, utility, utility, utility, utility, utility, utility, utility, utility, utility, utility);
	EvaluationFunction(const vector<utility>&);
	utility operator()(char, const Board&, Board::z) const;
	utility operator()(char, const Board&) const;
	vector<utility> Weights() const;

private:
	map<statistics, utility> weights;
	static utility TotalDoubles(const Board&, char);
	static utility TotalTriples(const Board&, char);
	static utility TotalPenultimateTriples(const Board&, char);
	static utility TotalAntepenultimateTriples(const Board&, char);

};