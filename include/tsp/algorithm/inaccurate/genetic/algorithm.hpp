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

#pragma once

#include <memory>
#include <random>

#include "tsp/algorithm/algorithm.hpp"
#include "tsp/operators/crossover/algorithm.hpp"
#include "tsp/operators/mutation/algorithm.hpp"
#include "tsp/operators/selection/algorithm.hpp"

namespace tsp::algorithm::inaccurate::genetic {

/**
 * @brief The implementation of the genetic algorithm for TSP
 * 
 */
class Algorithm final : public tsp::algorithm::Algorithm {
protected:
	using CrossoverAlgorithmType = tsp::operators::crossover::Algorithm;
	using MutationAlgorithmType = tsp::operators::mutation::Algorithm;
	using SelectionAlgorithmType = tsp::operators::selection::Algorithm;

	using PopulationType = tsp::operators::Operator::PopulationType;
	using PopulationSizeType = tsp::operators::Operator::PopulationSizeType;
	using SelectionPoolSizeType = tsp::operators::crossover::Algorithm::SelectionPoolSizeType;

public:
	/**
	 * @brief Construct a new Algorithm object
	 * 
	 * @param distances - the distance matrix to use
	 * @param population_size - the size of the population
	 * @param pool_size - the size of the selection pool
	 */
	Algorithm(DistanceMatrix distances,
			  PopulationSizeType population_size,
			  SelectionPoolSizeType pool_size);

public:
	/**
	 * @brief Set the crossover algorithm
	 * 
	 * @param ptr - a pointer to the crossover algorithm
	 */
	void SetCrossoverAlgorithm(std::unique_ptr<CrossoverAlgorithmType> ptr);

	/**
	 * @brief Set the mutation algorithm
	 * 
	 * @param ptr - a pointer to the mutation algorithm
	 */
	void SetMutationAlgorithm(std::unique_ptr<MutationAlgorithmType> ptr);

	/**
	 * @brief Set the selection algorithm
	 * 
	 * @param ptr - the pointer to the selection algorithm
	 */
	void SetSelectionAlgorithm(std::unique_ptr<SelectionAlgorithmType> ptr);

	/**
	 * @brief Solve the problem
	 * 
	 * @return Solution - the solution to the problem
	 */
	bool Solve() override;

protected:
	/**
	 * @brief Create a the starting population
	 * 
	 * @param size - the size of the population
	 * @return PopulationType - a new population
	 */
	PopulationType CreatePopulation(PopulationSizeType size) const;

	/**
	 * @brief Update the costs in the population
	 * 
	 * @param population - the population to update the cost for
	 */
	PopulationType UpdateCost(PopulationType population) const;

protected:
	const PopulationSizeType kPopulationSize;
	const SelectionPoolSizeType kPoolSize;

	std::unique_ptr<CrossoverAlgorithmType> crossover_algorithm_;
	std::unique_ptr<MutationAlgorithmType> mutation_algorithm_;
	std::unique_ptr<SelectionAlgorithmType> selection_algorithm_;
};
} // namespace tsp::algorithm::inaccurate::genetic