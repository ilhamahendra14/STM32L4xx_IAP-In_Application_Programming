# STM32L4xx_IAP-In_Application_Programming

## Hardware
+ I added a push button to the PA15 pin.

  ![alt text](https://github.com/ilhamahendra14/STM32L4xx_IAP-In_Application_Programming/blob/28655e09a9d55c6dcfd32f77a9422e5a13f01a44/Images/Push_Button.png?raw=true)
+ I added a buzzer to the PA8 pin.

## Firmware
+ To enter bootloader mode press and hold the button and reset the STM32 board, if it successfully enters bootloader mode it will beep 1 time.
+ If the STM32 board is reset without pressing the button, the STM32 will jump to the application.
+ If App1 is not uploaded, STM32 will looping a continous beep (error indicator).

Important :
+ Don't activate the RTC in both firmware (Bootloader and App1), it makes RTC reset and ambiguous when initializing date time.

### BootLoader
+ Bootloader starts at 0x08000000 but I allocate only 64kB. Go to 'STM32L432KCUX_FLASH.ld' to edit.
  ```C
  /* Memories definition */
  MEMORY
  {
    RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 64K
    RAM2    (xrw)    : ORIGIN = 0x10000000,   LENGTH = 16K
    FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 64K
  }
  ```
+ Bootloader has a function to jump to application.
  ```C
  bootloaderInit();
  ```

  ```C
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
  ```
+ Bootloader allows a STM32 board to have more than 1 application/firmware.
    ```C
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
              if .... //give condition here
                  jumpToApp(APP1_START);
              else
                  jumpToApp(APP2_START);
          else
              errorBlink();
      }
  }
  ```
+ Bootloader allows feature (you can add in bootloader.c):
  - Receive/update new firmware via USB-FS, SD-Card, or other.
  - Remove app firmware
  - Read/access STM32 memory
  - etc

### App1
+ App1 actually like generally main firmware.
+ App1 starts at 0x08010000 but I allocate only 192kB. To edit go to 'STM32L432KCUX_FLASH.ld' and 'system_stm32l4xx.c'.

  STM32L432KCUX_FLASH.ld:
  ```C
  /* Memories definition */
  MEMORY
  {
    RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 64K
    RAM2    (xrw)    : ORIGIN = 0x10000000,   LENGTH = 16K
    FLASH    (rx)    : ORIGIN = 0x8010000,   LENGTH = 192K
  }
  ```
  system_stm32l4xx.c:
  ```C
  #if defined(VECT_TAB_SRAM)
  #define VECT_TAB_BASE_ADDRESS   SRAM1_BASE      /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x200. */
  #define VECT_TAB_OFFSET         0x00000000U     /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x200. */
  #else
  #define VECT_TAB_BASE_ADDRESS   FLASH_BASE      /*!< Vector Table base address field.
                                                     This value must be a multiple of 0x200. */
  #define VECT_TAB_OFFSET         0x00010000U     /*!< Vector Table base offset field.
                                                     This value must be a multiple of 0x200. */
  #endif /* VECT_TAB_SRAM */
  #endif /* USER_VECT_TAB_ADDRESS */
  ```
+ App1 can't run if bootloader firmware is not running in STM32, because by default STM32 will run from 0x08000000.
+ I gave an example of beeping 2 times with a delay 300mS, after 3 second it will beeping 2 times with a delay 100mS and goes into standby mode.
+ If you want to add more than 1 App, allocate flash start and flash size in 'STM32L432KCUX_FLASH.ld' and 'system_stm32l4xx.c'. Make sure the App's size, memory allocation, and addressing are correct
