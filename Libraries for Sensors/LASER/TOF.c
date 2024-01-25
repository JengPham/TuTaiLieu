/*
 * TOF.c
 *
 *  Created on: Nov 8, 2023
 *      Author: KarimPham
 */

/*******************************************************************************
 * Include
 ******************************************************************************/
#include "TOF.h"

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

/*Enable: 0 to disable, 1 to enable.*/
void EnDisable_OUTPUT(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint8_t enable) {
	uint8_t Downward[] = { 0x5A, 0x05, 0x07, enable, 0x00 };
	uint8_t Upward[5];
	uint8_t Head;
	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 4, HAL_MAX_DELAY);
			break;
		}
	}
	TOF_Luna->OUTPUT_EN = Upward[3];
}

void GET_VERSION(UART_HandleTypeDef *huart, uint8_t *version) {
	uint8_t Downward[] = { 0x5A, 0x04, 0x01, 0x00 };
	uint8_t Upward[7];
	uint8_t Head;
	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 6, HAL_MAX_DELAY);
			break;
		}
	}
	version[0] = Upward[5];
	version[1] = Upward[4];
	version[2] = Upward[3];
}

/*0: Success; 1: Fail*/
uint8_t SOFT_RESET(UART_HandleTypeDef *huart) {
	uint8_t Downward[] = { 0x5A, 0x04, 0x02, 0x00 };
	uint8_t Upward[5];
	uint8_t Head;
	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 4, HAL_MAX_DELAY);
			break;
		}
	}
	if (Upward[3] == 0)
		return 0;
	return 1;
}

/*
 * TF-Luna supports is 250Hz (output_frequency ≤ 250Hz), and it must be 500/n Hz (n
 * is an integer that in the range [2, 500])
 */
void OUTPUT_FREQUENCY(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint16_t freq) {
	uint8_t Downward[] = { 0x5A, 0x06, 0x03, (uint8_t) freq, (uint8_t) (freq
			>> 8), 0x00 };

	uint8_t Upward[6];
	uint8_t Head;

	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);

	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 5, HAL_MAX_DELAY);
			break;
		}
	}

	TOF_Luna->SAMPLE_FREQ = (Upward[4] << 8) | Upward[3];
}

void TRIGGER_MODE(UART_HandleTypeDef *huart) {
	uint8_t Downward[] = { 0x5A, 0x04, 0x04, 0x00 };
	uint8_t Upward[4];
	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
	HAL_UART_Receive(huart, Upward, sizeof(Upward), HAL_MAX_DELAY);
}

/*
 * 0x01 = 9-byte/cm
 * 0x02 = PIX
 * 0x06 = 9-byte/mm
 * 0x07 = 32-byte with timestamp
 * 0x08 = ID-0
 * 0x09 = 8-byte/cm
 */
void OUTPUT_FORMAT_SETTING(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint8_t format) {
	uint8_t Downward[] = { 0x5A, 0x05, 0x05, format, 0x00 };
	uint8_t Upward[5];
	uint8_t Head;
	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 4, HAL_MAX_DELAY);
			break;
		}
	}
	TOF_Luna->FORMAT = Upward[3];
}

/*
 * Only baud rate in [9600,921600] are supported
 */
void BAUDRATE_SETTING(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint32_t baudrate) {
	uint8_t Downward[] = { 0x5A, 0x08, 0x06, (uint8_t) baudrate,
			(uint8_t) (baudrate >> 8), (uint8_t) (baudrate >> 16),
			(uint8_t) (baudrate >> 24), 0x00 };

	uint8_t Upward[8];
	uint8_t Head;

	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);

	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 7, HAL_MAX_DELAY);
			break;
		}
	}

	TOF_Luna->BAUDRATE = (Upward[6] << 24) | (Upward[5] << 16)
			| (Upward[4] << 8) | Upward[3];
}

/*
 * Enable: 0 to disable, 1 to enable
 * Default: 0
 */
void ENABLE_CHECKSUM_COMPARISON(UART_HandleTypeDef *huart,
		TOF_LunaTypedef *TOF_Luna, uint8_t enable) {
	uint8_t Downward[] = { 0x5A, 0x05, 0x08, enable, 0x00 };
	uint8_t Upward[5];
	uint8_t Head;
	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);
	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 4, HAL_MAX_DELAY);
			break;
		}
	}
	TOF_Luna->CHECKSUM = Upward[3];
}

/*
 * I2C_SLAVE_ADDR: Range [0x08, 0x77]
 * Default: 0x10
 */
void I2C_SLAVE_MACHINE_ADDRESS_CONFIG(UART_HandleTypeDef *huart,
		TOF_LunaTypedef *TOF_Luna, uint8_t I2C_SLAVE_ADDR) {
	uint8_t Downward[] = { 0x5A, 0x05, 0x0B, I2C_SLAVE_ADDR, 0x00 };

	uint8_t Upward[5];
	uint8_t Head;

	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);

	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 4, HAL_MAX_DELAY);
			break;
		}
	}

	TOF_Luna->I2C_SLAVE_ADDR = Upward[3];
}

/*
 * Status: 0 for success, otherwise for errors
 */
uint8_t RESTORE_DEFAULT_SETTING(UART_HandleTypeDef *huart) {
	uint8_t Downward[] = { 0x5A, 0x04, 0x10, 0x00 };

	uint8_t Upward[5];
	uint8_t Head;

	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);

	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 4, HAL_MAX_DELAY);
			break;
		}
	}

	return Upward[3];
}

/*
 * Status: 0 for success, otherwise for errors
 */
uint8_t SAVE_CURRENT_SETTING(UART_HandleTypeDef *huart) {
	uint8_t Downward[] = { 0x5A, 0x04, 0x11, 0x00 };

	uint8_t Upward[5];
	uint8_t Head;

	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);

	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 4, HAL_MAX_DELAY);
			break;
		}
	}

	return Upward[3];
}

/*
 * Amp_Threshold: When Amp < Amp_Threshold * 10, then output Dummy_Dist instead of the result of calculation
 * Dummy_Dist: The output distance when Amp is too low.
 */
void AMP_THRESHOLD_SETTING(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint8_t AMP_THRESHOLD, uint16_t DUMMY_DIST) {
	uint8_t Downward[] = { 0x5A, 0x07, 0x22, AMP_THRESHOLD,
			(uint8_t) DUMMY_DIST, (uint8_t) (DUMMY_DIST >> 8), 0x00 };

	uint8_t Upward[7];
	uint8_t Head;

	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);

	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 6, HAL_MAX_DELAY);
			break;
		}
	}

	TOF_Luna->AMP_THRESHOLD = Upward[3];
	TOF_Luna->DUMMY_DIST = (Upward[5] << 8) | Upward[4];
}

void TIME_SYNC(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint32_t TIMESTAMP) {
	uint8_t Downward[] = { 0x5A, 0x08, 0x31, (uint8_t) TIMESTAMP,
			(uint8_t) (TIMESTAMP >> 8), (uint8_t) (TIMESTAMP >> 16),
			(uint8_t) (TIMESTAMP >> 24), 0x00 };

	uint8_t Upward[8];
	uint8_t Head;

	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);

	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 7, HAL_MAX_DELAY);
			break;
		}
	}

	TOF_Luna->TIMESTAMP = (Upward[6] << 24) | (Upward[5] << 16)
			| (Upward[4] << 8) | Upward[3];
}

/*
 * Sample_rate: Work frequency if Sample_rate is positive (0 to disable power saving
 * Default Sample_rate: 0
 */
void ENABLE_POWER_SAVING_MODE(UART_HandleTypeDef *huart,
		TOF_LunaTypedef *TOF_Luna, uint16_t SAMPLE_RATE) {
	uint8_t Downward[] = { 0x5A, 0x06, 0x35, (uint8_t) SAMPLE_RATE,
			(uint8_t) (SAMPLE_RATE >> 8), 0x00 };

	uint8_t Upward[6];
	uint8_t Head;

	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);

	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 5, HAL_MAX_DELAY);
			break;
		}
	}

	TOF_Luna->SAMPLE_RATE = (Upward[4] << 8) | Upward[3];
}

/*
 * Dist_min: minimum distance output in centimeters.
 * Dist_max: maximum distance output in centimeters.
 * Silence: Not output when the distance is out of range if silence = 1. Output limit when out of range if silence = 0
 * Default maximum and minimum distance output: [min, max] = [0cm, 800cm]
 * Default Silence: 0
 * Note: Any distance value lower than 20cm or greater than 800cm may be unreliable.
 */
void DISTANCE_LIMIT_SETTING(UART_HandleTypeDef *huart,
		TOF_LunaTypedef *TOF_Luna, uint16_t DIST_MIN, uint16_t DIST_MAX,
		uint8_t SILENCE) {
	uint8_t Downward[] = { 0x5A, 0x09, 0x3A, (uint8_t) DIST_MIN,
			(uint8_t) (DIST_MIN >> 8), (uint8_t) DIST_MAX, (uint8_t) (DIST_MAX
					>> 8), SILENCE, 0x00 };

	uint8_t Upward[9];
	uint8_t Head;

	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);

	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 8, HAL_MAX_DELAY);
			break;
		}
	}

	TOF_Luna->DIST_LIMIT.DIST_MIN = (Upward[4] << 8) | Upward[3];
	TOF_Luna->DIST_LIMIT.DIST_MAX = (Upward[6] << 8) | Upward[5];
	TOF_Luna->DIST_LIMIT.SILENCE = Upward[7];
}

/*
 * Mode: 0 (Normal output) , 1 (On-off mode with high level output when closer) , 2 (On-off mode with low level output
 * when closer)
 * Dist: critical dist value (the closer one) in centimeters.
 * Zone: Zone size in centimeters
 * Delay1: Delay time 1 in millisecond. Pin 6 switch level only if the distance detected is less than Dist and the situation last
 * for Delay1 long.
 * Delay2: Delay time 2 in millisecond. Pin 6 switch level only if the distance detected is more than Dist + Zone and the
 * situation last for Delay2 long.
 */
void EnDisable_OnOff_MODE(UART_HandleTypeDef *huart, TOF_LunaTypedef *TOF_Luna,
		uint8_t mode, uint16_t dist, uint16_t zone, uint16_t delay_01,
		uint16_t delay_02) {
	uint8_t Downward[] = { 0x5A, 0x0D, 0x3B, mode, (uint8_t) dist,
			(uint8_t) (dist >> 8), (uint8_t) zone, (uint8_t) (zone >> 8),
			(uint8_t) delay_01, (uint8_t) (delay_01 >> 8), (uint8_t) delay_02,
			(uint8_t) (delay_02 >> 8), 0x00 };

	uint8_t Upward[13];
	uint8_t Head;

	HAL_UART_Transmit(huart, Downward, sizeof(Downward), HAL_MAX_DELAY);

	while (1) {
		HAL_UART_Receive(huart, &Head, 1, HAL_MAX_DELAY);
		if (Head == 0x5A) {
			Upward[0] = Head;
			HAL_UART_Receive(huart, &Upward[1], 12, HAL_MAX_DELAY);
			break;
		}
	}

	TOF_Luna->On_Off_Mode.MODE = Upward[3];
	TOF_Luna->On_Off_Mode.DIST = (Upward[5] << 8) | Upward[4];
	TOF_Luna->On_Off_Mode.ZONE = (Upward[7] << 8) | Upward[6];
	TOF_Luna->On_Off_Mode.DELAY_1 = (Upward[9] << 8) | Upward[8];
	TOF_Luna->On_Off_Mode.DELAY_2 = (Upward[11] << 8) | Upward[10];
}
