/*
 * XY-MD02.h
 *
 *  Created on: Dec 12, 2023
 *      Author: KarimPham
 */

#ifndef INC_XY_MD02_H_
#define INC_XY_MD02_H_

#include "modbus_crc.h"
#include "main.h"

typedef struct {
	float Temp;
	float Humi;
} Data_XY_MD20;

void send_data(UART_HandleTypeDef *huart, uint8_t *data);
void get_temp_humi(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA);
void get_temp(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA);
void get_humi(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA);
uint8_t take_slave_address(UART_HandleTypeDef *huart);

#endif /* INC_XY_MD02_H_ */
