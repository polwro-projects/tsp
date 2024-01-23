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

#include "tsp/operators/operator.hpp"

namespace tsp::operators::mutation {
/**
 * @brief This is a base class for all the algorithms for mutation (which is needed for the genetic algorithm)
 * 
 */
class Algorithm : protected Operator {
protected:
	using Path = tsp::algorithm::Algorithm::Solution::Path;
	using PathSizeType = Path::size_type;
	using PathIndexType = Path::size_type;

private:
	using ProbabilityType = float;
	using ProbabilityGeneratorType = std::mt19937;
	using ProbabilityDistributionType = std::uniform_real_distribution<ProbabilityType>;

public:
	/**
	 * @brief Construct a new Algorithm object
	 * 
	 * @param path_size - the size of a path to work with
	 */
	explicit Algorithm(PathSizeType path_size);

public:
	/**
	 * @brief Implementation of the mutation function
	 * 
	 * @param lhs - the first parent
	 * @param rhs - the second parent
	 * @return Path - the result of crossing two parents
	 */
	virtual Path Mutate(Path rhs) const = 0;

	/**
	 * @brief Mutate the population using the supplied mutation algorithm
	 * 
	 * @param population - the population to change
	 * @return PopulationType - a new population, created from the supplied one
	 */
	PopulationType Mutate(PopulationType population) const;

	/**
	 * @brief Set the mutation probability
	 * 
	 * @param value - a new value of the mutation probability
	 */
	void SetProbability(ProbabilityType value);

protected:
	/**
	 * @brief Get a random index inside of the predefined range
	 * 
	 * @return PathIndexType - a random index inside of the path range
	 */
	PathIndexType GetRandomIndex() const;

private:
	ProbabilityType probability_;
	mutable ProbabilityGeneratorType probability_generator_;
	mutable ProbabilityDistributionType probability_distribution_{0, 1};
};
} // namespace tsp::operators::mutation
