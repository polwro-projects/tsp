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

#include "tsp/neighborhood/random.hpp"

namespace tsp::neighborhood {

Random::Random(uint32_t size)
	: neighbor_distribution_{1, size - 2} {
	std::random_device device;
	neighbor_generator_ = std::mt19937{device()};
}

Random::Path Random::GetNeighbor(const Path& path) const noexcept {
	auto neighbor = path;
	const auto first_index = neighbor_distribution_(neighbor_generator_);
	const auto second_index = neighbor_distribution_(neighbor_generator_);
	std::iter_swap(neighbor.begin() + first_index, neighbor.begin() + second_index);

	return neighbor;
}
} // namespace tsp::neighborhood