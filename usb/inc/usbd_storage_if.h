/**
  ******************************************************************************
  * @file           : usbd_storage_if.h
  * @version        : v1.0_Cube
  * @brief          : Header for usbd_storage_if.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_STORAGE_IF_H__
#define __USBD_STORAGE_IF_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_msc.h"
#include "sd.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
/** STORAGE Interface callback. */
extern USBD_StorageTypeDef USBD_Storage_Interface_fops_FS;

//extern SD_HandleTypeDef hsd2;
//extern HAL_SD_CardInfoTypeDef SDCardInfo;

#ifdef __cplusplus
}
#endif

#endif /* __USBD_STORAGE_IF_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
