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

#include "tsp/algorithm/bf.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>

namespace tsp::algorithm {
BF::BF(DistanceMatrix distances)
	: Algorithm{distances} {
	if(distances_.Rows() != distances_.Columns()) {
		throw std::runtime_error("The distances matrix has incorrect size");
	}
}

void BF::Solve() {
	const auto path_size = distances_.Rows();
	uint32_t best_distance{std::numeric_limits<uint32_t>::max()}; // Needed for the first run;

	// Generate the list of positions and iterate over every permutation of it
	auto position_list = GeneratePath(path_size);
	do {
		// Get to the next permutation if it's length is bigger than the best one so far
		const auto distance = CalculateCost(position_list);
		if(distance >= solution_.cost) {
			continue;
		}

		// Save the best result
		solution_ = {position_list, distance};
	} while(std::next_permutation(position_list.begin(), position_list.end()));

	solution_.cost += distances_(solution_.path.back(), solution_.path.front());
	solution_.path.push_back(solution_.path.front());
}

BF::Solution::Path BF::GeneratePath(uint32_t size) {
	Solution::Path result;
	for(uint32_t index{}; index < size; ++index) {
		result.push_back(index);
	}
	return result;
}

uint32_t BF::CalculateCost(const Solution::Path& value) const {
	uint32_t result{};
	for(uint32_t index{}; index < value.size() - 1; ++index) {
		const auto& distance = distances_(value.at(index), value.at(index + 1));
		result += distance;
	}
	return result;
}
} // namespace tsp::algorithm