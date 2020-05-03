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
#include "modbus_util.h"

#include <cstddef>
#include <cstdint>

namespace modbus {

std::uint16_t crc16(std::uint8_t *bytes, std::size_t length) {
    // TODO: Implement me.
    static_cast<void>(bytes);
    static_cast<void>(length);
    return 0;
}

} // End namespace modbus.
