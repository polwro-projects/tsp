/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

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

	// Generate the list of positions and iterate over every permutation of it
	PositionList position_list = GeneratePositionList(positions_);
	do {
		// Get to the next permutation if it's length is bigger than the best one so far
		const auto distance = CalculateDistance(position_list);
		if(distance >= best_distance) {
			continue;
		}

		// Save the best result
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