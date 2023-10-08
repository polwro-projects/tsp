#pragma once

#include <list>
#include <deque>

#include "math/matrix.hpp"

class TSP {
public:
	using PositionList = std::deque<uint32_t>;

public:
	TSP(math::Matrix<uint32_t> distances);

public:
	PositionList Solve(int32_t start_position) const;

private:
	static PositionList GeneratePositionList(uint32_t size);
	uint32_t CalculateDistance(const PositionList& value) const;

private:
	math::Matrix<uint32_t> distances_;
	uint32_t positions_;
};