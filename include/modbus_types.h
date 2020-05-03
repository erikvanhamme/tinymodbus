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
#ifndef MODBUS_TYPES_H
#define MODBUS_TYPES_H

#include <cstddef>
#include <cstdint>

namespace modbus {

static constexpr const std::size_t MODBUS_ADU_OVERHEAD = 3;
static constexpr const std::size_t MODBUS_MBAP_OVERHEAD = 7;

static constexpr const std::size_t MODBUS_PDU_SIZE_MIN = 1;
static constexpr const std::size_t MODBUS_ADU_SIZE_MIN = MODBUS_PDU_SIZE_MIN + MODBUS_ADU_OVERHEAD;
static constexpr const std::size_t MODBUS_MBAP_SIZE_MIN = MODBUS_PDU_SIZE_MIN + MODBUS_MBAP_OVERHEAD;

static constexpr const std::size_t MODBUS_PDU_SIZE_MAX = 253;
static constexpr const std::size_t MODBUS_ADU_SIZE_MAX = MODBUS_PDU_SIZE_MAX + MODBUS_ADU_OVERHEAD;
static constexpr const std::size_t MODBUS_MBAP_SIZE_MAX = MODBUS_PDU_SIZE_MAX + MODBUS_MBAP_OVERHEAD;

struct Packet {
    std::size_t length;
    std::uint8_t *bytes;

    Packet() : length(0), bytes(nullptr) {
    }
};

} // End namespace modbus.

#endif // MODBUS_TYPES_H
