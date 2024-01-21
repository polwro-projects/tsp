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

#include "tsp/operators/crossover/algorithm.hpp"

namespace tsp::operators::crossover {
/**
 * @brief This class is a representation of the order type of crossover for 
 * 		  the genetic algorithm. 
 * 
 */
class OX : protected tsp::operators::crossover::Algorithm {
public:
	/**
	 * @brief Construct a new OX object
	 * 
	 * @param path_size - the size of a path to work with
	 */
	OX(PathSizeType path_size);

public:
	/**
	 * @brief Implementation of the crossing function
	 * 
	 * @param lhs - the first parent
	 * @param rhs - the second parent
	 * @return Path - the result of crossing two parents
	 */
	Path Cross(Path lhs, Path rhs) const override;
};
} // namespace tsp::operators::crossover
