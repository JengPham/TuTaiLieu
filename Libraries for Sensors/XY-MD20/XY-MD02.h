/*
 * XY-MD02.h
 *
 *  Created on: Dec 12, 2023
 *  Author    : Phong Thanh-Pham
 *  Email     : Phong.PT.HUST@gmail.com
 *
 */

/******************************************************************************
 * Multiple include protection
 *****************************************************************************/
#ifndef INC_XY_MD02_H_
#define INC_XY_MD02_H_

/*******************************************************************************
 * Include
 ******************************************************************************/
#include "modbus_crc.h"
#include "main.h"

/*******************************************************************************
 * Typedef
 ******************************************************************************/
typedef struct {
	float Temp;
	float Humi;
} Data_XY_MD20;

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
void send_data(UART_HandleTypeDef *huart, uint8_t *data);
void get_temp_humi(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA);
void get_temp(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA);
void get_humi(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA);
uint8_t take_slave_address(UART_HandleTypeDef *huart);

/*******************************************************************************
 * END
 ******************************************************************************/
#endif /* INC_XY_MD02_H_ */
