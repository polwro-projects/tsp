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

namespace ui::menu {
/**
 * @brief The class represents the entry of a menu
 * 
 */
class Entry {
public:
	/**
	 * @brief Construct a new Entry object
	 * 
	 * @param name the name of the entry
	 */
	explicit Entry(std::string name);

public:
	/**
	 * @brief Get the name of the entry
	 * 
	 * @return const std::string& the name of the entry 
	 */
	const std::string& GetName() const noexcept;

	/**
	 * @brief Enter the menu entry
	 * 
	 */
	virtual void Enter() = 0;

protected:
	std::string name_;
};
} // namespace ui::menu