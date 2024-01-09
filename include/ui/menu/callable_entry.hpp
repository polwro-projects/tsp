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
#include <memory>
#include <string>

#include "ui/menu/entry.hpp"

namespace ui::menu {
/**
 * @brief The class represents a callable entry of a menu
 * 
 */
class CallableEntry : public Entry {
public:
	using CallbackType = std::function<void()>;

public:
	/**
	 * @brief Construct a new Callable Entry object
	 * 
	 * @param name - the name of the menu
	 * @param callback - the callback to be called when this menu is chosen
	 */
	CallableEntry(std::string name, CallbackType callback);

public:
	/**
	 * @brief Enter the menu entry
	 * 
	 */
	void Enter();

protected:
	const CallbackType callback_;
};
} // namespace ui::menu