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

#include "application/menu/route/route.hpp"

#include "io/file/route/parser.hpp"
#include "ui/menu/callable_entry.hpp"
#include "ui/menu/submenu.hpp"

namespace application::menu::route {

std::unique_ptr<ui::menu::Submenu> Route::Create(ui::Menu* menu) {
	auto file_entry = std::make_shared<ui::menu::CallableEntry>("Change the output file", [this]() {
		std::cout << "Please, enter the name of the output file: ";
		std::cin >> output_file_;
	});

	auto read_entry =
		std::make_shared<ui::menu::CallableEntry>("Read the route from the file", [this]() {
			io::Reader reader(output_file_);
			if(!reader.Process()) {
				std::cout << "[ERROR] Reading the file failed." << std::endl;
				return;
			}

			// Read the matrix from the file
			io::file::route::Parser parser(reader.Get());
			if(!parser.Process()) {
				std::cout << "[ERROR] Parsing the file failed." << std::endl;
				return;
			}

			*solution_ = parser.Get();
		});

	auto write_entry =
		std::make_shared<ui::menu::CallableEntry>("Write the route to the file", [this]() {
			if(solution_->path.empty()) {
				std::cout << "[ERROR] The solution to write does not exists." << std::endl;
				return;
			}

			std::ofstream file{output_file_};
			if(!file.is_open()) {
				std::cout << "[ERROR] The file was not opened." << std::endl;
				return;
			}

			file << solution_->path.size() << std::endl;
			for(const auto index : solution_->path) {
				file << index << std::endl;
			}
		});

	auto cost_entry =
		std::make_shared<ui::menu::CallableEntry>("Calculate the cost of the route", [this]() {
			// Check if the matrix exists
			if(!matrix_) {
				std::cout << "[ERROR] The distance matrix does not exist." << std::endl;
				return;
			}

			// Check if the solution exists
			if(solution_->path.empty()) {
				std::cout << "[ERROR] The solution does not exist." << std::endl;
				return;
			}

			uint32_t cost{};
			for(uint32_t index = 0; index < solution_->path.size() - 1; ++index) {
				const auto start = solution_->path.at(index);
				const auto end = solution_->path.at(index + 1);
				cost += (*matrix_)(start, end);
			}
			std::cout << "Cost: " << cost << std::endl;
		});

	auto submenu = std::make_unique<ui::menu::Submenu>("Route manipulation", menu);
	submenu->AddChild(file_entry);
	submenu->AddChild(read_entry);
	submenu->AddChild(write_entry);
	submenu->AddChild(cost_entry);

	return std::move(submenu);
}

void Route::SetSolution(std::shared_ptr<Solution> ptr) {
	solution_ = ptr;
}

void Route::SetDistanceMatrix(const std::shared_ptr<DistanceMatrix> matrix) noexcept {
	matrix_ = matrix;
}
} // namespace application::menu::route