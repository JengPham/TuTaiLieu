/*
 * XY-MD02.c
 *
 *  Created on: Dec 12, 2023
 *  Author    : Phong Thanh-Pham
 *  Email     : Phong.PT.HUST@gmail.com
 *
 */

/*******************************************************************************
 * Include
 ******************************************************************************/
#include "XY-MD02.h"

/******************************************************************************
 * Data types
 *****************************************************************************/
static uint8_t RxDataSHT20[9];
static uint8_t TxData_Temp[8] =
		{ 0x01, 0x04, 0x00, 0x01, 0x00, 0x01, 0x60, 0x0A };
static uint8_t TxData_Humi[8] =
		{ 0x01, 0x04, 0x00, 0x02, 0x00, 0x01, 0x90, 0x0A };
static uint8_t TxData_Temp_Humi[8] = { 0x01, 0x04, 0x00, 0x01, 0x00, 0x02, 0x20,
		0x0B };
static uint8_t TxData_Div_Add[8] = { 0x01, 0x03, 0x01, 0x01, 0x00, 0x01, 0xD4,
		0x36 };
static uint8_t TxData_Modify_Add[8] = { 0x01, 0x06, 0x01, 0x01, 0x00, 0x08,
		0xD8, 0x30 };

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
  * @brief
  * @param  [in]
  * @param  [in]
  * @return
  */
void send_data(UART_HandleTypeDef *huart, uint8_t *data) {
	HAL_GPIO_WritePin(TX_EN_GPIO_Port, TX_EN_Pin, GPIO_PIN_SET); /*Pull the TX_EN pin (RE and DE Pins) High. This will put the module in the transmitter mode.*/
	HAL_UART_Transmit(huart, data, 8, 1000);
	HAL_GPIO_WritePin(TX_EN_GPIO_Port, TX_EN_Pin, GPIO_PIN_RESET);/*Pull the TX_EN pin LOW, so to put the module in the receive mode*/
}

/**
  * @brief
  * @param  [in]
  * @param  [in]
  * @return
  */
void get_temp_humi(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA) {
	HAL_GPIO_WritePin(TX_EN_GPIO_Port, TX_EN_Pin, GPIO_PIN_SET);
	HAL_UART_Transmit(huart, TxData_Temp_Humi, 8, 1000);
	HAL_GPIO_WritePin(TX_EN_GPIO_Port, TX_EN_Pin, GPIO_PIN_RESET);
	HAL_UART_Receive(huart, RxDataSHT20, 9, 1000);
	if (crc16(RxDataSHT20, 7) == (RxDataSHT20[8] << 8 | RxDataSHT20[7])) {
		DATA->Temp = (RxDataSHT20[3] << 8 | RxDataSHT20[4]) / 10.0;
		DATA->Humi = (RxDataSHT20[5] << 8 | RxDataSHT20[6]) / 10.0;
	} else {
		DATA->Temp = -100;
		DATA->Humi = -100;
	}
}

/**
  * @brief
  * @param  [in]
  * @param  [in]
  * @return
  */
void get_temp(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA) {
	HAL_GPIO_WritePin(TX_EN_GPIO_Port, TX_EN_Pin, GPIO_PIN_SET);
	HAL_UART_Transmit(huart, TxData_Temp, 8, 1000);
	HAL_GPIO_WritePin(TX_EN_GPIO_Port, TX_EN_Pin, GPIO_PIN_RESET);
	HAL_UART_Receive(huart, RxDataSHT20, 7, 1000);
	if (crc16(RxDataSHT20, 5) == (RxDataSHT20[6] << 8 | RxDataSHT20[5])) {
		DATA->Temp = (RxDataSHT20[3] << 8 | RxDataSHT20[4]) / 10.0;
	} else {
		DATA->Temp = -100;
	}
}

/**
  * @brief
  * @param  [in]
  * @param  [in]
  * @return
  */
void get_humi(UART_HandleTypeDef *huart, Data_XY_MD20 *DATA) {
	HAL_GPIO_WritePin(TX_EN_GPIO_Port, TX_EN_Pin, GPIO_PIN_SET);
	HAL_UART_Transmit(huart, TxData_Humi, 8, 1000);
	HAL_GPIO_WritePin(TX_EN_GPIO_Port, TX_EN_Pin, GPIO_PIN_RESET);
	HAL_UART_Receive(huart, RxDataSHT20, 7, 1000);
	if (crc16(RxDataSHT20, 5) == (RxDataSHT20[6] << 8 | RxDataSHT20[5])) {
		DATA->Humi = (RxDataSHT20[3] << 8 | RxDataSHT20[4]) / 10.0;
	} else {
		DATA->Humi = -100;
	}
}

/**
  * @brief
  * @param  [in]
  * @param  [in]
  * @return
  */
uint8_t take_slave_address(UART_HandleTypeDef *huart) {
	uint8_t add;
	HAL_GPIO_WritePin(TX_EN_GPIO_Port, TX_EN_Pin, GPIO_PIN_SET);
	HAL_UART_Transmit(huart, TxData_Div_Add, 8, 1000);
	HAL_GPIO_WritePin(TX_EN_GPIO_Port, TX_EN_Pin, GPIO_PIN_RESET);
	HAL_UART_Receive(huart, RxDataSHT20, 7, 1000);
	if (crc16(RxDataSHT20, 5) == (RxDataSHT20[6] << 8 | RxDataSHT20[5])) {
		add = RxDataSHT20[3] << 8 | RxDataSHT20[4];
	} else {
		add = 0;
	}
	return add;
}
