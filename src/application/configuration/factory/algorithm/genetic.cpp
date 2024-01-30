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

#include "application/configuration/factory/algorithm/genetic.hpp"

#include <algorithm>

#include "tsp/operators/crossover/ox.hpp"
#include "tsp/operators/mutation/swap.hpp"
#include "tsp/operators/selection/roulette.hpp"

namespace application::configuration::factory::algorithm {

std::unique_ptr<tsp::algorithm::Algorithm>
Genetic ::Create(const DistanceMatrix& matrix, const ConfigurationParameters& parameters) const {
	const auto crossover_algorithm = new tsp::operators::crossover::OX(matrix.Columns());
	crossover_algorithm->SetProbability(GetCrossoverProbability(parameters));

	const auto mutation_algorithm = new tsp::operators::mutation::Swap(matrix.Columns());
	mutation_algorithm->SetProbability(GetMutationProbability(parameters));

	const auto population = GetPopulationSize(parameters);
	const auto selection_algorithm = new tsp::operators::selection::Roulette(population);

	auto algorithm = std::make_unique<tsp::algorithm::inaccurate::genetic::Algorithm>(
		matrix, population, population / 2);
	algorithm->SetCrossoverAlgorithm(
		std::unique_ptr<tsp::operators::crossover::Algorithm>{crossover_algorithm});
	algorithm->SetMutationAlgorithm(
		std::unique_ptr<tsp::operators::mutation::Algorithm>(mutation_algorithm));
	algorithm->SetSelectionAlgorithm(
		std::unique_ptr<tsp::operators::selection::Algorithm>(selection_algorithm));
	return algorithm;
}

Genetic::PopulationSizeType
Genetic::GetPopulationSize(const ConfigurationParameters& parameters) const {
	// FIXME : std::stoi doesn't belong here where aliases are used
	// FIXME : no exception handling

	const auto key = "population";
	const auto iterator = std::find_if(parameters.begin(), parameters.end(), [&](auto section) {
		return section.properties.contains(key);
	});

	return iterator != parameters.end() ? std::stoi(iterator->properties.at(key)) : 0;
}

Genetic::ProbabilityType
Genetic::GetCrossoverProbability(const ConfigurationParameters& parameters) const {
	// FIXME : std::stof doesn't belong here where aliases are used
	// FIXME : no exception handling

	const auto key = "crossover_probability";
	const auto iterator = std::find_if(parameters.begin(), parameters.end(), [&](auto section) {
		return section.properties.contains(key);
	});

	return iterator != parameters.end() ? std::stof(iterator->properties.at(key)) : 0.0;
}

Genetic::ProbabilityType
Genetic::GetMutationProbability(const ConfigurationParameters& parameters) const {
	// FIXME : std::stof doesn't belong here where aliases are used
	// FIXME : no exception handling

	const auto key = "mutation_probability";
	const auto iterator = std::find_if(parameters.begin(), parameters.end(), [&](auto section) {
		return section.properties.contains(key);
	});

	return iterator != parameters.end() ? std::stof(iterator->properties.at(key)) : 0.0;
}
} // namespace application::configuration::factory::algorithm