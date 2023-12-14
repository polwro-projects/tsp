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

#include <map>
#include <string>
#include <vector>

#include "io/file/iparser.hpp"
#include "io/reader.hpp"

namespace io::file::configuration::ini {
/**
 * @brief The class is dedicated to parsing INI files
 * 
 */
class Parser : virtual public IParser {
public:
	/**
	 * @brief This struct holds the data from a section of the INI file
	 * 
	 */
	struct Section {
		using Property = std::pair<std::string, std::string>;

		std::string name;
		std::map<std::string, std::string> properties;

		/**
		 * @brief Clear the section
		 * 
		 */
		void Clear() {
			name.clear();
			properties.clear();
		}
	};

	using Parameters = std::vector<Section>;
	using Data = io::Reader::Data;

public:
	/**
	 * @brief Construct a new Parser object
	 * 
	 * @param data - the data read from the file
	 */
	explicit Parser(Data data);

public:
	/**
	 * @brief Process the data, received from the reader
	 * 
	 * @return true if the processing was successful
	 * @return false otherwise
	 */
	bool Process();

	/**
	 * @brief Get the result of the processing
	 * 
	 * @return const Parameters& - the vector of sections with the parameters read from the file
	 */
	const Parameters& Get() const noexcept;

protected:
	/**
	 * @brief Process the string and fill the property using data from it
	 * 
	 * @param value - the string to process
	 * @return Section::Property - the processed property
	 */
	static Section::Property ProcessProperty(const std::string& value);

	/**
	 * @brief Check if the given stirng contains the section's header
	 * 
	 * @param value - the string to check
	 * @return true if the string contains the section's header
	 * @return false otherwise
	 */
	static bool IsSectionHeader(const std::string& value);

	/**
	 * @brief Process the string and return the name of the section
	 * 
	 * @param value - the string to process
	 * @return std::string the name of the section
	 */
	static std::string ProcessSectionHeader(const std::string& value);

protected:
	Parameters parameters_;
	Data data_;
};
} // namespace io::file::configuration::ini