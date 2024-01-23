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

#include "tsp/operators/crossover/algorithm.hpp"

namespace tsp::operators::crossover {
Algorithm::Algorithm(PathSizeType path_size)
	: Operator{path_size - 1}
	, kPathSize{path_size} {

	// Set up the random float generator
	std::random_device device;
	generator_ = ProbabilityGeneratorType{device()};
}

std::tuple<Algorithm::PathIndexType, Algorithm::PathIndexType> Algorithm::GetRandomRange() const {
	// Generate the starting index
	PathIndexType start = distribution_(generator_);
	start = start == (kPathSize - 1) ? start - 2 : start;

	// Try to generate the end index to be greater than the start one
	PathIndexType end;
	do {
		end = distribution_(generator_);
	} while(end <= start);

	return {start, end};
}

Algorithm::PopulationType Algorithm::Cross(SelectionPoolType pool, PopulationSizeType size) const {
	PopulationType population;
	while(population.size() < size) {
		// Get two random parents
		const auto first = pool.at(rand() % pool.size());
		const auto second = pool.at(rand() % pool.size());

		// If the probability is not met, push the parents to the population
		const auto probability = probability_distribution_(probability_generator_);
		if(probability >= probability_) {
			// Add the child to the result population
			population.push_back(std::move(first));
			population.push_back(std::move(second));

			continue;
		}

		// Add the children to the  population
		population.emplace_back(Cross(first.path, second.path), 0);
		population.emplace_back(Cross(second.path, first.path), 0);
	}

	return population;
}

void Algorithm::SetProbability(ProbabilityType value) {
	probability_ = value;
}
} // namespace tsp::operators::crossover
