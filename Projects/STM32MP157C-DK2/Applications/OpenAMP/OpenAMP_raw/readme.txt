/**
  @page OpenAMP_raw OpenAMP raw example

  @verbatim
  ******************************************************************************
  * @file    OpenAMP/OpenAMP_raw/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the OpenAMP raw Application.
  ******************************************************************************
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *
  ******************************************************************************
  @endverbatim

@par Application Description

How to use OpenAMP MW  to create an Inter-Processor Communication channel.

This project deals with CPU2 (Cortex-M4) firmware and requires Linux OS running on CPU1 (Cortex-A7)
OpenAMP MW uses the following HW resources
    * IPCC peripheral for event signal (mailbox) between CPU1(CA7) and CPU2(CM4)
    * MCUSRAM peripheral for buffer communications (virtio buffers) between CPU1(CA7) and CPU2(CM4)
            Reserved shared memeory region for this example: SHM_ADDR=0x10040000 and SHM_SIZE=128k.
            It is defined in platform_info.c file

In this example:
    - Remote Core (CM4) initializes OpenAMP MW which initializes IPCC peripheral rely on HAL IPCC driver
    and setups the rpmsg for inter processor communication
    - Remote Core (CM4) creates an rpmsg endpoint
    - Remote Core (CM4) waits for messages from Master Core (CA7)
    - When CM4 receives a message on the rpmsg endpoint, it sends the message back to CA7:
      - 99 "hello world!" messages are exchanged  between the CA7 and CM4
      - 1 final "goodbye!" message is sent from CM4 to CA7

    Notes:
    - It requires Linux console to run example.
    - CM4 logging is redirected in Shared memory in MCUSRAM and can be displayed in Linux console for verdict
      using following command:
          cat /sys/kernel/debug/remoteproc/remoteproc0/trace0
    - The rpmsg_client_sample linux kernel module shall be loaded before the CM4 firmware:
        - to build this kernel module, select the SAMPLE_RPMSG_CLIENT linux kernel option
        - this kernel module can be loaded with the "modprobe rpmsg_client_sample" command
        - as soon as the rpmsg is available, this linux kernel module sends an "hello world!"
          message. Whenever it receives an incoming message, it sends back another "hello world!" message

    Following command should be done in Linux console on CA7 to run the example :

    > modprobe rpmsg_client_sample
    > ./fw_cortex_m4.sh start
    > ./fw_cortex_m4.sh stop
    > rmmod rpmsg_client_sample

    As the messages sent from CM4 are also output to the CM4 logging, you shall see the "goodbye!" log
    on test success.

@note Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in HAL time base ISR.
      This implies that if HAL_Delay() is called from a peripheral ISR process, then
      the HAL time base interrupt must have higher priority (numerically lower) than
      the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the HAL time base interrupt priority you have to use HAL_NVIC_SetPriority()
      function.

@note The application needs to ensure that the HAL time base is always set to 1 millisecond
      to have correct HAL operation.


@par Directory contents
    - OpenAMP/OpenAMP_raw/Inc/main.h                             Main program header file
    - OpenAMP/OpenAMP_raw/Inc/mbox_ipcc.h                        mailbox_ipcc_if.c MiddleWare configuration header file
    - OpenAMP/OpenAMP_raw/Inc/openamp.h                          User OpenAMP init header file
    - OpenAMP/OpenAMP_raw/Inc/openamp_conf.h                     Configuration file for OpenAMP MW
    - OpenAMP/OpenAMP_raw/Inc/rsc_table.h                        Resource_table for OpenAMP header file
    - OpenAMP/OpenAMP_raw/Inc/stm32mp1xx_hal_conf.h         HAL Library Configuration file
    - OpenAMP/OpenAMP_raw/Inc/stm32mp1xx_it.h               Interrupt handlers header file
    - OpenAMP/OpenAMP_raw/Src/main.c                             Main program
    - OpenAMP/OpenAMP_raw/Src/mbox_ipcc.c                        mailbox_ipcc_if.c MiddleWare configuration
    - OpenAMP/OpenAMP_raw/Src/openamp.c                          User OpenAMP init
    - OpenAMP/OpenAMP_raw/Src/rsc_table.c                        Resource_table for OpenAMP
    - OpenAMP/OpenAMP_raw/Src/stm32mp1xx_it.c               Interrupt handlers
    - OpenAMP/OpenAMP_raw/Src/system_stm32mp1xx.c           STM32MP1xx system clock configuration file


@par Hardware and Software environment

  - This example runs on STM32MP157CACx devices.

  - This example has been tested with STM32MP157C-DK2 board and can be
    easily tailored to any other supported device and development board.

@par How to use it ?

In order to make the program work, you must do the following:
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
