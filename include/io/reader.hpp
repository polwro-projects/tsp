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

#include <fstream>
#include <string>
#include <vector>

namespace io {
/**
 * @brief This class is used to read the files
 * 
 */
class Reader {
public:
	using Data = std::vector<std::string>;

public:
	/**
	 * @brief Construct a new Reader object
	 * 
	 * @param file - the name of the file to read
	 */
	Reader(const std::string& file);

public:
	/**
	 * @brief Process the data, read from the file
	 * 
	 * @return true if the processing was successful
	 * @return false otherwise
	 */
	bool Process();

	/**
	 * @brief Get the result of the processing
	 * 
	 * @return const Data& - the vector of lines which the given file consists of
	 */
	const Data& Get() const noexcept;

protected:
	Data data_;
	std::string filename_;
};
} // namespace io