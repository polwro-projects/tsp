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

#include <functional>
#include <string>

#include "ui/menu/entry.hpp"

namespace ui::menu {
class Submenu;
}

namespace ui {
/**
 * @brief The class represents the UI of a menu
 * 
 */
class Menu {
public:
	/**
	 * @brief Set the root menu entry
	 * 
	 * @param root - the root of the menu
	 */
	void SetRootEntry(std::shared_ptr<menu::Submenu> root) noexcept;

public:
	/**
	 * @brief Show the menu
	 * 
	 */
	void Show() const;

	/**
	 * @brief Choose the entry of the menu 
	 * 
	 * @param index - the index of the entry to choose
	 */
	void Choose(size_t index) const;

protected:
	friend class menu::Submenu;

	std::shared_ptr<menu::Submenu> root_;
};
} // namespace ui