/**
  ******************************************************************************
  * @file    IAP/src/download.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    10/15/2010
  * @brief   This file provides the software which allows to download an image 
  *          to internal Flash.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/** @addtogroup IAP
  * @{
  */
/* Includes ------------------------------------------------------------------*/
#include "download.h"
#include "common.h"
#include "ymodem.h"

uint8_t tab_1024[1024] =
  {
    0
  };

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval None
  */
int8_t SerialDownload(void)
{
  uint8_t Number[10] = "";
  int32_t Size = 0;
  SerialPutString("\r\n\r\nWaiting for the file to be sent ... (press 'a' to abort)\r\n");
  Size = Ymodem_Receive(&tab_1024[0]);
  if (Size > 0)
  {
    SerialPutString("\r\nProgramming Completed Successfully!\r\n");
	SerialPutString("------------------------------------\r\n");
	SerialPutString("Name: ");
    SerialPutString(file_name);
    Int2Str(Number, Size);
    SerialPutString("\r\nSize: ");
    SerialPutString(Number);
    SerialPutString("Bytes.\r\n");
    SerialPutString("------------------------------------\r\n");
	return 0;
  }
  else if (Size == -1)
  {
    SerialPutString("\n\n\rThe image size is higher than the allowed space memory!\n\r");
	return -1;
  }
  else if (Size == -2)
  {
    SerialPutString("\n\n\rVerification failed!\n\r");
	return -2;
  }
  else if (Size == -3)
  {
    SerialPutString("\r\n\nAborted by user.\n\r");
	return -3;
  }
  else
  {
    SerialPutString("\n\rFailed to receive the file!\n\r");
	return -4;
  }
}

/**
  * @}
  */

/*******************(C)COPYRIGHT 2010 STMicroelectronics *****END OF FILE******/
