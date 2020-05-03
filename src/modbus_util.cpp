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

bool isValidFunctionCodeValue(std::uint8_t fc) {
    switch (fc) {
    case READ_DISCRETE_INPUTS: // Falls through.
    case READ_COILS: // Falls through.
    case WRITE_SINGLE_COIL: // Falls through.
    case WRITE_MULTIPLE_COILS: // Falls through.
    case READ_INPUT_REGISTER: // Falls through.
    case READ_HOLDING_REGISTERS: // Falls through.
    case WRITE_SINGLE_REGISTER: // Falls through.
    case WRITE_MULTIPLE_REGISTERS: // Falls through.
    case READ_WRITE_MULTIPLE_REGISTERS: // Falls through.
    case MASK_WRITE_REGISTER: // Falls through.
    case READ_FIFO_QUEUE: // Falls through.
    case READ_FILE_RECORD: // Falls through.
    case WRITE_FILE_RECORD: // Falls through.
    case READ_EXCEPTION_STATUS: // Falls through.
    case DIAGNOSTIC: // Falls through.
    case GET_COM_EVENT_COUNTER: // Falls through.
    case GET_COM_EVENT_LOG: // Falls through.
    case REPORT_SERVER_ID: // Falls through.
    case READ_DEVICE_IDENTIFICATION:
        return true;
    default:
        return false;
    }
}

bool isBuiltInFunctionCode(FunctionCode fc) {
    // TODO: Implement me.
    static_cast<void>(fc);
    return false;
}

} // End namespace modbus.
