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

namespace tsp::neighborhood {
class Algorithm {
protected:
	using Path = tsp::algorithm::Algorithm::Solution::Path;

public:
	/**
     * @brief Get the neighbor for the existing path
     * 
     * @param path the path to find a soltuion in the neighborhood for
     * @return Path the path that is in a neighborhood to the existing one
     */
	virtual Path GetNeighbor(const Path& path) noexcept = 0;
};
} // namespace tsp::neighborhood