#pragma once

#include <deque>
#include <list>

#include "io/file/tsp/parser.hpp"
#include "math/matrix.hpp"

class TSP {
public:
	using DistanceMatrix = io::file::tsp::Parser::DistanceMatrix;
	using PositionList = std::deque<uint32_t>;

public:
	TSP(DistanceMatrix distances);

public:
	PositionList Solve() const;

private:
	static PositionList GeneratePositionList(uint32_t size);
	uint32_t CalculateDistance(const PositionList& value) const;

private:
	DistanceMatrix distances_;
	uint32_t positions_;
};