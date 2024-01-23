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
Algorithm::Algorithm(DistanceMatrix distances, PopulationSizeType population_size)
	: tsp::algorithm::Algorithm{distances}
	, kPopulationSize{population_size} { }

void Algorithm::SetCrossoverAlgorithm(std::unique_ptr<CrossoverAlgorithmType> ptr) {
	crossover_algorithm_ = std::move(ptr);
}

void Algorithm::SetCrossoverProbability(ProbabilityType value) {
	crossover_probability_ = value;
}

void Algorithm::SetMutationAlgorithm(std::unique_ptr<MutationAlgorithmType> ptr) {
	mutation_algorithm_ = std::move(ptr);
}

void Algorithm::SetMutationProbability(ProbabilityType value) {
	mutation_probability_ = value;
}

bool Algorithm::Solve() {
	// Unset the stop flag
	is_stopped_ = false;

	PopulationType population = CreatePopulation(kPopulationSize);

	while(true) {
		// Check if the flag to stop the app was risen
		if(is_stopped_) {
			return false;
		}

		const auto pool = Select(population);
		auto children = DoCrossover(std::move(pool));
		children = Mutate(children);

		// Add the children to the population
		std::copy(children.begin(), children.end(), std::back_inserter(pool));
	}
}

Algorithm::PopulationType Algorithm::CreatePopulation(PopulationSizeType popultaion_size) const {
	PopulationType population;

	// Create the most default path (e.g. 1,2,3,4...)
	Solution::Path path(distances_.Columns());
	std::iota(path.begin(), path.end(), 0);

	// Iterate over permutations and fill the population
	do {
		// Get to the next permutation if it's length is bigger than the best one so far
		const auto distance = CalculateCost(path);
		if(distance >= solution_.cost) {
			continue;
		}

		// Save the best result
		population.emplace_back(path, distance);
	} while(population.size() < popultaion_size && std::next_permutation(path.begin(), path.end()));
}

Algorithm::SelectionPoolType Algorithm::Select(const PopulationType& population) const {
	SelectionPoolType pool;

	// Calculate total fitness
	double total_cost = 0.0;
	for(const auto& individual : population) {
		total_cost += individual.cost;
	}

	for(uint32_t iteration = 0; iteration < kPopulationSize; ++iteration) {
		// "Spin" the roulette wheel
		double spin = static_cast<double>(rand()) / RAND_MAX * total_cost;

		// Select individual based on roulette wheel
		double cumulative_cost = 0.0;
		for(const auto& individual : population) {
			cumulative_cost += individual.cost;
			if(cumulative_cost >= spin) {
				pool.push_back(individual);
				break;
			}
		}
	}

	return pool;
}

Algorithm::PopulationType Algorithm::DoCrossover(SelectionPoolType pool) const { }
} // namespace tsp::algorithm::inaccurate::genetic