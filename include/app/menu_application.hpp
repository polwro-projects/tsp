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

#include "app/iapplication.hpp"
#include "tsp/algorithm/algorithm.hpp"
#include "ui/menu.hpp"

namespace app {
/**
 * @brief This class represents the application and is used to pass data from parsers to the algorithms and print the output
 * 
 */
class MenuApplication : public IApplication {
public:
	/**
	 * @brief Construct a new MenuApplication object
	 * 
	 */
	MenuApplication();

	/**
	 * @brief Destroy the MenuApplication object
	 * 
	 */
	virtual ~MenuApplication() = default;

public:
	/**
	 * @brief Start the application execution
	 * 
	 */
	void Start() override;

	/**
	 * @brief Get the input file name
	 * 
	 * @return std::string - the name of the input file
	 */
	static std::string GetInputFile();

protected:
	/**
	 * @brief Create the application menu
	 * 
	 * @return std::unique_ptr<ui::Menu> - the pointer to the menu
	 */
	std::unique_ptr<ui::Menu> CreateMenu();

	/**
	 * @brief Create the SA algorithm submenu
	 * 
	 * @param menu - the menu object to be used in the submenu instance
	 * @return std::unique_ptr<ui::Submenu> the submenu with the SA entries
	 */
	std::unique_ptr<ui::menu::Submenu> CreateSASubmenu(ui::Menu* menu);

	/**
	 * @brief Create the matrix manipulation submenu
	 * 
	 * @param menu - the menu object to be used in the submenu instance
	 * @return std::unique_ptr<ui::Submenu> the submenu with the matrix modification entries
	 */
	std::unique_ptr<ui::menu::Submenu> CreateMatrixSubmenu(ui::Menu* menu);

	/**
	 * @brief Output the test results 
	 * 
	 * @param value - the test results
	 */
	void OutputResults(const TestResult& value) override;

	/**
	 * @brief Generate a random matrix of the given size
	 * 
	 * @param size - the size of the matrix
	 * @return DistanceMatrix 
	 */
	static DistanceMatrix GenerateRandomMatrix(uint32_t size);

	/**
	 * @brief Get a random number which lies in the given range
	 * 
	 * @param min - the start of the range
	 * @param max - the end of the range
	 * @return uint32_t - a totally random number
	 */
	static uint32_t GetRandomNumber(uint32_t min, uint32_t max);

protected:
	DistanceMatrix distance_matrix_;
	std::unique_ptr<ui::Menu> menu_;
};
} // namespace app