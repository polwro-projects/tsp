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
#include <vector>

#include "io/file/iparser.hpp"
#include "io/reader.hpp"
#include "math/matrix.hpp"

namespace io::file::problem {
/**
 * @brief This class is used to parse TXT files
 * 
 */
class IProblemParser : virtual public IParser {
public:
	using DistanceMatrix = math::Matrix<int32_t, std::vector>;
	using Data = io::Reader::Data;

public:
	/**
	 * @brief Construct a new IProblemParser object
	 * 
	 * @param data - the data to use for parsing
	 */
	explicit IProblemParser(Data data);

	/**
     * @brief Destroy the IProblemParser object
     * 
     */
	virtual ~IProblemParser() = default;

public:
	/**
	 * @brief Get the result of the processing
	 * 
	 * @return const DistanceMatrix& - the distance matrix to use for calculations
	 */
	const DistanceMatrix& Get() const noexcept;

protected:
	DistanceMatrix matrix_;
	Data data_;
};
} // namespace io::file::problem