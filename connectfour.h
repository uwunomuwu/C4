#pragma once

#include "asrlc4.h"

class ConnectFour
{
public:
	static void Play();
	static void TrainDouble(ASRLC4&, ASRLC4&, size_t);
	static void TrainSingle(ASRLC4&, Agent&, size_t);
	static void TestDouble(Agent&, Agent&, size_t);
	static void PlayDouble(Agent&, Agent&);

private:
	static void HumanVsHuman();
	static void HumanVsAI();
	static void AIVsAI();

};
