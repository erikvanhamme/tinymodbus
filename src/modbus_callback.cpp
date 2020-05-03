/*
 * Copyright 2020 Erik Van Hamme (erik.vanhamme@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "modbus_callback.h"

#include <string>

#include "modbus_opt.h"
#include "modbus_types.h"

namespace modbus {

MODBUS_WEAK void errorCallback(std::string message, ArgType *arg) {
    static_cast<void>(message);
    static_cast<void>(arg);
}

MODBUS_WEAK void warningCallback(std::string message, ArgType *arg) {
    static_cast<void>(message);
    static_cast<void>(arg);
}

MODBUS_WEAK bool isSupportedFunctionCallback(FunctionCode fc, ArgType *arg) {
    static_cast<void>(fc);
    static_cast<void>(arg);
    return false;
}

} // End namespace modbus.
