/*
 * MODBUS_CRC.h
 *
 *  Created on: Dec 12, 2023
 *  Author    : Phong Thanh-Pham
 *  Email     : Phong.PT.HUST@gmail.com
 *
 */

/******************************************************************************
 * Multiple include protection
 *****************************************************************************/

#ifndef INC_MODBUS_CRC_H_
#define INC_MODBUS_CRC_H_

/*******************************************************************************
 * Include
 ******************************************************************************/
#include "stdint.h"

/*******************************************************************************
 * API
 ******************************************************************************/

/**
  * @brief: Calculates the 16-bit CRC value for the given data buffer.
  * @param[in] buffer: Pointer to the data buffer for which
  * CRC is to be calculated.
  * @param[in] buffer_length: Length of the data buffer.
  * @reVal: The calculated CRC value.
  */
uint16_t crc16(const uint8_t *buffer, uint16_t buffer_length);

#endif /* INC_MODBUS_CRC_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
