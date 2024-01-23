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

#include "tsp/algorithm/algorithm.hpp"
#include "tsp/operators/crossover/algorithm.hpp"
#include "tsp/operators/mutation/algorithm.hpp"

namespace tsp::algorithm::inaccurate::genetic {

/**
 * @brief The implementation of the genetic algorithm for TSP
 * 
 */
class Algorithm final : public tsp::algorithm::Algorithm {
public:
	using CrossoverAlgorithmType = tsp::operators::crossover::Algorithm;
	using MutationAlgorithmType = tsp::operators::mutation::Algorithm;
	using ProbabilityType = float;
	using PopulationSizeType = uint32_t;
	using PopulationType = std::vector<Solution>;
	using SelectionPoolType = std::vector<Solution>;
	using PathSizeType = Solution::Path::size_type;

public:
	/**
	 * @brief Construct a new Algorithm object
	 * 
	 * @param distances - the distance matrix to use
	 * @param population_size - the size of the population
	 */
	Algorithm(DistanceMatrix distances, PopulationSizeType population_size);

public:
	/**
	 * @brief Set the crossover algorithm
	 * 
	 * @param ptr - a pointer to the crossover algorithm
	 */
	void SetCrossoverAlgorithm(std::unique_ptr<CrossoverAlgorithmType> ptr);

	/**
	 * @brief Set the crossover probability
	 * 
	 * @param value - a new value of the crossing probability
	 */
	void SetCrossoverProbability(ProbabilityType value);

	/**
	 * @brief Set the mutation algorithm
	 * 
	 * @param ptr - a pointer to the mutation algorithm
	 */
	void SetMutationAlgorithm(std::unique_ptr<MutationAlgorithmType> ptr);

	/**
	 * @brief Set the mutation probability
	 * 
	 * @param value - a new value of the mutation probability
	 */
	void SetMutationProbability(ProbabilityType value);

	/**
	 * @brief Solve the problem
	 * 
	 * @return Solution - the solution to the problem
	 */
	bool Solve() override;

protected:
	PopulationType CreatePopulation(PopulationSizeType size) const;
	SelectionPoolType Select(const PopulationType& population) const;
	PopulationType DoCrossover(SelectionPoolType pool) const;
	PopulationType Mutate(PopulationType population) const;

protected:
	const PopulationSizeType kPopulationSize;

	std::unique_ptr<CrossoverAlgorithmType> crossover_algorithm_;
	ProbabilityType crossover_probability_;

	std::unique_ptr<MutationAlgorithmType> mutation_algorithm_;
	ProbabilityType mutation_probability_;
};
} // namespace tsp::algorithm::inaccurate::genetic