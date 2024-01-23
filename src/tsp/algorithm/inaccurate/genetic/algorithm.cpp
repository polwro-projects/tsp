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

#include "tsp/algorithm/inaccurate/genetic/algorithm.hpp"

#include <algorithm>

namespace tsp::algorithm::inaccurate::genetic {
Algorithm::Algorithm(DistanceMatrix distances,
					 PopulationSizeType population_size,
					 SelectionPoolSizeType pool_size)
	: tsp::algorithm::Algorithm{distances}
	, kPopulationSize{population_size}
	, kPoolSize{pool_size} { }

void Algorithm::SetCrossoverAlgorithm(std::unique_ptr<CrossoverAlgorithmType> ptr) {
	crossover_algorithm_ = std::move(ptr);
}

void Algorithm::SetMutationAlgorithm(std::unique_ptr<MutationAlgorithmType> ptr) {
	mutation_algorithm_ = std::move(ptr);
}

void Algorithm::SetSelectionAlgorithm(std::unique_ptr<SelectionAlgorithmType> ptr) {
	selection_algorithm_ = std::move(ptr);
}

bool Algorithm::Solve() {
	// Check if the algorithm is supplied with all the operators needed
	if(!crossover_algorithm_ || !mutation_algorithm_ || !selection_algorithm_) {
		return false;
	}

	// Unset the stop flag
	is_stopped_ = false;

	PopulationType population = CreatePopulation(kPopulationSize);

	while(true) {
		// Check if the flag to stop the app was risen
		if(is_stopped_) {
			return false;
		}

		const auto pool = selection_algorithm_->Select(population, kPoolSize);
		population = crossover_algorithm_->Cross(std::move(pool), kPopulationSize);
		population = mutation_algorithm_->Mutate(population);
		population = UpdateCost(std::move(population));

		// Check every individual in the resulting population
		for(const auto& individual : population) {
			const auto distance = distances_(individual.path.back(), individual.path.front());
			const auto cost = individual.cost + distance;

			// Check if the cost of the solution is better than the existing one
			if(cost < solution_.cost) {
				solution_ = individual;

				// Add the last hop to the path
				solution_.path.push_back(solution_.path.front());
				solution_.cost = cost;
			}
		}
	}

	return true;
}

Algorithm::PopulationType Algorithm::CreatePopulation(PopulationSizeType popultaion_size) const {
	PopulationType population;

	// Create the most default path (e.g. 1,2,3,4...)
	Solution::Path path(distances_.Columns());
	std::iota(path.begin(), path.end(), 0);

	// Iterate over permutations and fill the population
	do {
		const auto distance = CalculateCost(path);
		population.emplace_back(path, distance);
	} while(population.size() < popultaion_size && std::next_permutation(path.begin(), path.end()));

	return population;
}

Algorithm::PopulationType Algorithm::UpdateCost(PopulationType population) const {
	// Calculate cost of every solution in the population
	for(auto iterator = population.begin(); iterator != population.end(); ++iterator) {
		iterator->cost = CalculateCost(iterator->path);
	}

	return population;
}
} // namespace tsp::algorithm::inaccurate::genetic