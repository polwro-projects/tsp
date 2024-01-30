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

#include "application/iapplication.hpp"
#include "application/menu/algorithm/branch_and_bound.hpp"
#include "application/menu/algorithm/bruteforce.hpp"
#include "application/menu/algorithm/genetic_algorithm.hpp"
#include "application/menu/algorithm/simulated_annealing.hpp"
#include "application/menu/math/matrix.hpp"
#include "application/menu/route/route.hpp"
#include "ui/menu.hpp"

namespace application::menu {
/**
 * @brief This class represents the application and is used to pass data from parsers to the algorithms and print the output
 * 
 */
class Application : public application::IApplication {
public:
	/**
	 * @brief Construct a new MenuApplication object
	 * 
	 */
	Application();

public:
	/**
	 * @brief Start the application execution
	 * 
	 */
	void Start() override;

	/**
	 * @brief Calculate the solution to the TSP problem with the given algorithm
	 * 
	 * @param algorithm - the algorithm to use
	 */
	void CalculateSolution(tsp::algorithm::Algorithm* algorithm);

protected:
	/**
	 * @brief Create the application menu
	 * 
	 * @return std::unique_ptr<ui::Menu> - the pointer to the menu
	 */
	std::unique_ptr<ui::Menu> CreateMenu();

	/**
	 * @brief Output the test results 
	 * 
	 * @param value - the test results
	 */
	void OutputResults(const TestResult& value) override;

protected:
	application::menu::algorithm::BranchAndBound branch_and_bound_menu_;
	application::menu::algorithm::BruteForce bruteforce_menu_;
	application::menu::algorithm::GeneticAlgorithm genetic_menu_;
	application::menu::algorithm::SimulatedAnnealing annealing_menu_;
	application::menu::math::Matrix matrix_menu_;
	application::menu::route::Route route_menu_;

	std::unique_ptr<ui::Menu> menu_;

	std::shared_ptr<Solution> solution_{std::make_shared<Solution>()};
};
} // namespace application::menu