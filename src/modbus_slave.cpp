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
#include "modbus_slave.h"

#include <algorithm>
#include <cstdint>

#include "modbus_callback.h"
#include "modbus_opt.h"
#include "modbus_pool.h"
#include "modbus_types.h"
#include "modbus_util.h"

namespace modbus {

ModbusSlave::ModbusSlave(std::uint8_t slave_id, ArgType *arg) : _slave_id(slave_id) {
    if ((slave_id == 0) || (slave_id == 255)) {
        errorCallback("Modbus slave: invalid slave id.", arg);
    }
}

Packet *ModbusSlave::receiveAdu(Packet *packet, ArgType *arg, bool stable) {
    if (packet == nullptr) {
        errorCallback("Modbus slave: nullptr packet.", arg);
        return nullptr;
    }

    if (packet->length < MODBUS_ADU_SIZE_MIN) {
        errorCallback("Modbus slave: runt ADU received.", arg);
        return nullptr;
    }

    if (! stable) {
        packet = _copyPacket(packet, arg);
        if (packet == nullptr) {
            return nullptr;
        }
    }

    auto crc16_calc = crc16(packet->bytes, packet->length - 2);
    auto crc16_recv = readWordBE(packet->bytes, packet->length - 2);
    if (crc16_recv != crc16_calc) {
        if (! stable) {
            _pool.free(packet, arg);
        }
        return nullptr;
    }

    std::uint8_t unit_id = packet->bytes[0];
    if ((unit_id != _slave_id) && (unit_id != 255)) {
        if (! stable) {
            _pool.free(packet, arg);
        }
        return nullptr;
    }

    auto response = _pool.allocate(arg);
    if (response == nullptr) {
        if (! stable) {
            _pool.free(packet, arg);
        }
        return nullptr;
    }

    auto response_length = _receivePdu(
                packet->bytes + MODBUS_ADU_OVERHEAD,
                packet->length - MODBUS_ADU_OVERHEAD,
                response->bytes + MODBUS_ADU_OVERHEAD,
                arg);
    if (response_length == 0) {
        if (! stable) {
            _pool.free(packet, arg);
        }
        return nullptr;
    }

    response->bytes[0] = unit_id;
    crc16_calc = crc16(response->bytes, response_length + 1);
    writeWordBE(crc16_calc, response->bytes, response_length + 1);
    response->length = response_length + MODBUS_ADU_OVERHEAD;

    return response;
}

Packet *ModbusSlave::receiveMbap(Packet *packet, ArgType *arg, bool stable) {
    if (packet == nullptr) {
        errorCallback("Modbus slave: nullptr packet.", arg);
        return nullptr;
    }

    if (packet->length < MODBUS_MBAP_SIZE_MIN) {
        errorCallback("Modbus slave: runt MBAP received.", arg);
        return nullptr;
    }

    if (! stable) {
        packet = _copyPacket(packet, arg);
        if (packet == nullptr) {
            return nullptr;
        }
    }

    std::uint16_t transaction_id = readWordBE(packet->bytes, 0);

    std::uint16_t protocol_id = readWordBE(packet->bytes, 2);
    if (protocol_id != 0) {
        warningCallback("Modbus slave: MBAP protocol_id != 0.", arg);
    }

    std::uint16_t length = readWordBE(packet->bytes, 4);
    if (length != (packet->length - 6)) {
        warningCallback("Modbus slave: MBAP incorrect length in MBAP header.", arg);
    }

    std::uint8_t unit_id = packet->bytes[6];
    if ((unit_id != _slave_id) && (unit_id != 255)) {
        if (! stable) {
            _pool.free(packet, arg);
        }
        return nullptr;
    }

    auto response = _pool.allocate(arg);
    if (response == nullptr) {
        if (! stable) {
            _pool.free(packet, arg);
        }
        return nullptr;
    }

    auto response_length = _receivePdu(
                packet->bytes + MODBUS_MBAP_OVERHEAD,
                packet->length - MODBUS_MBAP_OVERHEAD,
                response->bytes + MODBUS_MBAP_OVERHEAD,
                arg);
    if (response_length == 0) {
        if (! stable) {
            _pool.free(packet, arg);
        }
        return nullptr;
    }

    writeWordBE(transaction_id, response->bytes, 0);
    writeWordBE(protocol_id, response->bytes, 2);
    writeWordBE(response_length + 1, response->bytes, 4);
    response->bytes[6] = unit_id;
    response->length = response_length + MODBUS_MBAP_OVERHEAD;

    return response;
}

std::size_t ModbusSlave::_receivePdu(const std::uint8_t *pdu, std::size_t pdu_length, std::uint8_t *response_pdu, ArgType *arg) {
    if ((pdu == nullptr) || (pdu_length < MODBUS_PDU_SIZE_MIN) || (response_pdu == nullptr)) {
        errorCallback("Modbus slave: PDU argument error.", arg);
        return 0;
    }

    std::uint8_t fc = pdu[0];
    if (isValidFunctionCodeValue(fc) &&
            ((isBuiltInFunctionCode(static_cast<FunctionCode>(fc))) || (isSupportedFunctionCallback(static_cast<FunctionCode>(fc), arg)))) {

        switch (fc) {
        case READ_DISCRETE_INPUTS:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case READ_COILS:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case WRITE_SINGLE_COIL:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case WRITE_MULTIPLE_COILS:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);

        case READ_INPUT_REGISTER:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case READ_HOLDING_REGISTERS:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case WRITE_SINGLE_REGISTER:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case WRITE_MULTIPLE_REGISTERS:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case READ_WRITE_MULTIPLE_REGISTERS:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case MASK_WRITE_REGISTER:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case READ_FIFO_QUEUE:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);

        case READ_FILE_RECORD:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case WRITE_FILE_RECORD:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);

        case READ_EXCEPTION_STATUS:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case DIAGNOSTIC:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case GET_COM_EVENT_COUNTER:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case GET_COM_EVENT_LOG:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case REPORT_SERVER_ID:
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        case READ_DEVICE_IDENTIFICATION: // TODO: Figure out how to deal with the 2 function codes in category other.
            // TODO: Implement me.
            return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
        }
    }

    return _unsupportedFc(pdu, pdu_length, response_pdu, arg);
}

std::size_t ModbusSlave::_unsupportedFc(const std::uint8_t *pdu, std::size_t pdu_length, std::uint8_t *response_pdu, ArgType *arg) {
    static_cast<void>(pdu_length);
    static_cast<void>(arg);
    std::uint8_t function_code = pdu[0];
    response_pdu[0] = function_code + MODBUS_FUNCTION_CODE_ERROR_MASK;
    response_pdu[1] = ExceptionCode::ILLEGAL_FUNCTION;
    return 2;
}

Packet *ModbusSlave::_copyPacket(Packet *packet, ArgType *arg) {
    auto copy = _pool.allocate(arg);
    if (copy == nullptr) {
        return nullptr;
    }

    std::copy(packet->bytes, packet->bytes + packet->length, copy->bytes);
    copy->length = packet->length;

    return copy;
}

} // End namespace modbus.
