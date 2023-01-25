/*********************************************************************
 * INCLUDES
 */
#include <string.h>
#include "nvds_in_ram.h"

#include "board_flash.h"
#include "user_config.h"
#include "user_advertising.h"
#include "user_flash.h"
#include "user_timer.h"
#include "user_dimming.h"

void saveTotalConfigDataInFlash(void);

/*********************************************************************
 * DEFINITIONS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */
TotalConfigData_t g_totalConfigData = {0};
uint8_t g_flashEraseStatus = YES_ERASE;				// flash������־��0-�Ѳ� 1-δ��

/*********************************************************************
 * LOCAL VARIABLES
 */


/*********************************************************************
 * PUBLIC FUNCTIONS
 */
/*********************************************************************
 * LOCAL FUNCTIONS
 */
/**
 @brief ����ȫ������������Flash��
 @param ��
 @return ��
*/
void saveTotalConfigDataInFlash(void)
{
	Flash_UserWrite((uint8_t *)&g_totalConfigData, USER_FALSH_SIZE);
}


/**
 @brief ��Flash�м���ȫ����������
 @param ��
 @return ��
*/
void LoadTotalConfigDataFromFlash(void)
{
	TotalConfigData_t totalConfigData = {0};
	
    Flash_UserRead((uint8_t *)&totalConfigData, USER_FALSH_SIZE);
    memcpy(&g_totalConfigData, &totalConfigData, USER_FALSH_SIZE);
	
    LoadJoinNetworkData();
//    LoadBleNameData();
//    LoadFilterDeviceData();
//    LoadAdvParamsData();
//    LoadScanParamsData();
    LoadBleAddress(g_deviceAddress);
	
	//�ƹ��������ݼ���
	if(g_totalConfigData.initData.dimmingModeData.dimmingDataCofingFlag == 1)
		memcpy(dimmingData, g_totalConfigData.initData.dimmingModeData.DimmingDataCofing, USER_FALSH_SIZE);
	
//	for(uint8_t i =0;i < 6; ++i)
//	{
//		LOG_RAW("%02x ",g_totalConfigData.initData.joinNetworkData.domainAddress[i]);
//	}
//	for(uint8_t i =0;i < 6; ++i)
//	{
//		LOG_RAW("%02x ",g_totalConfigData.initData.joinNetworkData.networkVerificationCode[i]);
//	}
}

/**
 @brief ���ر���������ַ
 @param address -[out] ��ַ
 @return ��
*/
void LoadBleAddress(uint8_t *address)
{
    uint8_t addr[6] ={0};
    uint8_t addrLen = NVDS_LEN_BD_ADDRESS;             
    if(nvds_get(NVDS_TAG_BD_ADDRESS, &addrLen, addr) == NVDS_OK)       // ��ȡ������ַ
    {
        for(uint8_t i=0; i < addrLen; i++)
        {
            address[i] = addr[5-i];
        }
        
#if DEBUG
        LOG_RAW("ADDR:");
        for(uint8_t i = 0; i < addrLen; i++)
        {
            LOG_RAW("-%02X", address[i]);
        }
        LOG_RAW("\n");
#endif
    }
}

/**
 @brief �����������ݣ������ȵ���LoadTotalConfigDataFromFlash��
 @param ��
 @return ��
*/
void LoadJoinNetworkData(void)
{
	if(g_totalConfigData.initData.joinNetworkData.networkConfigState != 0 && g_totalConfigData.initData.joinNetworkData.networkConfigState != 1 &&
		g_totalConfigData.initData.joinNetworkData.networkConfigState != 2 && g_totalConfigData.initData.joinNetworkData.networkConfigState != 3 &&
		g_totalConfigData.initData.joinNetworkData.networkConfigState != 4)
	{
		memset(&g_totalConfigData.initData, 0, sizeof(g_totalConfigData.initData));
	}
	
}

///**
// @brief �����豸�����ݣ������ȵ���LoadTotalConfigDataFromFlash��
// @param ��
// @return ��
//*/
//void LoadBleNameData(void)
//{
//    BleNameData_t bleNameData;
//    Flash_BleNameDataRead(&bleNameData);
//	if(bleNameData.length != 0 && bleNameData.length != 0xFF)
//	{
//		SetBleName(bleNameData.name, bleNameData.length);
//		UpdateAdvData();
//	}	
//}

///**
// @brief ���ع����豸���ݣ������ȵ���LoadTotalConfigDataFromFlash��
// @param ��
// @return ��
//*/
//void LoadFilterDeviceData(void)
//{
//	if(g_totalConfigData.filterData.deviceNameFilter[0].length == 0xFF ||
//        g_totalConfigData.filterData.deviceNameFilter[0].length == 0x00)
//	{
////        uint8_t name[4] = {'A','L','M','5'};
//		memset(&g_totalConfigData.filterData.deviceNameFilter[0], 0, sizeof(BleNameData_t));
////        g_totalConfigData.filterData.deviceNameFilter[0].advType =2;
////        g_totalConfigData.filterData.deviceNameFilter[0].length = 3;
////        memcpy(&g_totalConfigData.filterData.deviceNameFilter[0].name,name,3);
//	}
//	
//	if(g_totalConfigData.filterData.deviceNameFilter[1].length == 0xFF ||
//        g_totalConfigData.filterData.deviceNameFilter[1].length == 0x00)
//	{
//		memset(&g_totalConfigData.filterData.deviceNameFilter[1], 0, sizeof(BleNameData_t));
//        
//	}
//	
//	if(g_totalConfigData.filterData.deviceNameFilter[2].length == 0xFF ||
//        g_totalConfigData.filterData.deviceNameFilter[2].length == 0x00)
//	{
//		memset(&g_totalConfigData.filterData.deviceNameFilter[2], 0, sizeof(BleNameData_t));
//		
//	}
//	
//	if(g_totalConfigData.filterData.deviceNameFilter[3].length == 0xFF ||
//        g_totalConfigData.filterData.deviceNameFilter[3].length == 0x00)
//	{
//		memset(&g_totalConfigData.filterData.deviceNameFilter[3], 0, sizeof(BleNameData_t));
//		
//	}	
//	
//	if(g_totalConfigData.filterData.deviceAddrFilter[0].length == 0xFF ||
//        g_totalConfigData.filterData.deviceAddrFilter[0].length == 0x00)
//	{
//		memset(&g_totalConfigData.filterData.deviceAddrFilter[0], 0, sizeof(BleMacAddrData_t));
//        
//	}
//	
//	if(g_totalConfigData.filterData.deviceAddrFilter[1].length == 0xFF || 
//        g_totalConfigData.filterData.deviceAddrFilter[1].length == 0x00)
//	{
//		memset(&g_totalConfigData.filterData.deviceAddrFilter[1], 0, sizeof(BleMacAddrData_t));
//	}
//	
//	if(g_totalConfigData.filterData.deviceAddrFilter[2].length == 0xFF || 
//        g_totalConfigData.filterData.deviceAddrFilter[2].length == 0x00)
//	{
//		memset(&g_totalConfigData.filterData.deviceAddrFilter[2], 0, sizeof(BleMacAddrData_t));
//	}
//	
//	if(g_totalConfigData.filterData.deviceAddrFilter[3].length == 0xFF || 
//        g_totalConfigData.filterData.deviceAddrFilter[3].length == 0x00)
//	{
//		memset(&g_totalConfigData.filterData.deviceAddrFilter[3], 0, sizeof(BleMacAddrData_t));
//	}
//}

/**
 @brief ���ع㲥�������ݣ������ȵ���LoadTotalConfigDataFromFlash��
 @param ��
 @return ��
*/
void LoadAdvParamsData(void)
{
    AdvParamsData_t advParam;
//    Flash_AdvParamDataRead(&advParam);
    
    if(advParam.advIntervalData.advInterval == 0 || advParam.advIntervalData.advInterval == 0xFFFF)
    {
        
    }
    else
    {
        SetAdvInterval(advParam.advIntervalData.advInterval);
        UpdateAdvData();
    }
    
    if(advParam.configurationAdvData.length != 0 && advParam.configurationAdvData.length != 0xFF)
    {
        SetConfigurationAdvData(advParam.configurationAdvData.data, advParam.configurationAdvData.length);
        UpdateAdvData();
    }
}

/**
 @brief ����ɨ���������
 @param ��
 @return ��
*/
void LoadScanParamsData(void)
{
    ScanParamsData_t scanParam;
//    Flash_ScanParamDataRead(&scanParam);
    
    if((scanParam.scanInterval == 0xFF || scanParam.scanInterval == 0) && (scanParam.scanWindows == 0xFFFF || scanParam.scanWindows == 0))
    {
        scanParam.scanInterval = SCAN_INTERVAL_DEFAULT;
        scanParam.scanWindows = SCAN_WINDOWS_DEFAULT;
//        Flash_ScanParamDataWrite(&scanParam);
    }
    
    if(scanParam.scanEnble == 1)
    {
        // ����ɨ�輰��ʱ��
        StartScanTimer();
#if FLASH_DEBUG
        LOG_RAW("Scan Enble\n");
#endif
    }
    else
    {
#if FLASH_DEBUG
        LOG_RAW("Scan disable[%02X]\n", scanParam.scanEnble);
#endif
    }
    
    
}


///**
// @brief ������������д��
// @param bleNameData -[in] ������������
// @return ��
//*/
//void Flash_BleNameDataWrite(const BleNameData_t *bleNameData)
//{
//    memcpy(&g_totalConfigData.bleNameData, bleNameData, sizeof(BleNameData_t));
//    saveTotalConfigDataInFlash();
//}

///**
// @brief �����������ݶ�ȡ
// @param bleNameData -[out] ������������
// @return ��
//*/
//void Flash_BleNameDataRead(BleNameData_t *bleNameData)
//{
//    memset(bleNameData, 0x00, sizeof(BleNameData_t));                                 // �������
//    memcpy(bleNameData, &g_totalConfigData.bleNameData, sizeof(BleNameData_t));    // ��ȡ����
//}

///**
// @brief �㲥��������д�� 
// @param advParam -[in] �㲥����
// @return ��
//*/
//void Flash_AdvParamDataWrite(const AdvParamsData_t *advParam)
//{
//    memcpy(&g_totalConfigData.advParamsData, advParam, sizeof(AdvParamsData_t));
//    saveTotalConfigDataInFlash();
//}

///**
// @brief �㲥�������ݶ�ȡ
// @param advParam -[out] �㲥����
// @return ��
//*/
//void Flash_AdvParamDataRead(AdvParamsData_t *advParam)
//{
//    memset(advParam, 0x00, sizeof(AdvParamsData_t));                                 // �������
//    memcpy(advParam, &g_totalConfigData.advParamsData, sizeof(AdvParamsData_t));    // ��ȡ����
//}

///**
// @brief ɨ���������д�� 
// @param scanParam -[in] ɨ�����
// @return ��
//*/
//void Flash_ScanParamDataWrite(const ScanParamsData_t *scanParam)
//{
//    memcpy(&g_totalConfigData.scanParam, scanParam, sizeof(ScanParamsData_t));
//    saveTotalConfigDataInFlash();
//}

///**
// @brief ɨ��������ݶ�ȡ
// @param scanParam -[out] ɨ�����
// @return ��
//*/
//void Flash_ScanParamDataRead(ScanParamsData_t *scanParam)
//{
//    memset(scanParam, 0x00, sizeof(ScanParamsData_t));                                 // �������
//    memcpy(scanParam, &g_totalConfigData.scanParam, sizeof(ScanParamsData_t));    // ��ȡ����
//}

///**
// @brief ɨ���������д�� 
// @param scanParam -[in] ɨ�����
// @return ��
//*/
//void Flash_FilterDataWrite(const FilterDeviceData_t *filterData)
//{
//    memcpy(&g_totalConfigData.filterData, filterData, sizeof(FilterDeviceData_t));
//    saveTotalConfigDataInFlash();
//}

///**
// @brief ɨ��������ݶ�ȡ
// @param scanParam -[out] ɨ�����
// @return ��
//*/
//void Flash_FilterDataRead(FilterDeviceData_t *filterData)
//{
//    memset(filterData, 0x00, sizeof(FilterDeviceData_t));                                 // �������
//    memcpy(filterData, &g_totalConfigData.filterData, sizeof(FilterDeviceData_t));    // ��ȡ����
//}

/**
 @brief ���������Flash�е�����
 @param None
 @return None
*/
void Flash_all_erase()
{
	Flash_erase();
}
/****************************************************END OF FILE****************************************************/
