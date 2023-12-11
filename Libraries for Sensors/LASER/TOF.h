/*
 * TOF.h
 *
 *  Created on: Nov 8, 2023
 *      Author: KarimPham
 */

#ifndef INC_TOF_H_
#define INC_TOF_H_

#include "main.h"
#include "stm32f1xx_hal.h"

typedef struct {
	uint8_t MODE;
	uint16_t DIST;
	uint16_t ZONE;
	uint16_t DELAY_1;
	uint16_t DELAY_2;
} ON_OFF_MODE;

typedef struct {
	uint16_t DIST_MIN;
	uint16_t DIST_MAX;
	uint8_t SILENCE;
} DISTANCE;

typedef struct {
	uint8_t OUTPUT_EN;
	uint16_t SAMPLE_FREQ;
	uint8_t FORMAT;
	uint32_t BAUDRATE;
	uint8_t CHECKSUM;
	uint8_t I2C_SLAVE_ADDR;
	uint8_t AMP_THRESHOLD;
	uint16_t DUMMY_DIST;
	uint32_t TIMESTAMP;
	uint16_t SAMPLE_RATE;
	DISTANCE DIST_LIMIT;
	ON_OFF_MODE On_Off_Mode;
} TOF_LunaTypedef;

uint8_t RESTORE_DEFAULT_SETTING(UART_HandleTypeDef *huart);
uint8_t SAVE_CURRENT_SETTING(UART_HandleTypeDef *huart);
uint8_t SOFT_RESET(UART_HandleTypeDef *huart);
void EnDisable_OUTPUT(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint8_t enable);
void GET_VERSION(UART_HandleTypeDef *huart, uint8_t *version);
void OUTPUT_FREQUENCY(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint16_t freq);
void TRIGGER_MODE(UART_HandleTypeDef *huart);
void OUTPUT_FORMAT_SETTING(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint8_t format);
void BAUDRATE_SETTING(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint32_t baudrate); /*Only baud rate in [9600,921600] are supported*/
void ENABLE_CHECKSUM_COMPARISON(UART_HandleTypeDef *huart,
		TOF_LunaTypedef *TOF_Luna, uint8_t enable);
void I2C_SLAVE_MACHINE_ADDRESS_CONFIG(UART_HandleTypeDef *huart,
		TOF_LunaTypedef *TOF_Luna, uint8_t I2C_SLAVE_ADDR);
void AMP_THRESHOLD_SETTING(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint8_t AMP_THRESHOLD, uint16_t DUMMY_DIST);
void TIME_SYNC(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint32_t TIMESTAMP);
void ENABLE_POWER_SAVING_MODE(UART_HandleTypeDef *huart,
		TOF_LunaTypedef *TOF_Luna, uint16_t SAMPLE_RATE);
void DISTANCE_LIMIT_SETTING(UART_HandleTypeDef *huart,
		TOF_LunaTypedef *TOF_Luna, uint16_t DIST_MIN, uint16_t DIST_MAX,
		uint8_t SILENCE);
void EnDisable_OnOff_MODE(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint8_t mode, uint16_t dist, uint16_t zone, uint16_t delay_01,
		uint16_t delay_02);
void Enable_low_sample_rate_mode(void);
void Read_config_by_id(void);

#endif /* INC_TOF_H_ */
