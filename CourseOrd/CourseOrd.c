/**
 * @file CourseOrd.c
 *
 * @section desc File description
 *
 *
 * @section copyright Copyright
 *
 *
 * @section infos File informations
 *
 * $Date$ mar. mars 26 09:41:51 CET 2019
 * $Rev$
 * $Author$ 11000766
 * $URL$ /private/student/6/66/11000766/Documents/ITR/CourseOrd
 */

#include "tpl_os.h"
#include "nxt_motors.h"
#include "ecrobot_interface.h" 
#include "ecrobot_private.h"
int distance = 0;
int vitesse = 0;
int pathSearch = 0;
int collide = 0;

FUNC(int, OS_APPL_CODE) main(void)
{   
    StartOS(OSDEFAULTAPPMODE);
    ShutdownOS(E_OK);
    return 0;
}

DeclareTask(init);
DeclareTask(check);
DeclareTask(mouve);

// initialisation task
// priorite 50 
TASK(init)
{
	ecrobot_init_sonar_sensor(NXT_PORT_S3);
}

//	Movment task
//	priorité 1
TASK(mouve)
{
		
	if(collide == 1)
	{
		//back
		ecrobot_set_motor_speed(NXT_PORT_A, -100);
		ecrobot_set_motor_speed(NXT_PORT_C, -100);
		systick_wait_ms(250);
		//rotate 1/16 rigth
		ecrobot_set_motor_speed(NXT_PORT_A, 100);
		systick_wait_ms(200);
		ecrobot_set_motor_speed(NXT_PORT_A, 0);
		ecrobot_set_motor_speed(NXT_PORT_C, 0);
		collide =0;
	}
	else if (collide == 2)
	{
		//back
		ecrobot_set_motor_speed(NXT_PORT_A, -100);
		ecrobot_set_motor_speed(NXT_PORT_C, -100);
		systick_wait_ms(250);
		//rotate 1/16 left
		ecrobot_set_motor_speed(NXT_PORT_A, 100);
		systick_wait_ms(200);
		ecrobot_set_motor_speed(NXT_PORT_A, 0);
		ecrobot_set_motor_speed(NXT_PORT_C, 0);
		collide =0;
	}
	else if(distance < 30 && pathSearch == 3 )
	{
		//rotate 1/8 left
		ecrobot_set_motor_speed(NXT_PORT_A, 100);
		ecrobot_set_motor_speed(NXT_PORT_C, -100);
		systick_wait_ms(400);
		ecrobot_set_motor_speed(NXT_PORT_A, 0);
		ecrobot_set_motor_speed(NXT_PORT_C, 0);
	}
	else if(distance < 30 && pathSearch < 3)
	{
		//rotate 1/8 rigth
		ecrobot_set_motor_speed(NXT_PORT_A, -100);
		ecrobot_set_motor_speed(NXT_PORT_C, 100);
		systick_wait_ms(400);
		ecrobot_set_motor_speed(NXT_PORT_A, 0);
		ecrobot_set_motor_speed(NXT_PORT_C, 0);
		pathSearch++;
	}
	else
	{ 
		// Speed setting
		if(distance > 60)
		{
			vitesse = 60;
		}
		else
		{
			vitesse=distance;
		}
		ecrobot_set_motor_speed(NXT_PORT_A, vitesse);
		ecrobot_set_motor_speed(NXT_PORT_C, vitesse);
		pathSearch=0;
	}
}


// Checking collision task
// priorité 2
TASK(check)
{	
	distance = ecrobot_get_sonar_sensor(NXT_PORT_S3);
	display_clear(1);
	display_goto_xy(0,0);
	display_int(distance, 3);
	display_update();
	
	if(distance < 30 )
	{
		ecrobot_set_motor_speed(NXT_PORT_A, 0);
		ecrobot_set_motor_speed(NXT_PORT_C, 0);
	}
	else if(ecrobot_get_touch_sensor(NXT_PORT_S4) == 1)
	{
		collide = 2;
		ecrobot_set_motor_speed(NXT_PORT_A, 0);
		ecrobot_set_motor_speed(NXT_PORT_C, 0);
	}
	else if(ecrobot_get_touch_sensor(NXT_PORT_S1) == 1)
	{
		collide = 1;
		ecrobot_set_motor_speed(NXT_PORT_A, 0);
		ecrobot_set_motor_speed(NXT_PORT_C, 0);
	}
}

ISR(isr_button_start)
{
    ecrobot_status_monitor("isr_button_start");
    
}

ISR(isr_button_stop)
{
    ShutdownOS(E_OK);
}

ISR(isr_button_left)
{
    ecrobot_status_monitor("isr_button_left"); 

}

ISR(isr_button_right)
{
    ecrobot_status_monitor("isr_button_right");   

}

/* End of file CourseOrd.c */
