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

#include "io/file/route/parser.hpp"

namespace io::file::route {
Parser::Parser(Data data)
	: data_{std::move(data)} { }

bool Parser::Process() {
	// Check if the data is empty
	if(data_.empty()) {
		return false;
	}

	// Read the size
	const auto size = std::stoi(data_.at(0));

	// Read the route
	for(uint32_t index = 1; index < data_.size(); ++index) {
		const auto line = data_.at(index);
		solution_.path.push_back(std::stoi(line));
	}

	return solution_.path.size() == size;
}

const Parser::Solution& Parser::Get() const noexcept {
	return solution_;
}
} // namespace io::file::route