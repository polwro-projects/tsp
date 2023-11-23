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

#include "io/reader.hpp"

namespace io {
Reader::Reader(const std::string& file)
	: filename_{file} { }

bool Reader::Process() {
	// Open the given file
	std::ifstream stream{filename_};
	if(!stream.is_open()) {
		return false;
	}

	std::string line;
	while(std::getline(stream, line)) {
		// Don't do anything if the line is empty
		if(line.empty()) {
			continue;
		}

		// Remove the end of line symbols
		line.erase(std::remove_if(line.begin(),
								  line.end(),
								  [](char symbol) { return symbol == '\n' || symbol == '\r'; }),
				   line.cend());

		// Add the line to the container
		data_.emplace_back(std::move(line));
	}

	return !data_.empty();
}

const Reader::Data& Reader::Get() const noexcept {
	return data_;
}

} // namespace io