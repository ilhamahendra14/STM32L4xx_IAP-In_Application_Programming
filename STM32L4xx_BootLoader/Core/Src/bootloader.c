#include "bootloader.h"

void bootloaderInit(void) {
	BootloaderMode bootloaderMode;
	if (HAL_GPIO_ReadPin(BootStat_GPIO_Port, BootStat_Pin) == GPIO_PIN_RESET)
		bootloaderMode = FlashMode;
	else
		bootloaderMode = JumpMode;
	if (bootloaderMode == JumpMode) {
		uint8_t emptyCellCount = 0;
		for (uint8_t i = 0; i < 10; i++) {
			if (readWord(APP1_START + (i * 8)) == -1)
				emptyCellCount++;
		}
		if (emptyCellCount != 10)
			jumpToApp(APP1_START);
		else
			errorBlink();
	}

}

uint32_t readWord(uint32_t address){
	uint32_t read_data;
	read_data = *(uint32_t*)(address);
	return read_data;
}

void jumpToApp(const uint32_t address){
	const JumpStruct* vector_p = (JumpStruct*)address;
	deinitEverything();
    asm("msr msp, %0; bx %1;" : : "r"(vector_p->stack_addr), "r"(vector_p->func_p));
}

void deinitEverything(void){
	HAL_GPIO_DeInit(Buzzer_GPIO_Port, Buzzer_Pin);
	  __HAL_RCC_GPIOC_CLK_DISABLE();
	  __HAL_RCC_GPIOB_CLK_DISABLE();
	  __HAL_RCC_GPIOA_CLK_DISABLE();
	HAL_RCC_DeInit();
	HAL_DeInit();
	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;
}

void errorBlink(void){
	HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
	while(1){
		HAL_GPIO_TogglePin(Buzzer_GPIO_Port, Buzzer_Pin);
		HAL_Delay(100);
	}
}
