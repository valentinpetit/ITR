
/**
 * @file itr_claptrap.c
 *
 * @section desc File description
 *
 *
 * @section copyright Copyright
 *
 *
 * @section infos File informations
 *
 * $Date$ mar. mars  5 10:29:38 CET 2019
 * $Rev$
 * $Author$ 16009249
 * $URL$ /private/student/9/49/16009249/ITR/itr-labs/itr_claptrap
 */

#include "tpl_os.h"
#include "nxt_motors.h"
#include "ecrobot_interface.h" 
#include "ecrobot_private.h"

FUNC(int, OS_APPL_CODE) main(void)
{   
  StartOS(OSDEFAULTAPPMODE);
  ShutdownOS(E_OK);
  return 0;
}

/**
 * Global variables
 */
int distance_contact, distance_sonar;
// int tsA, tsB; touch sensors A and B;

/**
 * TASK declaration
 */
DeclareTask(init);
DeclareTask(motors);
DeclareTask(detection_contact);
DeclareTask(detection_distance);
DeclareTask(navigation);

/**
 * TASK Implementation
 */
TASK(init) {
  // activate sound sensor on port 2
  ecrobot_init_sonar_sensor(NXT_PORT_S2);
}

TASK(motors) {
  // start motors on port A & B at 70 (100 : forward, -100 : backward)
  ecrobot_set_motor_speed(NXT_PORT_A, 70);
  ecrobot_set_motor_speed(NXT_PORT_B, 70);
}

TASK(detection_contact) {
  // return 0 if the robot touches somethins on BOTH sensors
  distance_contact = !ecrobot_get_touch_sensor(NXT_PORT_S1) || !ecrobot_get_touch_sensor(NXT_PORT_S3);
}

TASK(detection_distance) {
  //get distance from sonar sensor in centimeters
  distance_sonar = ecrobot_get_sonar_sensor(NXT_PORT_S2);
  
  // dummy code to avoid a .rxe file at 35Ko which freezes software
  if(distance_sonar) {
    display_clear(0);
    display_goto_xy(0,0);
    display_int(distance_sonar, 1);
    display_update();
    display_clear(0);
    display_goto_xy(0,0);
    display_int(distance_sonar, 1);
    display_update();
    display_clear(0);
    display_goto_xy(0,0);
    display_int(distance_sonar, 1);
    display_update();
    display_clear(0);
    display_goto_xy(0,0);
    display_int(distance_sonar, 1);
    display_update();
    display_clear(0);
    display_goto_xy(0,0);
    display_int(distance_sonar, 1);
    display_update();
    display_clear(0);
    display_goto_xy(0,0);
    display_int(distance_sonar, 1);
    display_update();
    display_clear(0);
    display_goto_xy(0,0);
    display_int(distance_sonar, 1);
    display_update();
  }
}

TASK(navigation) {
  if(distance_contact == 0) {
    // reverse gears
    ecrobot_set_motor_speed(NXT_PORT_A, -60);
    ecrobot_set_motor_speed(NXT_PORT_B, -60);
  } else if(distance_sonar < 50) {
    // go arbitrarly to the left to try to avoid smtg
    ecrobot_set_motor_speed(NXT_PORT_A, 20);
    ecrobot_set_motor_speed(NXT_PORT_B, 60);
  } else {
    // go forward
    ChainTask(motors);
  }
}

/**
 * HOOK Implementation
 */

void PreTaskHook() {
  display_clear(0);
}

void PostTaskHook() {
  display_clear(0);
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

/* End of file itr_claptrap.c */
