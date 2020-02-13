#pragma once

class ConnectFour
{
public:
	constexpr ConnectFour() = default;
	~ConnectFour() = default;
	void Play();
	void Train();

private:
	void HumanVsHuman();
	void HumanVsAI();
	void AIVsAI();

};
