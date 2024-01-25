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

#include "tsp/operators/selection/roulette.hpp"

#include <algorithm>

namespace tsp::operators::selection {
Roulette::Roulette(PopulationSizeType size)
	: Algorithm{size} { }

Roulette::SelectionPoolType Roulette::Select(PopulationType population,
											 const SelectionPoolSize pool_size) const {
	// Don't do anything if the population is empty
	if(population.empty()) {
		return {};
	}

	// Update the distribution boundaries
	const auto max = CalculateMaxCost(population) + 1;
	distribution_ = DistributionType(0, max);

	// Fill the pool
	SelectionPoolType pool;
	while(pool.size() < pool_size) {
		// "Spin" the roulette wheel
		double spin = distribution_(generator_);

		// Select individual based on roulette wheel
		double cumulative_cost = 0.0;
		for(auto iterator = population.begin(); iterator != population.end();) {
			cumulative_cost += max - iterator->cost;

			// Check if the individual can be added to the pool
			if(cumulative_cost >= spin) {
				// Add the selected individual to the selection pool
				pool.push_back(*iterator);

				// Erase the selected individual and get the iterator to the next element
				iterator = population.erase(iterator);

				break;
			}

			// Move to the next individual
			++iterator;
		}
	}

	return pool;
}

Roulette::CostType Roulette::CalculateMaxCost(const PopulationType& population) const {
	// Don't do anything if the population is empty
	if(population.empty()) {
		return {};
	}

	const auto max = std::max_element(population.begin(), population.end());

	return max->cost;
}
} // namespace tsp::operators::selection
