/**
 * @file Course.c
 *
 * @section desc File description
 *
 *
 * @section copyright Copyright
 *
 *
 * @section infos File informations
 *
 * $Date$ mar. mars  5 10:52:58 CET 2019
 * $Rev$
 * $Author$ 13006499
 * $URL$ /private/student/9/99/13006499/M1/ITR/Course
 */

#include "tpl_os.h"
#include "nxt_motors.h"
#include "ecrobot_interface.h" 
#include "ecrobot_private.h"

int distance = 0;
int vitesse = 0;
int pathSearch = 0;

FUNC(int, OS_APPL_CODE) main(void)
{   
    StartOS(OSDEFAULTAPPMODE);
    ShutdownOS(E_OK);
    return 0;
}

DeclareTask(init);
DeclareTask(check_collide);
DeclareTask(stop);
DeclareTask(maincourse);
DeclareTask(search_path);

//task init
// priorite 50 
TASK(init)
{
	ecrobot_init_sonar_sensor(NXT_PORT_S3);
	distance = ecrobot_get_sonar_sensor(NXT_PORT_S3);
	ChainTask(maincourse);
}

//	Task principale
//	priorité minimale
TASK(maincourse){
	// adaptation vitesse
	if(distance > 100){vitesse = 100;}
	else if (distance > 20){vitesse = distance;}
	else{vitesse = 0;}
	ecrobot_set_motor_speed(NXT_PORT_A, vitesse);
	ecrobot_set_motor_speed(NXT_PORT_C, vitesse);
	
	distance = ecrobot_get_sonar_sensor(NXT_PORT_S3);
	
	display_clear(1);
	display_goto_xy(0,0);
	display_string("main");
	display_update();
	
	ChainTask(check_collide);
}


//Task check collision
// priorité 2
TASK(check_collide){
	
		distance = ecrobot_get_sonar_sensor(NXT_PORT_S3);
		display_clear(1);
		display_goto_xy(0,0);
		display_int(distance ,3);
		display_update();
		
		if(distance <20)
		{
			ChainTask(stop);
		}
		else if(ecrobot_get_touch_sensor(NXT_PORT_S4) == 1)
		{
			ecrobot_set_motor_speed(NXT_PORT_A, -100);
			ecrobot_set_motor_speed(NXT_PORT_C, 0);
			systick_wait_ms(500);
		}
		else if(ecrobot_get_touch_sensor(NXT_PORT_S1) == 1)
		{
			ecrobot_set_motor_speed(NXT_PORT_A, 0);
			ecrobot_set_motor_speed(NXT_PORT_C, -100);
			systick_wait_ms(500);
		}
		
		ChainTask(maincourse);
	}
 
// Task stop
// priorité maximale

TASK(stop){
	//moteur à zero
	display_clear(1);
	display_goto_xy(0,0);
	display_string("stop");
	display_update();
	ecrobot_set_motor_speed(NXT_PORT_A, -100);
	ecrobot_set_motor_speed(NXT_PORT_C, -100);
	systick_wait_ms(300);
	distance = 0;
	ChainTask(serach_path);
}

// Task search path

TASK(serach_path){
	if(pathSearch == 0)
	{
		//rotate 3/8 rigth
		ecrobot_set_motor_speed(NXT_PORT_A, 0);
		ecrobot_set_motor_speed(NXT_PORT_C, -100);
		systick_wait_ms(750);
		ecrobot_set_motor_speed(NXT_PORT_C, 0);
		pathSearch=1;
	}
	distance = ecrobot_get_sonar_sensor(NXT_PORT_S3);
	
	if(distance < 30)
	{
		//rotate 1/8 left
		ecrobot_set_motor_speed(NXT_PORT_A, -100);
		ecrobot_set_motor_speed(NXT_PORT_C, 0);
		systick_wait_ms(250);
		ecrobot_set_motor_speed(NXT_PORT_A, 0);
		ChainTask(serach_path);
	}
	else
	{
		//continue
		pathSearch=0;
		ChainTask(maincourse);
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

/* End of file Course.c */
