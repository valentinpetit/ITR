/**
 * @file tp2.c
 *
 * @section desc File description
 *
 *
 * @section copyright Copyright
 *
 *
 * @section infos File informations
 *
 * $Date$ mar. févr. 26 11:12:47 CET 2019
 * $Rev$
 * $Author$ 13006499
 * $URL$ /private/student/9/99/13006499/M1/ITR/tp2
 */

#include "tpl_os.h"
#include "nxt_motors.h"
#include "ecrobot_interface.h" 
#include "ecrobot_private.h"
//var globale
int distance = 0;

FUNC(int, OS_APPL_CODE) main(void)
{   
    StartOS(OSDEFAULTAPPMODE);
    ShutdownOS(E_OK);
    return 0;
}

DeclareTask(task1);
DeclareTask(detection_contact_gauche);
DeclareTask(detection_contact_droit);

TASK(task1)
{
	ecrobot_init_sonar_sensor(NXT_PORT_S3);// set US to port 3
	distance=ecrobot_get_sonar_sensor(NXT_PORT_S3);
	//ecrobot_set_motor_speed(NXT_PORT_A,100);
	//ecrobot_set_motor_speed(NXT_PORT_C, 100);
	/*while(1){
		systick_wait_ms(100);
		if(ecrobot_get_touch_sensor(NXT_PORT_S4) == 1 
		&& ecrobot_get_touch_sensor(NXT_PORT_S1) == 1)
		{
			ChainTask(detection_contact_gauche);
		}
		if(ecrobot_get_touch_sensor(NXT_PORT_S4) == 1)
		{
		ChainTask(detection_contact_gauche);
		}
		
		else if(ecrobot_get_touch_sensor(NXT_PORT_S1) == 1)
		{
		ChainTask(detection_contact_droit);
		}
	}*/
	
		ecrobot_init_sonar_sensor(NXT_PORT_S2);
	while(1){
		display_clear(1);
		display_goto_xy(0,0);
		display_int(ecrobot_get_sonar_sensor(NXT_PORT_S2), 3);
		display_update();
		
		systick_wait_ms(500);
	}
}

TASK(detection_contact_gauche)
{
	//if(distance == 0)
	//{
		ecrobot_set_motor_speed(NXT_PORT_A, -100);
		ecrobot_set_motor_speed(NXT_PORT_C, -100);
		systick_wait_ms(1000);
		ecrobot_set_motor_speed(NXT_PORT_A, -100);
		ecrobot_set_motor_speed(NXT_PORT_C, 0);
		systick_wait_ms(500);
		ecrobot_set_motor_speed(NXT_PORT_A, 100);
		ecrobot_set_motor_speed(NXT_PORT_C, 100);	
	//}
	ChainTask(task1);	
}

TASK(detection_contact_droit)
{
	//if(distance ==0)
	//{
		ecrobot_set_motor_speed(NXT_PORT_A, -100);
		ecrobot_set_motor_speed(NXT_PORT_C, -100);
		systick_wait_ms(1000);
		ecrobot_set_motor_speed(NXT_PORT_A, 0);
		ecrobot_set_motor_speed(NXT_PORT_C, -100);
		systick_wait_ms(500);
		ecrobot_set_motor_speed(NXT_PORT_A, 100);
		ecrobot_set_motor_speed(NXT_PORT_C, 100);	
	//}
	ChainTask(task1);	
}

ISR(isr_button_start)
{
  //  ecrobot_status_monitor("isr_button_start");
    
}

ISR(isr_button_stop)
{
    ShutdownOS(E_OK);
}

ISR(isr_button_left)
{
   // ecrobot_status_monitor("isr_button_left"); 

}

ISR(isr_button_right)
{
   // ecrobot_status_monitor("isr_button_right");   

}

/* End of file tp2.c */
