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

#include <string>

#include "io/file/problem/iproblemparser.hpp"

namespace io::file::problem::tsp {
/**
 * @brief This class is used to parse TSP files
 * 
 */
class Parser : virtual public IProblemParser {
public:
	/**
	 * @brief Construct a new Parser object
	 * 
	 * @param data - the data to use for parsing
	 */
	explicit Parser(Data data);

public:
	/**
	 * @brief Process the data, received from the reader
	 * 
	 * @return true if the processing was successful
	 * @return false otherwise
	 */
	bool Process() override;

protected:
	/**
	 * @brief Check of the string contains the dimension parameter
	 * 
	 * @param value - the string to check
	 * @return true if the string contains the parameter
	 * @return false otherwise
	 */
	bool IsDimensionParameter(const std::string& value) const;

	/**
	 * @brief Get the dimension parameter
	 * 
	 * @param value - the string to process
	 * @return uint32_t - the parameter
	 */
	uint32_t GetDimensionParameter(const std::string& value) const;

	/**
	 * @brief Check if the line contains matrix data
	 * 
	 * @param value - the line to check
	 * @return true if the line contains matrix data
	 * @return false otherwise
	 */
	bool HasMatrixData(const std::string& value) const;

	/**
	 * @brief Get the distance matrix from the given data
	 * 
	 * @param data - the data to parse to get the matrix
	 * @return DistanceMatrix - the matrix, parsed from the given data
	 */
	DistanceMatrix GetDistanceMatrix(const Data& data) const;

protected:
	uint32_t dimension_;
};
} // namespace io::file::problem::tsp