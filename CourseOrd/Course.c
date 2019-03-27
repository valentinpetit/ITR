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

//task init
// priorite 50 
TASK(init)
{
	ecrobot_init_sonar_sensor(NXT_PORT_S3);
}

//	Task principale
//	priorité 1
TASK(mouve){
	// adaptation vitesse
	if(distance > 100){vitesse = 100;}
	else{vitesse=distance;}
	ecrobot_set_motor_speed(NXT_PORT_A, vitesse);
	ecrobot_set_motor_speed(NXT_PORT_C, vitesse);
	
	if(collide == 1)
	{
		//go back
		nxt_motor_set_count(NXT_PORT_A, -200);
		nxt_motor_set_count(NXT_PORT_C, -200);
		//rotate 1/8 rigth
		nxt_motor_set_count(NXT_PORT_A, 0);
		nxt_motor_set_count(NXT_PORT_C, 0);
	}
	else if(collide == 1)
	{
		//go back		
		nxt_motor_set_count(NXT_PORT_A, -200);
		nxt_motor_set_count(NXT_PORT_C, -200);
		//rotate 1/8 left
		nxt_motor_set_count(NXT_PORT_A, 0);
		nxt_motor_set_count(NXT_PORT_C, 0);
	}
	else if(vitesse < 30 && pathSearch == 0)
	{
		//rotate 3/8 rigth
		nxt_motor_set_count(NXT_PORT_A, 0);
		nxt_motor_set_count(NXT_PORT_C, 0);
		pathSearch=1;
	}
	else if(distance < 30 && pathSearch == 1)
	{
		//rotate 1/8 left
		nxt_motor_set_count(NXT_PORT_A, 0);
		nxt_motor_set_count(NXT_PORT_C, 0);
		pathSearch=1;
	}
	else
	{ 
		pathSearch=0;
	}
}


//Task check collision
// priorité 2
TASK(check)
{	
	distance = ecrobot_get_sonar_sensor(NXT_PORT_S3);
		
	if(distance <20 )
	{
		distance=0;
	}
	else if(ecrobot_get_touch_sensor(NXT_PORT_S4) == 1)
	{
		collide = 2;
		distance = 0;
	}
	else if(ecrobot_get_touch_sensor(NXT_PORT_S1) == 1)
	{
		collide = 1;
		distance = 0;
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
