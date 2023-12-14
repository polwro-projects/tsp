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

#include "io/file/configuration/ini/parser.hpp"

#include <regex>

#include "io/file/configuration/ini/patterns.hpp"
#include "utils/tokenizer.hpp"

namespace io::file::configuration::ini {
Parser::Parser(Data data)
	: data_{std::move(data)} { }

bool Parser::Process() {
	if(data_.empty()) {
		return false;
	}

	// Clean the previous data, if it exists
	parameters_.clear();

	Section section;
	for(const auto& line : data_) {
		if(IsSectionHeader(line)) {
			if(!section.name.empty()) {
				parameters_.push_back(section);
			}

			// Update the section
			section.Clear();
			section.name = ProcessSectionHeader(line);

			continue;
		}

		try {
			auto property = ProcessProperty(line);
			section.properties.insert(property);
		} catch(const std::exception& e) {
			return false;
		}
	}

	// Save the latest section
	parameters_.push_back(section);

	return !parameters_.empty();
}

const Parser::Parameters& Parser::Get() const noexcept {
	return parameters_;
}

Parser::Section::Property Parser::ProcessProperty(const std::string& value) {
	auto parsed_line = utils::Tokenizer::tokenize(value, '=');
	if(parsed_line.size() != 2) {
		throw std::runtime_error("Property is not defined properly.");
	}

	return {parsed_line.at(0), parsed_line.at(1)};
}

bool Parser::IsSectionHeader(const std::string& value) {
	std::smatch match;
	return std::regex_match(value, match, kSectionHeaderPattern);
}

std::string Parser::ProcessSectionHeader(const std::string& value) {
	return value.substr(1, value.size() - 2);
}
} // namespace io::file::configuration::ini