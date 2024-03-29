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

#include "tsp/algorithm/algorithm.hpp"

#include <algorithm>

namespace tsp::algorithm {
Algorithm::Algorithm(DistanceMatrix distances)
	: distances_{distances} {
	if(distances_.Rows() != distances_.Columns()) {
		throw std::runtime_error("The distances matrix has incorrect size");
	}
}

Algorithm::Solution Algorithm::GetSolution() const noexcept {
	return solution_;
}

void Algorithm::Stop() noexcept {
	is_stopped_ = true;
}

void Algorithm::Clear() {
	// Clear the previous solution
	solution_.Clear();
}

uint32_t Algorithm::CalculateCost(const Solution::Path& value) const {
	uint32_t result{};
	for(uint32_t index{}; index < value.size() - 1; ++index) {
		const auto& distance = distances_(value.at(index), value.at(index + 1));
		result += distance;
	}
	return result;
}

void Algorithm::Solution::Clear() {
	path.clear();

	cost = std::numeric_limits<uint32_t>::max();
}
} // namespace tsp::algorithm