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

#include "ui/menu/callable_entry.hpp"

#include <stdexcept>

namespace ui::menu {
CallableEntry::CallableEntry(std::string name, CallbackType callback)
	: Entry{name}
	, callback_{callback} { }

void CallableEntry::Enter() {
	if(!callback_) {
		throw std::runtime_error(
			"This menu entry doesn't have an associated callback. This is a bug.");
	}

	callback_();
}
} // namespace ui::menu