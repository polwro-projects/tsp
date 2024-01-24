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

#include "app/menu/math/matrix.hpp"

#include <memory>
#include <random>

#include "app/iapplication.hpp"
#include "ui/menu/callable_entry.hpp"
#include "ui/menu/submenu.hpp"

namespace application::menu::math {

std::unique_ptr<ui::menu::Submenu> Matrix::Create(ui::Menu* menu) {
	auto read_entry =
		std::make_shared<ui::menu::CallableEntry>("Read matrix from the file", [this]() {
			if(!matrix_) {
				std::cout << "The matrix instance is not created. This is a bug." << std::endl;
				return;
			}

			const auto filename = std::move(GetInputFile());
			*matrix_ = std::move(app::IApplication::ReadMatrix(filename));
		});

	auto generate_entry =
		std::make_shared<ui::menu::CallableEntry>("Generate a random matrix", [this]() {
			if(!matrix_) {
				std::cout << "The matrix instance is not created. This is a bug." << std::endl;
				return;
			}

			uint32_t size;
			std::cout << "Please, enter the size of the matrix: ";
			std::cin >> size;

			// Handle some smartasses' requests to generate 0x0 matrixes
			if(size == 0) {
				std::cout << "The size is incorrect. Please, try again." << std::endl;
				return;
			}

			*matrix_ = std::move(GenerateRandomMatrix(size));
		});

	auto print_entry = std::make_shared<ui::menu::CallableEntry>("Print current matrix", [this]() {
		if(!matrix_) {
			std::cout << "The matrix instance is not created. This is a bug." << std::endl;
			return;
		}

		std::cout << *matrix_ << std::endl;
	});

	auto submenu = std::make_unique<ui::menu::Submenu>("Matrix manipulation", menu);
	submenu->AddChild(read_entry);
	submenu->AddChild(generate_entry);
	submenu->AddChild(print_entry);

	return std::move(submenu);
}

std::shared_ptr<Matrix::DistanceMatrix> Matrix::GetMatrix() const noexcept {
	return matrix_;
}

std::string Matrix::GetInputFile() {
	std::string filename;
	std::cout << "Please, enter the name of the file: ";
	std::cin >> filename;

	return filename;
}

uint32_t Matrix::GetRandomNumber(uint32_t min, uint32_t max) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}

Matrix::DistanceMatrix Matrix::GenerateRandomMatrix(uint32_t size) {
	DistanceMatrix matrix;
	for(uint32_t row_index = 0; row_index < size; ++row_index) {
		DistanceMatrix::RowType row;
		for(uint32_t column_index = 0; column_index < size; ++column_index) {
			if(column_index == row_index) {
				row.push_back(-1);
				continue;
			}

			// Generate a random value to be used as a distance
			const auto value = GetRandomNumber(1, size);
			row.push_back(value);
		}

		matrix.InsertRow(std::move(row));
	}
	return std::move(matrix);
}
} // namespace application::menu::math