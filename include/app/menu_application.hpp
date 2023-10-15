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
#include "io/file/ini/parser.hpp"
#include "ui/menu.hpp"

namespace app {
/**
 * @brief This class represents the application and is used to pass data from parsers to the algorithms and print the output
 * 
 */
class MenuApplication : public IApplication {
	using DistanceMatrix = IApplication::DistanceMatrix;

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
	 * @brief Read the distance matrix from the given file
	 * 
	 * @param filename - the name of the file to use
	 * @return DistanceMatrix - the distance matrix, read from the file
	 */
	static DistanceMatrix ReadMatrix(const std::string& filename);

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

protected:
	DistanceMatrix distance_matrix_;
	std::unique_ptr<ui::Menu> menu_;
};
} // namespace app