#include "tsp.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>

TSP::TSP(DistanceMatrix distances)
	: distances_{distances}
	, positions_{static_cast<uint32_t>(distances_.Rows())} {
	if(distances_.Rows() != distances_.Columns()) {
		throw std::runtime_error("The distances matrix has incorrect size");
	}
}

TSP::PositionList TSP::Solve() const {
	uint32_t best_distance{std::numeric_limits<uint32_t>::max()}; // Needed for the first run
	PositionList result;

	PositionList position_list = GeneratePositionList(positions_);
	do {
		const auto distance = CalculateDistance(position_list);
		if(distance >= best_distance) {
			continue;
		}

		// Save the best result so far
		best_distance = distance;
		result = position_list;
	} while(std::next_permutation(position_list.begin(), position_list.end()));

	return result;
}

TSP::PositionList TSP::GeneratePositionList(uint32_t size) {
	PositionList result;
	for(uint32_t index{}; index < size; ++index) {
		result.push_back(index);
	}
	return result;
}

uint32_t TSP::CalculateDistance(const PositionList& value) const {
	uint32_t result{};
	for(uint32_t index{}; index < value.size() - 1; ++index) {
		const auto& distance = distances_(value.at(index), value.at(index + 1));
		result += distance;
	}
	return result;
}