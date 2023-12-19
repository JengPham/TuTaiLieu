/*
 * modbus_crc.h
 *
 *  Created on: Dec 11, 2023
 *      Author: KarimPham
 */

#ifndef INC_MODBUS_CRC_H_
#define INC_MODBUS_CRC_H_

#include "stdint.h"
uint16_t crc16(uint8_t *buffer, uint16_t buffer_length);

#endif /* INC_MODBUS_CRC_H_ */
