/*********************************************************************
* INCLUDES
*/
#include "board_gpio.h"

/*********************************************************************
* LOCAL VARIABLES
*/


/*********************************************************************
* PUBLIC FUNCTIONS
*/
/**
 @brief GPIO��ʼ��
 @param ��
 @return ��
*/
void GPIOInit()
{
//	bx_pm_lock( BX_PM_GPIO );
    bxd_gpio_open( BX_GPIOA );                                     //��ʱ��
	bxd_gpio_set_mode( BX_GPIOA, key_0, BX_GPIO_MODE_INPUT );      //���ð���1����10Ϊ����ģʽ
	bxd_gpio_set_mode( BX_GPIOA, key_1, BX_GPIO_MODE_INPUT );      //���ð���2����15Ϊ����ģʽ
    bxd_gpio_set_mode( BX_GPIOA, IR_IO, BX_GPIO_MODE_INPUT );      //���ú�������16Ϊ����ģʽ
	
	bxd_gpio_set_pull( BX_GPIOA, key_0, BX_GPIO_PULLUP );
	bxd_gpio_set_pull( BX_GPIOA, key_1, BX_GPIO_PULLUP );
	bxd_gpio_set_pull( BX_GPIOA, IR_IO, BX_GPIO_PULLDOWN );
	
//    bxd_gpio_write( BX_GPIOA, IR_IO, 0 );                          //������16��ƽ����
//	bxd_gpio_write( BX_GPIOA, key_0, 1 );                          
//	bxd_gpio_write( BX_GPIOA, key_1, 1 );                          
	
//	bxd_gpio_set_mode( BX_GPIOA, IR_IO, BX_GPIO_MODE_IT_RISING );  //����IRΪ�����ش����ж�
//	
//    bxd_gpio_enable_intr( BX_GPIOA );                              //ʹ���ж�
}

/**
 @brief GPIO�жϺ���
 @param ��
 @return ��
*/
//������bxd_gpio.c���GPIO_IRQHandler�жϺ���

/**
 @brief 
 @param L_data [in] - 
 @return ��
*/
void keyCallback(uint8_t *L_data)
{
	
}