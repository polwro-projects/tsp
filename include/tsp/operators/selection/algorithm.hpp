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

#include "tsp/algorithm/algorithm.hpp"
#include "tsp/operators/operator.hpp"

namespace tsp::operators::selection {
/**
 * @brief This is a base class for all the algorithms for selection (which is needed for the genetic algorithm)
 * 
 */
class Algorithm : protected Operator {
public:
	using SelectionPoolType = std::vector<tsp::algorithm::Algorithm::Solution>;
	using SelectionPoolSize = uint32_t;
	using PopulationType = std::vector<tsp::algorithm::Algorithm::Solution>;
	using PopulationSizeType = uint32_t;

public:
	/**
	 * @brief Construct a new Algorithm object
	 * 
	 * @param size - the size of the population to work with
	 */
	explicit Algorithm(PopulationSizeType size);

public:
	/**
     * @brief Do selection on the given population
     * 
     * @param population - the population to filter
	 * @param pool_size - the size of the pool
     * @return SelectionPoolType - the selected individuals
     */
	virtual SelectionPoolType Select(PopulationType population,
									 const SelectionPoolSize pool_size) const = 0;

protected:
	const PopulationSizeType kPopulationSize;
};
} // namespace tsp::operators::selection
