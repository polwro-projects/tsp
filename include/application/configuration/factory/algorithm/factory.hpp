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

#include "io/file/configuration/ini/parser.hpp"
#include "tsp/algorithm/algorithm.hpp"

namespace application::configuration::factory::algorithm {
class Factory {
protected:
	using ConfigurationParameters = io::file::configuration::ini::Parser::Parameters;
	using DistanceMatrix = io::file::problem::IProblemParser::DistanceMatrix;

public:
	/**
	 * @brief Create an algorithm based on the input
	 * 
	 * @param matrix - the distance matrix 
	 * @return std::unique_ptr<tsp::algorithm::Algorithm> - a pointer to the algorithm instance or nullptr
	 */
	virtual std::unique_ptr<tsp::algorithm::Algorithm>
	Create(const DistanceMatrix& matrix, const ConfigurationParameters& parameters) const = 0;
};

} // namespace application::configuration::factory::algorithm