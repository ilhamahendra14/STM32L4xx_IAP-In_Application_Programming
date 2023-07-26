

#ifndef INC_BOOTLOADER_H_
#define INC_BOOTLOADER_H_

#define APP1_START (0x08010000)
#include "main.h"
#include <string.h>

typedef enum
{
    JumpMode,
	FlashMode
} BootloaderMode;

typedef void (application_t)(void);

typedef struct
{
    uint32_t		stack_addr;     // Stack Pointer
    application_t*	func_p;        // Program Counter
} JumpStruct;

void bootloaderInit();
void flashWord(uint64_t dataToFlash);
void flashTime(uint64_t dataToFlash);
void Read_Data(uint64_t StartPageAddress, uint64_t *RxBuf, uint16_t numberofwords);
void Convert_Str(void);
uint32_t readWord(uint32_t address);
void eraseMemory(void);
void jumpToApp(const uint32_t address);
void deinitEverything(void);
void errorBlink(void);

#endif /* INC_BOOTLOADER_H_ */
