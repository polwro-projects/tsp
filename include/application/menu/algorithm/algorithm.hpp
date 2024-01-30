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

#include "application/menu/menu.hpp"
#include "io/file/problem/iproblemparser.hpp"
#include "tsp/algorithm/inaccurate/sa/linear.hpp"

namespace application ::menu {
class Application;
} // namespace application::menu

namespace application::menu::algorithm {
/**
 * @brief The implementation of the simulated annealing menu class
 * 
 */
class Algorithm : public Menu {
public:
	using DistanceMatrix = io::file::problem::IProblemParser::DistanceMatrix;

public:
	/**
      * @brief Construct a new Algorithm object
      * 
      * @param application - a pointer to the menu application instance
      */
	Algorithm(application::menu::Application* application);

public:
	/**
     * @brief Set the distance matrix
     * 
     * @param matrix - the matrix pointer to store
     */
	void SetDistanceMatrix(const std::shared_ptr<DistanceMatrix> matrix) noexcept;

protected:
	std::shared_ptr<DistanceMatrix> matrix_;
	Application* application_;
};
} // namespace application::menu::algorithm