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

#include "tsp/operators/selection/algorithm.hpp"

namespace tsp::operators::selection {
/**
 * @brief This class is a representation of the roulette selection algorithm, 
 *        which selects the individuals based on the "spin".
 * 
 */
class Roulette : public tsp::operators::selection::Algorithm {
private:
	using CostType = tsp::algorithm::Algorithm::Solution::SizeType;

public:
	/**
	 * @brief Construct a new Roulette object
	 * 
	 * @param size - the size of a population to work with
	 */
	Roulette(PopulationSizeType size);

public:
	/**
     * @brief Do selection on the given population
     * 
     * @param population - the population to filter
	 * @param pool_size - the size of the pool
     * @return SelectionPoolType - the selected individuals
     */
	SelectionPoolType Select(PopulationType population,
							 const SelectionPoolSize pool_size) const override;

protected:
	/**
     * @brief Calculate the total cost of all the population
     * 
     * @param population - the population to calculate the cost for
     * @return CostType - the cost of the whole population
     */
	CostType CalculateTotalCost(const PopulationType& population) const;
};
} // namespace tsp::operators::selection
