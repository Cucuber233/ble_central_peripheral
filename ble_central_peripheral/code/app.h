/**
  ******************************************************************************
  * @file   :   .h
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "bx_type_def.h"
#include "rwip_task.h"
#include "co_bt.h"
#include "ke_task.h"
#include "gapc_task.h"
#include "gapm_task.h"
#include "gattc_task.h"
#include "co_error.h"
#include "ke_timer.h"
#include "bx_kernel_timer.h"
#include "bx_kernel.h"
#include "app_dis.h"
/* config --------------------------------------------------------------------*/
#define APP_DEVICE_NAME_MAX_LEN         (18)
#define APP_IDX_MAX                     (1)
/* exported paras ------------------------------------------------------------*/

enum user_msg_app {
    USM_APP_FIRST = BXM_FIRST_USER_MSG,
    
    USM_APP_STOP_ADV,
    USM_APP_START_SCAN,
    // add by wude
    USM_APP_STOP_SCAN,
    USM_APP_START_ADV,
	USM_APP_ADV_AND_SCAN_TIMER,
	
	LED_FLASH_ON_EVENT,  
	LED_FLASH_OFF_EVENT,
	
	PROMPT_TIMEOUT_EVENT,
	DIMMING_MODE_EVENT,
	AUTO_SAVE_DATA_EVENT,
	SAVE_FLASH_EVENT,
	STOP_CHANGE_ADV_SCAN,
	
	DIMMINGALARM,         //������������

};    
    
    
/* exported types ------------------------------------------------------------*/
/// States of APP task
enum appm_state_def
{
    /// Initialization state
    APP_INIT,
    /// Database create state
    APP_CREATE_DB,
    /// Ready State
    APP_READY,
    /// Advertising state
    APP_ADVERTISING,
    /// Connected state
    APP_CONNECTED,
    /// Number of defined states.
    APP_STATE_MAX
};

struct app_env_tag
{
    /// Connection handle
    uint16_t conhdl;
    /// Connection Index
    uint8_t  conidx;

    /// Last initialized profile
    uint8_t next_svc;

    /// Bonding status
    bool bonded;

    /// Device Name length
    uint8_t dev_name_len;
    /// Device Name
    uint8_t dev_name[APP_DEVICE_NAME_MAX_LEN];

    /// Local device IRK( Identity Resolving Key)
    uint8_t loc_irk[16];

    /// Secure Connections on current link
    bool sec_con_enabled;

    /// Counter used to generate IRK
    uint8_t rand_cnt;
};

typedef void ( *add_svc_func_t )( void );

/* exported variables --------------------------------------------------------*/
extern struct app_env_tag app_env;
extern const struct ke_state_handler appm_default_handler;
extern ke_state_t app_state[APP_IDX_MAX];

extern s32 user_service_id;

extern bool led_status;    //ѡ��״̬

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

void app_init( void );
void app_ble_init( void );
void app_on_ble_init( void );
bool app_add_svc( void );
void app_set_dev_cfg( struct gapm_set_dev_config_cmd * );
void app_on_ble_ready( void );
void app_on_ble_disconnect( void );
void app_on_ble_connect_fail( void );
uint8_t app_get_dev_name( uint8_t * name );

int app_on_scan_adv_report( ke_msg_id_t const msgid, adv_report_t const * param, ke_task_id_t const dest_id, ke_task_id_t const src_id );

void SystemTickEvent(void);
void KeyEvent(void);


#ifdef __cplusplus
}
#endif

#endif /* __USER_APP_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
