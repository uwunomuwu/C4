#pragma once

#include "asrlc4.h"
#include "evaluation.h"
#include "minimax.h"

class ConnectFour
{
public:
	static void Play();
	static void TrainDouble(ASRLC4&, ASRLC4&, size_t);
	static void TrainSingle(ASRLC4&, Agent&, size_t);
	static void TestDouble(Agent&, Agent&, size_t);
	static void PlayDouble(Agent&, Agent&);
	static Minimax Evolve(size_t, size_t, size_t, long double, long double, long double);
	static Minimax EvolveAgent(const Minimax&, size_t, size_t, size_t, long double, long double);

private:
	static void HumanVsHuman();
	static void HumanVsAI();
	static void AIVsAI();

	static pair<size_t, size_t> Compete(Agent&, Agent&, size_t);
	static vector<EvaluationFunction::utility> Breed(const vector<EvaluationFunction::utility>&, const vector<EvaluationFunction::utility>&, long double);
	static vector<EvaluationFunction::utility> Mutate(const vector<EvaluationFunction::utility>&, long double);
	static long double Test(Agent&, size_t);

};
