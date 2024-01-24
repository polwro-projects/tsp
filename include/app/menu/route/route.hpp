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

#include "app/menu/menu.hpp"
#include "io/file/problem/iproblemparser.hpp"
#include "tsp/algorithm/algorithm.hpp"

namespace application::menu::route {
/**
 * @brief The implementation of the matrix manipulation menu class
 * 
 */
class Route : public Menu {
	using Solution = tsp::algorithm::Algorithm::Solution;
	using DistanceMatrix = io::file::problem::IProblemParser::DistanceMatrix;

public:
	/**
     * @brief Create a Menu object
     * 
     * @param menu - the top level menu object 
     * @return std::unique_ptr<ui::menu::Submenu> - the submenu instance
     */
	std::unique_ptr<ui::menu::Submenu> Create(ui::Menu* menu) override;

	/**
	 * @brief Set the solution pointer
	 * 
	 * @param ptr - the pointer to the solution instance
	 */
	void SetSolution(std::shared_ptr<Solution> ptr);

	/**
     * @brief Set the distance matrix
     * 
     * @param matrix - the matrix pointer to store
     */
	void SetDistanceMatrix(const std::shared_ptr<DistanceMatrix> matrix) noexcept;

protected:
	std::shared_ptr<Solution> solution_;
	std::shared_ptr<DistanceMatrix> matrix_;
	std::string output_file_;
};
} // namespace application::menu::route