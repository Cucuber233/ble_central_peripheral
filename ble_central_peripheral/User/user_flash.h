/**===========================================================================
  Copyright (C) ALMSound Technologies Co., Ltd. All rights reserved.

  @file     user_flash.h
  @brief    ���ļ����û�flash����
  @author   wude
  @version  r0.1
  @date     2021/11/10
  @license ALMSound (ALM)
----------------------------------------------------------------------------
  Remark: (��ע����)
----------------------------------------------------------------------------
                                History
----------------------------------------------------------------------------
  <Date>     | <Version> | <Author>       | <Description>
-------------|-----------|----------------|---------------------------------
  2021/11/10 | r0.1      | wude           | ����
-------------|-----------|----------------|---------------------------------
             |           |                |
-------------|-----------|----------------|---------------------------------
             |           |                |
-------------|-----------|----------------|---------------------------------
             |           |                |
============================================================================*/

#ifndef _USER_FLASH_H_
#define _USER_FLASH_H_

/*********************************************************************
 * INCLUDES
 */
#include "app.h"

#include "user_config.h"

/*********************************************************************
 * DEFINITIONS
 */


#define ADV_INTERVAL_UNIT                   		100             // �㲥���Ĭ�ϵ�λ 100ms

#define BEACON_STATUS_SET							0x01			// �ű�״ֵ̬��1����
#define BEACON_STATUS_CLEAR							0x02			// �ű�״ֵ̬��0����
#define BEACON_ADV_STATUS							0x01			// �ű�㲥״̬
#define BEACON_SCAN_STATUS							0x02			// �ű�ɨ��״̬
#define BEACON_LOW_BATTERY							0x04			// �ű�͵����澯

#define ADV_INTERVAL_M_UINT                         10              // �㲥���ʱ�䱶�ʵ�λ(*10ms)

#define SEND_ADDR_ADV

#define USER_FALSH_SIZE     (sizeof(TotalConfigData_t))
	
#define NOT_ERASE				1			// δ��
#define YES_ERASE				0			// �Ѳ�

/*********************************************************************
 * TYPEDEFS
 */
 /* ��ʼ������ */
typedef struct
{
    uint8_t length;												// ����
    uint8_t name[11];											// �豸����	
} BleNameData_t;

typedef struct
{
    uint8_t length;							        // ����
    uint8_t advType;                                // ���˵Ĺ㲥����,0-�㲥���ݣ�1-ɨ����Ӧ��2-�㲥+ɨ����Ӧ
    uint8_t name[10];								// ��������	
} BleNameFilter_t;

typedef struct
{
    uint8_t length;							        // ����
    uint8_t advType;                                // ���˵Ĺ㲥����,0-�㲥���ݣ�1-ɨ����Ӧ��2-�㲥+ɨ����Ӧ
    uint8_t addr[6];								// ������ַ	
} BleMacAddrData_t;

typedef struct 
{
	BleNameFilter_t deviceNameFilter[FILTER_DEV_NUM_MAX];	    // �豸����������
    BleMacAddrData_t deviceAddrFilter[FILTER_DEV_NUM_MAX];      // �豸��ַ��������
} FilterDeviceData_t;

typedef struct
{
    uint8_t length;
	uint8_t data[31];
} ConfigurationAdvData_t;										// ���ù㲥����

typedef struct
{
    uint16_t advInterval;                                        // �㲥���
    uint8_t txPower;                                            // ���书��
} AdvIntervalData_t;	

// �㲥����
typedef struct 
{
    AdvIntervalData_t advIntervalData;
	ConfigurationAdvData_t configurationAdvData;
} AdvParamsData_t;

// ɨ�����
typedef struct 
{
    uint8_t scanEnble;
    uint8_t scanInterval;
    uint16_t scanWindows;
} ScanParamsData_t;
//--------------------------------------------------------------------------------------------
typedef struct
{
    /* ��������״̬��0 ����������δ�����������ű�;δ������;
     *               1 �����У������÷����������ű�,�ȴ�����;δ������;
     *               2 �����У��յ�Ӧ��,��ʼ����Эͬ����;δ������;
     *               3 �����У������÷�����Эͬ�����ű�;��������;
     *               4 ������ */
    uint8_t networkConfigState;
    uint8_t statusType;                                 				// ״̬���ͣ�0x01����δ����;0x02��������
    uint8_t networkVerificationCode[6];								    // ������֤��
	/* δ����ʱΪ��������;
     * ������ʱΪѡ�ֽ�ƫ�� + ���ֽ�λѡ�� + appId */
    uint8_t networkParameter[4];
	uint8_t domainAddress[6];											// �������ַ
	uint8_t groupNumber;												// Ⱥ������
	uint8_t hostMac[6];												    // ������ַ
	uint8_t expansionParameter1;
	uint8_t expansionParameter2;
	uint8_t expansionParameter3;
} JoinNetworkData_t;

// ң����������Ϣ
typedef struct
{
	uint8_t networkConfigState;									// ����״̬ 0-δ���� 1-������
	uint8_t hostMac[6];											// Mac��ַ
	uint8_t touchPermissionCode[6];								// ����Ȩ����
	uint8_t groupNumber;											// ����
	uint8_t byteOffset;											// λѡ�ֽ�ƫ��
	uint8_t bitOffset;											// ���ֽ�λѡ��
} TelecontrolData_t;


typedef struct 
{
	uint8_t red;													// RGBW-red��ɫ
	uint8_t green;												// RGBW-green��ɫ
	uint8_t blue;													// RGBW-blue��ɫ
	uint8_t white;												// RGBW-white��ɫ
} RGBWData_t;

//typedef struct 
//{
////----����ɫ����ɫ����ɫ����ɫ��Ƶ��, ����ʱ�䡿-----
//	uint8_t red;
//	uint8_t green;
//	uint8_t blue;
//	uint8_t white;
//	uint16_t frequency;               //Ƶ��
//	uint16_t time_of_duration;        //����ʱ��
//} CofingData;

typedef struct 
{
	RGBWData_t sceneMode[8];
	uint8_t DimmingDataCofing[16][5];                           //�����������õƹ�����
	uint8_t dimming_time_of_duration;                           //�����������õƹ���˸����ʱ��
	uint8_t dimmingDataCofingFlag;                              //����״̬
} DimmingModeData_t;


typedef struct
{
	JoinNetworkData_t joinNetworkData;							// ��������
	TelecontrolData_t telecontrolData;							// ң������
	DimmingModeData_t dimmingModeData;							// ��������
} InitData_t;

typedef struct
{
    InitData_t initData;
//	BleNameData_t bleNameData;
//	FilterDeviceData_t filterData;						// �����豸����
//    AdvParamsData_t advParamsData;
//    ScanParamsData_t scanParam;
} TotalConfigData_t;
//---------------------------------------------------------------------------------------------

// �㲥���ͱ�־
typedef struct 
{
	bool tAdvTypeFlag;								// ������ʱ���Ĺ㲥���ͱ�־
    bool bLinkFlag;                                 // �������ӱ�־
} AdvTypeFlag_t;

/*********************************************************************
 * GLOBAL VARIABLES
 */
extern TotalConfigData_t g_totalConfigData;
extern uint8_t g_flashEraseStatus;

/*********************************************************************
 * API FUNCTIONS
 */
void LoadTotalConfigDataFromFlash(void);
void LoadBleAddress(uint8_t *address);
void LoadJoinNetworkData(void);
//void LoadBleNameData(void);
//void LoadFilterDeviceData(void);
void LoadAdvParamsData(void);
void LoadScanParamsData(void);

//void Flash_BleNameDataWrite(const BleNameData_t *bleNameData);
//void Flash_BleNameDataRead(BleNameData_t *bleNameData);
//void Flash_AdvParamDataWrite(const AdvParamsData_t *advParam);
//void Flash_AdvParamDataRead(AdvParamsData_t *advParam);
//void Flash_ScanParamDataWrite(const ScanParamsData_t *scanParam);
//void Flash_ScanParamDataRead(ScanParamsData_t *scanParam);
void Flash_FilterDataWrite(const FilterDeviceData_t *filterData);
void Flash_FilterDataRead(FilterDeviceData_t *filterData);

void Flash_all_erase(void);

void saveTotalConfigDataInFlash(void);

#endif /* _USER_FLASH_H_ */
