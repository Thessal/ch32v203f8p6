/********************************** (C) COPYRIGHT *******************************
 * File Name          : ota.h
 * Author             : WCH
 * Version            : V1.10
 * Date               : 2018/12/14
 * Description        : oad������ö���
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef __OTA_H
#define __OTA_H

/* ------------------------------------------------------------------------------------------------
 *                                             OTA FLASH
 * ------------------------------------------------------------------------------------------------
 */

/* �����û�code���ֳ�3�飬16K��216K��216K���ֱ����imageIAP ��imageA���û�����������imageB�����ݴ���������imageIAP */

/* FLASH���� */
#define FLASH_PAGE_SIZE        256
#define FLASH_BLOCK_SIZE       4096
#define IMAGE_SIZE             216 * 1024

/* imageIAP���� */
#define IMAGE_IAP_FLAG         0x03
#define IMAGE_IAP_START_ADD    0x08000000
#define IMAGE_IAP_SIZE         16 * 1024

/* imageA���� */
#define IMAGE_A_FLAG           0x01
#define IMAGE_A_START_ADD      (IMAGE_IAP_START_ADD + IMAGE_IAP_SIZE)
#define IMAGE_A_SIZE           IMAGE_SIZE

/* imageB���� */
#define IMAGE_B_FLAG           0x02
#define IMAGE_B_START_ADD      (IMAGE_A_START_ADD + IMAGE_SIZE)
#define IMAGE_B_SIZE           IMAGE_SIZE

/* IAP���� */
/* ����ΪIAP��������� */
#define CMD_IAP_PROM           0x80               // IAP�������
#define CMD_IAP_ERASE          0x81               // IAP��������
#define CMD_IAP_VERIFY         0x82               // IAPУ������
#define CMD_IAP_END            0x83               // IAP������־
#define CMD_IAP_INFO           0x84               // IAP��ȡ�豸��Ϣ

/* ����֡���ȶ��� */
#define IAP_LEN                247

/* �����DataFlash��ַ������ռ��������λ�� */
#define OTA_DATAFLASH_ADD      0x08077000

/* �����DataFlash���OTA��Ϣ */
typedef struct
{
    unsigned char ImageFlag; //��¼�ĵ�ǰ��image��־
    unsigned char flag[3];
} OTADataFlashInfo_t;

/* OTA IAPͨѶЭ�鶨�� */
/* ��ַʹ��4��ƫ�� */
typedef union
{
    struct
    {
        unsigned char cmd;          /* ������ 0x81 */
        unsigned char len;          /* �������ݳ��� */
        unsigned char addr[2];      /* ������ַ */
        unsigned char block_num[2]; /* �������� */

    } erase; /* �������� */
    struct
    {
        unsigned char cmd;       /* ������ 0x83 */
        unsigned char len;       /* �������ݳ��� */
        unsigned char status[2]; /* ���ֽ�״̬������ */
    } end;                       /* �������� */
    struct
    {
        unsigned char cmd;              /* ������ 0x82 */
        unsigned char len;              /* �������ݳ��� */
        unsigned char addr[2];          /* У���ַ */
        unsigned char buf[IAP_LEN - 4]; /* У������ */
    } verify;                           /* У������ */
    struct
    {
        unsigned char cmd;              /* ������ 0x80 */
        unsigned char len;              /* �������ݳ��� */
        unsigned char addr[2];          /* ��ַ */
        unsigned char buf[IAP_LEN - 4]; /* �������� */
    } program;                          /* ������� */
    struct
    {
        unsigned char cmd;              /* ������ 0x84 */
        unsigned char len;              /* �������ݳ��� */
        unsigned char buf[IAP_LEN - 2]; /* �������� */
    } info;                             /* ������� */
    struct
    {
        unsigned char buf[IAP_LEN]; /* �������ݰ�*/
    } other;
} OTA_IAP_CMD_t;

/* ��¼��ǰ��Image */
extern unsigned char CurrImageFlag;

#endif