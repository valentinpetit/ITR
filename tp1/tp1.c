/**
 * @file tp1.c
 *
 * @section desc File description
 *
 *
 * @section copyright Copyright
 *
 *
 * @section infos File informations
 *
 * $Date$ ven. févr.  8 14:41:17 CET 2019
 * $Rev$
 * $Author$ 11000766
 * $URL$ /private/student/6/66/11000766/Documents/ITR/ITR_TP1/tp1
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
DeclareTask(task0);
DeclareTask(task1);
DeclareTask(task2);
DeclareTask(task3);
DeclareTask(task4);

void PreTaskHook() {
    display_string("PreTaskHook \n");
}

void PostTaskHook() {
    display_string("PosTaskHook \n");
}

TASK(task0)
{    
	display_string("task0 : \n hello World \n");
	display_update();
	systick_wait_ms(3000);
    ActivateTask(task1);
}

TASK(task1){
	display_clear(1);
	display_goto_xy(0,0);
	display_string("task1 :");
	display_int(systick_get_ms(), 3);
	display_string("\n");
	display_update();
	systick_wait_ms(3000);
	ActivateTask(task2);
}

TASK(task2){
	display_clear(1);
	display_goto_xy(0,0);
	display_string("task2 : \n call Task3 \n");
	display_update();
	systick_wait_ms(3000);
	ChainTask(task3);
}

TASK(task3){
	display_clear(1);
	display_goto_xy(0,0);
	display_string("task3 : ");
	display_int(systick_get_ms(), 3);
	display_string("\n");
	systick_wait_ms(3000);
	display_update();
}

TASK(task4){
	display_clear(1);
	display_goto_xy(0,0);
	display_string("task4 : \n");
	display_string("bouton right \n pushed \n");
	systick_wait_ms(3000);
	display_update();
}
ISR(isr_button_start)
{
//    ecrobot_status_monitor("isr_button_start"); 
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
	display_clear(1);
	display_goto_xy(0,0);
	display_string("click \n right button \n");
	ActivateTask(task4);

}

/* End of file tp1.c */
