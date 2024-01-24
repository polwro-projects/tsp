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

namespace application::menu::math {
/**
 * @brief The implementation of the matrix manipulation menu class
 * 
 */
class Matrix : public Menu {
public:
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
	 * @brief Get the matrix
	 * 
	 * @return std::shared_ptr<DistanceMatrix> - the pointer to the matrix instance
	 */
	std::shared_ptr<DistanceMatrix> GetMatrix() const noexcept;

protected:
	/**
	 * @brief Get the input file name
	 * 
	 * @return std::string - the name of the input file
	 */
	static std::string GetInputFile();

	/**
	 * @brief Get a random number which lies in the given range
	 * 
	 * @param min - the start of the range
	 * @param max - the end of the range
	 * @return uint32_t - a totally random number
	 */
	static uint32_t GetRandomNumber(uint32_t min, uint32_t max);

	/**
	 * @brief Generate a random matrix of the given size
	 * 
	 * @param size - the size of the matrix
	 * @return DistanceMatrix 
	 */
	static DistanceMatrix GenerateRandomMatrix(uint32_t size);

protected:
	std::shared_ptr<DistanceMatrix> matrix_{std::make_shared<DistanceMatrix>()};
};
} // namespace application::menu::math