#include "tsp.hpp"

#include <algorithm>
#include <stdexcept>
#include <limits>

TSP::TSP(math::Matrix<uint32_t> distances) : distances_{ distances }, positions_{ static_cast<uint32_t>(distances_.Rows()) } {
	if (distances_.Rows() != distances_.Columns()) {
		throw std::runtime_error("The distances matrix has incorrect size");
	}
}

TSP::PositionList TSP::Solve(int32_t start_position) const {
	uint32_t best_distance{ std::numeric_limits<uint32_t>::max() };	// Needed for the first run
	PositionList result;

	PositionList position_list = GeneratePositionList(positions_);
	do {
		if (position_list.at(0) != start_position || start_position != -1) {
			continue;
		}

		const auto distance = CalculateDistance(position_list);
		if (distance >= best_distance) {
			continue;
		}
		std::cout << best_distance << std::endl;
		// Save the best result so far
		best_distance = distance;
		result = position_list;
	} while (std::next_permutation(position_list.begin(), position_list.end()));

	return result;
}

TSP::PositionList TSP::GeneratePositionList(uint32_t size) {
	PositionList result;
	for (uint32_t index{}; index < size; ++index) {
		result.push_back(index);
	}
	return result;
}

uint32_t TSP::CalculateDistance(const PositionList& value) const {
	uint32_t result{};
	for (uint32_t index{}; index < value.size() - 1; ++index) {
		const auto& distance = distances_(value.at(index), value.at(index + 1));
		result += distance;
	}
	return result;
}