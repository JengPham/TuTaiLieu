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

/**
  * @brief: Structure stores temperature and humidity data.
  */
typedef struct {
	float Temp;
	float Humi;
} Data_XY_MD20;

/*******************************************************************************
 * API
 ******************************************************************************/

/**
  * @brief: Send data from the microcontroller to the sensor via UART.
  * @param[out] huart: UART handle pointer.
  * @param[out] data: Pointer to the data array to be transmitted.
  * @reVal: none.
  */
void send_data(UART_HandleTypeDef *huart, const uint8_t *data);

/**
  * @brief: Read temperature and humidity data from the sensor.
  * @param[out]: UART handle pointer.
  * @param[in]: Pointer to the Data_XY_MD20 structure to store
  * temperature and humidity data.
  * @note: If an error occurs during the reading process,
  * temperature and humidity are set to -100.
  * @reVal: none.
  */
void get_temp_humi(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA);

/**
  * @brief: Read temperature data from the sensor.
  * @param[out]: UART handle pointer.
  * @param[in]: Pointer to the Data_XY_MD20 structure to store
  * temperature data.
  * @note: If an error occurs during the reading process,
  * temperature is set to -100.
  * @reVal: none.
  */
void get_temp(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA);

/**
  * @brief: Read humidity data from the sensor.
  * @param[out]: UART handle pointer.
  * @param[in]: Pointer to the Data_XY_MD20 structure to store
  * humidity data.
  * @note: If an error occurs during the reading process,
  * humidity is set to -100.
  * @reVal: none.
  */
void get_humi(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA);

/**
  * @brief: Retrieves the address of the slave device.
  * @param[out]: UART handle pointer.
  * @note: If there is an error it returns 0.
  * @reVal: The slave address.
  */
uint8_t take_slave_address(UART_HandleTypeDef *huart);


#endif /* INC_XY_MD02_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
