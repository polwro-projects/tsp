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

#include "io/file/iparser.hpp"
#include "tsp/algorithm/algorithm.hpp"

namespace io::file::route {
/**
 * @brief The class is dedicated to parsing route TXT files
 * 
 */
class Parser : virtual public IParser {
	using Data = io::Reader::Data;
	using Solution = tsp::algorithm::Algorithm::Solution;

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
	const Solution& Get() const noexcept;

protected:
	Data data_;
	Solution solution_;
};
} // namespace io::file::route