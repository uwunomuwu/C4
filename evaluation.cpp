#include "evaluation.h"
#include <cmath>

EvaluationFunction::EvaluationFunction(const EvaluationFunction& other)
{
	weights = other.weights;
}

EvaluationFunction::EvaluationFunction(EvaluationFunction&& other) noexcept
{
	weights = move(other.weights);
}

EvaluationFunction& EvaluationFunction::operator=(const EvaluationFunction& other)
{
	weights = other.weights;
	return *this;
}

EvaluationFunction& EvaluationFunction::operator=(EvaluationFunction&& other) noexcept
{
	weights = move(other.weights);
	return *this;
}

EvaluationFunction::EvaluationFunction(
	utility totalDoublesWeight,
	utility totalTriplesWeight,
	utility totalPenultimateTriplesWeight,
	utility totalAntepenultimateTriplesWeight,
	utility marginalDoublesWeight,
	utility marginalTriplesWeight,
	utility marginalPenultimateTriplesWeight,
	utility marginalAntepenultimateTriplesWeight,
	utility totalDoublesOpponentWeight,
	utility totalTriplesOpponentWeight,
	utility totalPenultimateTriplesOpponentWeight,
	utility totalAntepenultimateTriplesOpponentWeight,
	utility marginalDoublesOpponentWeight,
	utility marginalTriplesOpponentWeight,
	utility marginalPenultimateTriplesOpponentWeight,
	utility marginalAntepenultimateTriplesOpponentWeight,
	utility winWeight,
	utility winOpponentWeight,
	utility tieWeight)
{
	weights[totalDoubles] = totalDoublesWeight;
	weights[totalTriples] = totalTriplesWeight;
	weights[totalPenultimateTriples] = totalPenultimateTriplesWeight;
	weights[totalAntepenultimateTriples] = totalAntepenultimateTriplesWeight;
	weights[marginalDoubles] = marginalDoublesWeight;
	weights[marginalTriples] = marginalTriplesWeight;
	weights[marginalPenultimateTriples] = marginalPenultimateTriplesWeight;
	weights[marginalAntepenultimateTriples] = marginalAntepenultimateTriplesWeight;
	weights[totalDoublesOpponent] = totalDoublesOpponentWeight;
	weights[totalTriplesOpponent] = totalTriplesOpponentWeight;
	weights[totalPenultimateTriplesOpponent] = totalPenultimateTriplesOpponentWeight;
	weights[totalAntepenultimateTriplesOpponent] = totalAntepenultimateTriplesOpponentWeight;
	weights[marginalDoublesOpponent] = marginalDoublesOpponentWeight;
	weights[marginalTriplesOpponent] = marginalTriplesOpponentWeight;
	weights[marginalPenultimateTriplesOpponent] = marginalPenultimateTriplesOpponentWeight;
	weights[marginalAntepenultimateTriplesOpponent] = marginalAntepenultimateTriplesOpponentWeight;
	weights[win] = winWeight;
	weights[winOpponent] = winOpponentWeight;
	weights[tie] = tieWeight;
}

EvaluationFunction::EvaluationFunction(const vector<utility>& utilities)
{
	if (utilities.size() != 19)
	{
		throw exception("Invalid number of weights.");
	}

	weights[totalDoubles] = utilities[0];
	weights[totalTriples] = utilities[1];
	weights[totalPenultimateTriples] = utilities[2];
	weights[totalAntepenultimateTriples] = utilities[3];
	weights[marginalDoubles] = utilities[4];
	weights[marginalTriples] = utilities[5];
	weights[marginalPenultimateTriples] = utilities[6];
	weights[marginalAntepenultimateTriples] = utilities[7];
	weights[totalDoublesOpponent] = utilities[8];
	weights[totalTriplesOpponent] = utilities[9];
	weights[totalPenultimateTriplesOpponent] = utilities[10];
	weights[totalAntepenultimateTriplesOpponent] = utilities[11];
	weights[marginalDoublesOpponent] = utilities[12];
	weights[marginalTriplesOpponent] = utilities[13];
	weights[marginalPenultimateTriplesOpponent] = utilities[14];
	weights[marginalAntepenultimateTriplesOpponent] = utilities[15];
	weights[win] = utilities[16];
	weights[winOpponent] = utilities[17];
	weights[tie] = utilities[18];
}

EvaluationFunction::utility EvaluationFunction::operator()(char player, const Board& current, Board::z action) const
{
	char opponent;
	if (player == 'x')
	{
		opponent = 'o';
	}
	else
	{
		opponent = 'x';
	}

	Board evaluating = current;
	evaluating.Place(player, action);

	utility value = 0.0l;
	value += (weights.at(totalDoubles) * TotalDoubles(evaluating, player));
	value += (weights.at(totalTriples) * TotalTriples(evaluating, player));
	value += (weights.at(totalPenultimateTriples) * TotalPenultimateTriples(evaluating, player));
	value += (weights.at(totalAntepenultimateTriples) * TotalAntepenultimateTriples(evaluating, player));
	value += (weights.at(marginalDoubles) * (TotalDoubles(evaluating, player) - TotalDoubles(current, player)));
	value += (weights.at(marginalTriples) * (TotalTriples(evaluating, player) - TotalTriples(current, player)));
	value += (weights.at(marginalPenultimateTriples) * (TotalPenultimateTriples(evaluating, player) - TotalPenultimateTriples(current, player)));
	value += (weights.at(marginalAntepenultimateTriples) * (TotalAntepenultimateTriples(evaluating, player) - TotalAntepenultimateTriples(current, player)));
	value -= (weights.at(totalDoublesOpponent) * TotalDoubles(evaluating, opponent));
	value -= (weights.at(totalTriplesOpponent) * TotalTriples(evaluating, opponent));
	value -= (weights.at(totalPenultimateTriplesOpponent) * TotalPenultimateTriples(evaluating, opponent));
	value -= (weights.at(totalAntepenultimateTriplesOpponent) * TotalAntepenultimateTriples(evaluating, opponent));
	value -= (weights.at(marginalDoublesOpponent) * (TotalDoubles(evaluating, opponent) - TotalDoubles(current, opponent)));
	value -= (weights.at(marginalTriplesOpponent) * (TotalTriples(evaluating, opponent) - TotalTriples(current, opponent)));
	value -= (weights.at(marginalPenultimateTriplesOpponent) * (TotalPenultimateTriples(evaluating, opponent) - TotalPenultimateTriples(current, opponent)));
	value -= (weights.at(marginalAntepenultimateTriplesOpponent) * (TotalAntepenultimateTriples(evaluating, opponent) - TotalAntepenultimateTriples(current, opponent)));
	value += (weights.at(win) * (evaluating.Winner() == player) ? 1.0l : 0.0l);
	value -= (weights.at(winOpponent) * (evaluating.Winner() == opponent) ? 1.0l : 0.0l);
	value += (log(weights.at(tie)) * (evaluating.IsFull() && evaluating.Winner() == ' ') ? 1.0l : 0.0l);

	return value;
}

EvaluationFunction::utility EvaluationFunction::operator()(char player, const Board& current) const
{
	char opponent;
	if (player == 'x')
	{
		opponent = 'o';
	}
	else
	{
		opponent = 'x';
	}

	utility value = 0.0l;
	value += (weights.at(win) * (current.Winner() == player) ? 1.0l : 0.0l);
	value += (weights.at(winOpponent) * (current.Winner() == opponent) ? 1.0l : 0.0l);
	value += (weights.at(tie) * (current.IsFull() && current.Winner() == ' ') ? 1.0l : 0.0l);

	return value;
}

vector<EvaluationFunction::utility> EvaluationFunction::Weights() const
{
	vector<utility> returnValue;
	for (map<statistics, utility>::const_iterator weightsIterator = weights.cbegin(); weightsIterator != weights.cend(); weightsIterator++)
	{
		returnValue.push_back(weightsIterator->second);
	}
	return returnValue;
}

EvaluationFunction::utility EvaluationFunction::TotalDoubles(const Board& b, char c)
{
	return b.SpaceDoubles(c);
}

EvaluationFunction::utility EvaluationFunction::TotalTriples(const Board& b, char c)
{
	return b.SpaceTriples(c);
}

EvaluationFunction::utility EvaluationFunction::TotalPenultimateTriples(const Board& b, char c)
{
	return b.PenultimateTriples(c);
}

EvaluationFunction::utility EvaluationFunction::TotalAntepenultimateTriples(const Board& b, char c)
{
	return b.AntepenultimateTriples(c);
}
