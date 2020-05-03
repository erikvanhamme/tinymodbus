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

static constexpr const std::uint8_t MODBUS_FUNCTION_CODE_ERROR_MASK = 0x80;

struct Packet {
    std::size_t length;
    std::uint8_t *bytes;

    Packet() : length(0), bytes(nullptr) {
    }
};

enum FunctionCode : std::uint8_t {
    // Bit access.
    READ_DISCRETE_INPUTS = 0x02,
    READ_COILS = 0x01,
    WRITE_SINGLE_COIL = 0x05,
    WRITE_MULTIPLE_COILS = 0x0F,

    // Register access.
    READ_INPUT_REGISTER = 0x04,
    READ_HOLDING_REGISTERS = 0x03,
    WRITE_SINGLE_REGISTER = 0x06,
    WRITE_MULTIPLE_REGISTERS = 0x10,
    READ_WRITE_MULTIPLE_REGISTERS = 0x17,
    MASK_WRITE_REGISTER = 0x16,
    READ_FIFO_QUEUE = 0x18,

    // File record access.
    READ_FILE_RECORD = 0x14,
    WRITE_FILE_RECORD = 0x15,

    // Diagnostics.
    READ_EXCEPTION_STATUS = 0x07,
    DIAGNOSTIC = 0x08,
    GET_COM_EVENT_COUNTER = 0x0b,
    GET_COM_EVENT_LOG = 0x0c,
    REPORT_SERVER_ID = 0x11,
    READ_DEVICE_IDENTIFICATION = 0x2b,

    // Other.
    ENCAPSULATED_INTERFACE_TRANSPORT = 0x2b,
    CANOPEN_GENERAL_REFERENCE = 0x2b,
};

enum ExceptionCode : std::uint8_t {
    ILLEGAL_FUNCTION = 0x01,
    ILLEGAL_DATA_ADDRESS = 0x02,
    ILLEGAL_DATA_VALUE = 0x03,
    SERVER_DEVICE_FAILURE = 0x04,
    ACKNOWLEDGE = 0x05,
    SERVER_DEVICE_BUSY = 0x06,
    MEMORY_PARITY_ERROR = 0x08,
    GATEWAY_PATH_UNAVAILABLE = 0x0a,
    GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND = 0x0b,
};

} // End namespace modbus.

#endif // MODBUS_TYPES_H
