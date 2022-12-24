#ifndef VECTORS_H
#define VECTORS_H

    #include "common.h"

    #ifdef __ASSEMBLER__

        .global Default_Handler
        .global Vector_Table

        .weak      NMI_Handler
        .thumb_set NMI_Handler,Default_Handler

        .weak      HardFault_Handler
        .thumb_set HardFault_Handler,Default_Handler

        .weak      MemManage_Handler
        .thumb_set MemManage_Handler,Default_Handler

        .weak      BusFault_Handler
        .thumb_set BusFault_Handler,Default_Handler

        .weak      UsageFault_Handler
        .thumb_set UsageFault_Handler,Default_Handler

        .weak      SVC_Handler
        .thumb_set SVC_Handler,Default_Handler

        .weak      DebugMon_Handler
        .thumb_set DebugMon_Handler,Default_Handler

        .weak      PendSV_Handler
        .thumb_set PendSV_Handler,Default_Handler

        .weak      SysTick_Handler
        .thumb_set SysTick_Handler,Default_Handler

        .weak      WWDG_IRQHandler
        .thumb_set WWDG_IRQHandler,Default_Handler

        .weak      PVD_IRQHandler
        .thumb_set PVD_IRQHandler,Default_Handler

        .weak      TAMP_STAMP_IRQHandler
        .thumb_set TAMP_STAMP_IRQHandler,Default_Handler

        .weak      RTC_WKUP_IRQHandler
        .thumb_set RTC_WKUP_IRQHandler,Default_Handler

        .weak      FLASH_IRQHandler
        .thumb_set FLASH_IRQHandler,Default_Handler

        .weak      RCC_IRQHandler
        .thumb_set RCC_IRQHandler,Default_Handler

        .weak      EXTI0_IRQHandler
        .thumb_set EXTI0_IRQHandler,Default_Handler

        .weak      EXTI1_IRQHandler
        .thumb_set EXTI1_IRQHandler,Default_Handler

        .weak      EXTI2_IRQHandler
        .thumb_set EXTI2_IRQHandler,Default_Handler

        .weak      EXTI3_IRQHandler
        .thumb_set EXTI3_IRQHandler,Default_Handler

        .weak      EXTI4_IRQHandler
        .thumb_set EXTI4_IRQHandler,Default_Handler

        .weak      DMA1_Stream0_IRQHandler
        .thumb_set DMA1_Stream0_IRQHandler,Default_Handler

        .weak      DMA1_Stream1_IRQHandler
        .thumb_set DMA1_Stream1_IRQHandler,Default_Handler

        .weak      DMA1_Stream2_IRQHandler
        .thumb_set DMA1_Stream2_IRQHandler,Default_Handler

        .weak      DMA1_Stream3_IRQHandler
        .thumb_set DMA1_Stream3_IRQHandler,Default_Handler

        .weak      DMA1_Stream4_IRQHandler
        .thumb_set DMA1_Stream4_IRQHandler,Default_Handler

        .weak      DMA1_Stream5_IRQHandler
        .thumb_set DMA1_Stream5_IRQHandler,Default_Handler

        .weak      DMA1_Stream6_IRQHandler
        .thumb_set DMA1_Stream6_IRQHandler,Default_Handler

        .weak      ADC_IRQHandler
        .thumb_set ADC_IRQHandler,Default_Handler

        .weak      EXTI9_5_IRQHandler
        .thumb_set EXTI9_5_IRQHandler,Default_Handler

        .weak      TIM1_BRK_TIM9_IRQHandler
        .thumb_set TIM1_BRK_TIM9_IRQHandler,Default_Handler

        .weak      TIM1_UP_TIM10_IRQHandler
        .thumb_set TIM1_UP_TIM10_IRQHandler,Default_Handler

        .weak      TIM1_TRG_COM_TIM11_IRQHandler
        .thumb_set TIM1_TRG_COM_TIM11_IRQHandler,Default_Handler

        .weak      TIM1_CC_IRQHandler
        .thumb_set TIM1_CC_IRQHandler,Default_Handler

        .weak      TIM2_IRQHandler
        .thumb_set TIM2_IRQHandler,Default_Handler

        .weak      TIM3_IRQHandler
        .thumb_set TIM3_IRQHandler,Default_Handler

        .weak      TIM4_IRQHandler
        .thumb_set TIM4_IRQHandler,Default_Handler

        .weak      I2C1_EV_IRQHandler
        .thumb_set I2C1_EV_IRQHandler,Default_Handler

        .weak      I2C1_ER_IRQHandler
        .thumb_set I2C1_ER_IRQHandler,Default_Handler

        .weak      I2C2_EV_IRQHandler
        .thumb_set I2C2_EV_IRQHandler,Default_Handler

        .weak      I2C2_ER_IRQHandler
        .thumb_set I2C2_ER_IRQHandler,Default_Handler

        .weak      SPI1_IRQHandler
        .thumb_set SPI1_IRQHandler,Default_Handler

        .weak      SPI2_IRQHandler
        .thumb_set SPI2_IRQHandler,Default_Handler

        .weak      USART1_IRQHandler
        .thumb_set USART1_IRQHandler,Default_Handler

        .weak      USART2_IRQHandler
        .thumb_set USART2_IRQHandler,Default_Handler

        .weak      EXTI15_10_IRQHandler
        .thumb_set EXTI15_10_IRQHandler,Default_Handler

        .weak      RTC_Alarm_IRQHandler
        .thumb_set RTC_Alarm_IRQHandler,Default_Handler

        .weak      OTG_FS_WKUP_IRQHandler
        .thumb_set OTG_FS_WKUP_IRQHandler,Default_Handler

        .weak      DMA1_Stream7_IRQHandler
        .thumb_set DMA1_Stream7_IRQHandler,Default_Handler

        .weak      SDIO_IRQHandler
        .thumb_set SDIO_IRQHandler,Default_Handler

        .weak      TIM5_IRQHandler
        .thumb_set TIM5_IRQHandler,Default_Handler

        .weak      SPI3_IRQHandler
        .thumb_set SPI3_IRQHandler,Default_Handler

        .weak      DMA2_Stream0_IRQHandler
        .thumb_set DMA2_Stream0_IRQHandler,Default_Handler

        .weak      DMA2_Stream1_IRQHandler
        .thumb_set DMA2_Stream1_IRQHandler,Default_Handler

        .weak      DMA2_Stream2_IRQHandler
        .thumb_set DMA2_Stream2_IRQHandler,Default_Handler

        .weak      DMA2_Stream3_IRQHandler
        .thumb_set DMA2_Stream3_IRQHandler,Default_Handler

        .weak      DMA2_Stream4_IRQHandler
        .thumb_set DMA2_Stream4_IRQHandler,Default_Handler

        .weak      OTG_FS_IRQHandler
        .thumb_set OTG_FS_IRQHandler,Default_Handler

        .weak      DMA2_Stream5_IRQHandler
        .thumb_set DMA2_Stream5_IRQHandler,Default_Handler

        .weak      DMA2_Stream6_IRQHandler
        .thumb_set DMA2_Stream6_IRQHandler,Default_Handler

        .weak      DMA2_Stream7_IRQHandler
        .thumb_set DMA2_Stream7_IRQHandler,Default_Handler

        .weak      USART6_IRQHandler
        .thumb_set USART6_IRQHandler,Default_Handler

        .weak      I2C3_EV_IRQHandler
        .thumb_set I2C3_EV_IRQHandler,Default_Handler

        .weak      I2C3_ER_IRQHandler
        .thumb_set I2C3_ER_IRQHandler,Default_Handler

        .weak      FPU_IRQHandler
        .thumb_set FPU_IRQHandler,Default_Handler

        .weak      SPI4_IRQHandler
        .thumb_set SPI4_IRQHandler,Default_Handler

        .weak      SPI5_IRQHandler
        .thumb_set SPI5_IRQHandler,Default_Handler

    #else

        void Default_Handler(void);

        void NMI_Handler 					(void) __attribute__ ((weak, alias("Default_Handler")));
        void HardFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void MemManage_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void BusFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void UsageFault_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void SVC_Handler 					(void) __attribute__ ((weak, alias("Default_Handler")));
        void DebugMon_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void PendSV_Handler   				(void) __attribute__ ((weak, alias("Default_Handler")));
        void SysTick_Handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
        void WWDG_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void PVD_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void TAMP_STAMP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void RTC_WKUP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void RCC_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void EXTI0_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void EXTI1_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void EXTI2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void EXTI3_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void EXTI4_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA1_Stream0_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA1_Stream1_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA1_Stream2_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA1_Stream3_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA1_Stream4_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA1_Stream5_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA1_Stream6_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
        void ADC_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void CAN1_TX_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void CAN1_RX0_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void CAN1_RX1_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void CAN1_SCE_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void EXTI9_5_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM1_BRK_TIM9_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM1_UP_TIM10_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM1_TRG_COM_TIM11_IRQHandler 	(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM1_CC_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM3_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM4_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void I2C1_EV_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void I2C1_ER_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void I2C2_EV_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void I2C2_ER_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
        void SPI1_IRQHandler  				(void) __attribute__ ((weak, alias("Default_Handler")));
        void SPI2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
        void USART1_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));
        void USART2_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));
        void USART3_IRQHandler   			(void) __attribute__ ((weak, alias("Default_Handler")));
        void EXTI15_10_IRQHandler   		(void) __attribute__ ((weak, alias("Default_Handler")));
        void RTC_Alarm_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));
        void OTG_FS_WKUP_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM8_BRK_TIM12_IRQHandler   	(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM8_UP_TIM13_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM8_TRG_COM_TIM14_IRQHandler 	(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM8_CC_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA1_Stream7_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
        void FSMC_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
        void SDIO_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM5_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
        void SPI3_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
        void UART4_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
        void UART5_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM6_DAC_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
        void TIM7_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA2_Stream0_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA2_Stream1_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA2_Stream2_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA2_Stream3_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA2_Stream4_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
        void ETH_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler")));
        void ETH_WKUP_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
        void CAN2_TX_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
        void CAN2_RX0_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
        void CAN2_RX1_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
        void CAN2_SCE_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
        void OTG_FS_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA2_Stream5_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA2_Stream6_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
        void DMA2_Stream7_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
        void USART6_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
        void I2C3_EV_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
        void I2C3_ER_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
        void OTG_HS_EP1_OUT_IRQHandler   	(void) __attribute__ ((weak, alias("Default_Handler")));
        void OTG_HS_EP1_IN_IRQHandler    	(void) __attribute__ ((weak, alias("Default_Handler")));
        void OTG_HS_WKUP_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
        void OTG_HS_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
        void DCMI_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
        void CRYP_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
        void HASH_RNG_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
        void FPU_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler")));

#endif

#endif //VECTORS_H
