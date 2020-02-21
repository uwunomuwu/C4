#pragma once

#include "agent.h"
#include <vector>
#include <unordered_map>
#include <random>

using namespace std;

class ASRLC4 : public Agent
{
public:
	virtual Board::z TakeTurn(const Board&) noexcept = 0;

	enum class Result { win, loss, tie };
	virtual void Learn(const vector<pair<Board, Board::z>>&, Result) = 0;

protected:
	class PDist
	{
	public:
		PDist()
		{
			random_device seeder;
			rng.seed(seeder());
		}
		size_t& operator[](size_t index)
		{
			return relativeProbabilities[index];
		}
		size_t Sum() const
		{
			return relativeProbabilities[0] +
				relativeProbabilities[1] +
				relativeProbabilities[2] +
				relativeProbabilities[3] +
				relativeProbabilities[4] +
				relativeProbabilities[5] +
				relativeProbabilities[6];
		}
		Board::z Select()
		{
			size_t value = rng() % (Sum());
			for (Board::z index = 0; index < 7; index++)
			{
				if (value < relativeProbabilities[index])
				{
					return index;
				}
				else
				{
					value -= relativeProbabilities[index];
				}
			}

			// execution should NEVER reach here
			throw runtime_error("Stack corruption during execution of this function.");
		}

	private:
		size_t relativeProbabilities[7] = { 0, 0, 0, 0, 0, 0, 0 };
		minstd_rand rng;

	};

	unordered_map<Board, PDist> actions;
	virtual void NewAction(const Board&) noexcept = 0;

};
