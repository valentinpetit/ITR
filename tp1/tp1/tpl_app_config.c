/**
 * @file tpl_app_config.c
 *
 * @section desc File description
 *
 * OS data structure generated from application test
 * Automatically generated by goil on Tue Feb 26 11:11:00 2019
 * from root OIL file tp1.oil
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005-2007
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

#include "tpl_app_config.h"

#include "tpl_os_internal_types.h"
#include "tpl_machine.h"
#include "tpl_os_it.h"
#include "tpl_os_it_kernel.h"
#include "tpl_os_alarm_kernel.h"
#include "tpl_os_alarm.h"
#include "tpl_os_rez_kernel.h"
#include "tpl_os_rez.h"
#include "tpl_os_event_kernel.h"
#include "tpl_os_event.h"
#include "tpl_os_action.h"
#include "tpl_os_kernel.h"
#include "tpl_os_definitions.h"


#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/*=============================================================================
 * Declaration of processes IDs
 */

/* Task task0 identifier */
#define task0_id 0
CONST(TaskType, AUTOMATIC) task0 = task0_id;

/* Task task1 identifier */
#define task1_id 1
CONST(TaskType, AUTOMATIC) task1 = task1_id;

/* Task task2 identifier */
#define task2_id 2
CONST(TaskType, AUTOMATIC) task2 = task2_id;

/* Task task3 identifier */
#define task3_id 3
CONST(TaskType, AUTOMATIC) task3 = task3_id;

/* Task task4 identifier */
#define task4_id 4
CONST(TaskType, AUTOMATIC) task4 = task4_id;

/* ISR isr_button_left identifier */
#define isr_button_left_id 5
/* ISR isr_button_right identifier */
#define isr_button_right_id 6
/* ISR isr_button_start identifier */
#define isr_button_start_id 7
/* ISR isr_button_stop identifier */
#define isr_button_stop_id 8
#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2VAR(tpl_resource, AUTOMATIC, OS_APPL_DATA)
tpl_resource_table[RESOURCE_COUNT] = {
  &res_sched_rez_desc  
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Counters related defines and structures
 */
/*-----------------------------------------------------------------------------
 * Counter SystemCounter descriptor
 */

#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_tick, OS_CONST) OSTICKSPERBASE = 1;
CONST(tpl_tick, OS_CONST) OSMAXALLOWEDVALUE = 2000;
CONST(tpl_tick, OS_CONST) OSMINCYCLE = 1;

#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_counter, OS_VAR) SystemCounter_counter_desc = {
  /* ticks per base       */  1,
  /* max allowed value    */  2000,
  /* minimum cycle        */  1,
  /* current tick         */  0,
  /* current date         */  0,
#if WITH_OSAPPLICATION == YES
    /* OS Application id    */  
#endif
    /* first alarm          */  NULL_PTR,
    /* next alarm to raise  */  NULL_PTR
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#include "tpl_os_kernel.h"          /* tpl_schedule */
#include "tpl_os_timeobj_kernel.h"  /* tpl_counter_tick */
#include "tpl_machine_interface.h"  /* tpl_switch_context_from_it */
#include "AT91SAM7.h" /* AT91C_AIC_ISCR */

#define OS_START_SEC_VAR_8BIT
#include "tpl_memmap.h"
VAR(u8, OS_VAR) check_buttons_period = 0;
#define OS_STOP_SEC_VAR_8BIT
#include "tpl_memmap.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

FUNC(void, OS_CODE) tpl_tick_it_timer1()
{
  tpl_status  need_rescheduling = NO_SPECIAL_CODE;

  need_rescheduling |= tpl_counter_tick(&SystemCounter_counter_desc);

  
  check_buttons_period++;
  if (check_buttons_period == 10)
  {
    /* Call check_buttons_status() (via interrupts)
     * which will check if buttons are pressed or not.
     */
     *AT91C_AIC_ISCR = (1 << AT91C_PERIPHERAL_ID_IRQ0);
     check_buttons_period = 0;
  }

  if (need_rescheduling == NEED_RESCHEDULING)
  {
    tpl_schedule_from_running();
#if WITH_SYSTEM_CALL == NO
    if (tpl_kern.need_switch != NO_NEED_SWITCH) {
      tpl_switch_context_from_it(
        &(tpl_kern.s_old->context),
        &(tpl_kern.s_running->context)
      );
    }
#endif
  }
}

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of Task related defines and structures
 */
/*-----------------------------------------------------------------------------
 * Task task0 descriptor
 */
#define APP_Task_task0_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * Task task0 function prototype
 */
FUNC(void, OS_APPL_CODE) task0_function(void);
#define APP_Task_task0_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task task0 stack
 */
#define APP_Task_task0_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) task0_stack_zone[500/sizeof(tpl_stack_word)];
#define APP_Task_task0_STOP_SEC_STACK
#include "tpl_memmap.h"

#define task0_STACK {task0_stack_zone, 500}

/*
 * Task task0 context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_context, OS_VAR) task0_int_context;

#define task0_CONTEXT &task0_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"



#if WITH_AUTOSAR_TIMING_PROTECTION == YES
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
#endif

/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task task0
 */
CONST(tpl_proc_static, OS_CONST) task0_task_stat_desc = {
  /* context                  */  task0_CONTEXT,
  /* stack                    */  task0_STACK,
  /* entry point (function)   */  task0_function,
  /* internal ressource       */  NULL,
  /* task id                  */  task0_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  2,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* pointer to the timing
     protection descriptor    */  $TIMING_PROT_REF$
#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task task0
 */
VAR(tpl_proc, OS_VAR) task0_task_desc = {
  /* resources                      */  NULL,
#if WITH_MEMORY_PROTECTION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_MEMORY_PROTECTION */
  /* activate count                 */  0,
  /* task priority                  */  2,
  /* task state                     */  AUTOSTART
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task task1 descriptor
 */
#define APP_Task_task1_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * Task task1 function prototype
 */
FUNC(void, OS_APPL_CODE) task1_function(void);
#define APP_Task_task1_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task task1 stack
 */
#define APP_Task_task1_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) task1_stack_zone[500/sizeof(tpl_stack_word)];
#define APP_Task_task1_STOP_SEC_STACK
#include "tpl_memmap.h"

#define task1_STACK {task1_stack_zone, 500}

/*
 * Task task1 context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_context, OS_VAR) task1_int_context;

#define task1_CONTEXT &task1_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"



#if WITH_AUTOSAR_TIMING_PROTECTION == YES
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
#endif

/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task task1
 */
CONST(tpl_proc_static, OS_CONST) task1_task_stat_desc = {
  /* context                  */  task1_CONTEXT,
  /* stack                    */  task1_STACK,
  /* entry point (function)   */  task1_function,
  /* internal ressource       */  NULL,
  /* task id                  */  task1_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  2,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* pointer to the timing
     protection descriptor    */  $TIMING_PROT_REF$
#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task task1
 */
VAR(tpl_proc, OS_VAR) task1_task_desc = {
  /* resources                      */  NULL,
#if WITH_MEMORY_PROTECTION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_MEMORY_PROTECTION */
  /* activate count                 */  0,
  /* task priority                  */  2,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task task2 descriptor
 */
#define APP_Task_task2_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * Task task2 function prototype
 */
FUNC(void, OS_APPL_CODE) task2_function(void);
#define APP_Task_task2_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task task2 stack
 */
#define APP_Task_task2_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) task2_stack_zone[500/sizeof(tpl_stack_word)];
#define APP_Task_task2_STOP_SEC_STACK
#include "tpl_memmap.h"

#define task2_STACK {task2_stack_zone, 500}

/*
 * Task task2 context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_context, OS_VAR) task2_int_context;

#define task2_CONTEXT &task2_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"



#if WITH_AUTOSAR_TIMING_PROTECTION == YES
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
#endif

/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task task2
 */
CONST(tpl_proc_static, OS_CONST) task2_task_stat_desc = {
  /* context                  */  task2_CONTEXT,
  /* stack                    */  task2_STACK,
  /* entry point (function)   */  task2_function,
  /* internal ressource       */  NULL,
  /* task id                  */  task2_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  1,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* pointer to the timing
     protection descriptor    */  $TIMING_PROT_REF$
#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task task2
 */
VAR(tpl_proc, OS_VAR) task2_task_desc = {
  /* resources                      */  NULL,
#if WITH_MEMORY_PROTECTION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_MEMORY_PROTECTION */
  /* activate count                 */  0,
  /* task priority                  */  1,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task task3 descriptor
 */
#define APP_Task_task3_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * Task task3 function prototype
 */
FUNC(void, OS_APPL_CODE) task3_function(void);
#define APP_Task_task3_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task task3 stack
 */
#define APP_Task_task3_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) task3_stack_zone[500/sizeof(tpl_stack_word)];
#define APP_Task_task3_STOP_SEC_STACK
#include "tpl_memmap.h"

#define task3_STACK {task3_stack_zone, 500}

/*
 * Task task3 context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_context, OS_VAR) task3_int_context;

#define task3_CONTEXT &task3_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"



#if WITH_AUTOSAR_TIMING_PROTECTION == YES
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
#endif

/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task task3
 */
CONST(tpl_proc_static, OS_CONST) task3_task_stat_desc = {
  /* context                  */  task3_CONTEXT,
  /* stack                    */  task3_STACK,
  /* entry point (function)   */  task3_function,
  /* internal ressource       */  NULL,
  /* task id                  */  task3_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  1,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* pointer to the timing
     protection descriptor    */  $TIMING_PROT_REF$
#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task task3
 */
VAR(tpl_proc, OS_VAR) task3_task_desc = {
  /* resources                      */  NULL,
#if WITH_MEMORY_PROTECTION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_MEMORY_PROTECTION */
  /* activate count                 */  0,
  /* task priority                  */  1,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Task task4 descriptor
 */
#define APP_Task_task4_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * Task task4 function prototype
 */
FUNC(void, OS_APPL_CODE) task4_function(void);
#define APP_Task_task4_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * Task task4 stack
 */
#define APP_Task_task4_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) task4_stack_zone[500/sizeof(tpl_stack_word)];
#define APP_Task_task4_STOP_SEC_STACK
#include "tpl_memmap.h"

#define task4_STACK {task4_stack_zone, 500}

/*
 * Task task4 context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_context, OS_VAR) task4_int_context;

#define task4_CONTEXT &task4_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"



#if WITH_AUTOSAR_TIMING_PROTECTION == YES
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
#endif

/*
  No timing protection
 */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of task task4
 */
CONST(tpl_proc_static, OS_CONST) task4_task_stat_desc = {
  /* context                  */  task4_CONTEXT,
  /* stack                    */  task4_STACK,
  /* entry point (function)   */  task4_function,
  /* internal ressource       */  NULL,
  /* task id                  */  task4_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  1,
  /* max activation count     */  1,
  /* task type                */  TASK_BASIC,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* pointer to the timing
     protection descriptor    */  $TIMING_PROT_REF$
#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task task4
 */
VAR(tpl_proc, OS_VAR) task4_task_desc = {
  /* resources                      */  NULL,
#if WITH_MEMORY_PROTECTION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_MEMORY_PROTECTION */
  /* activate count                 */  0,
  /* task priority                  */  1,
  /* task state                     */  SUSPENDED
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Definition and initialization of ISR2 related defines and structures
 */
/*-----------------------------------------------------------------------------
 * ISR isr_button_left descriptor
 */
#define APP_ISR_isr_button_left_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * ISR isr_button_left function prototype
 */
FUNC(void, OS_APPL_CODE) isr_button_left_function(void);
#define APP_ISR_isr_button_left_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * ISR isr_button_left stack
 */
#define APP_ISR_isr_button_left_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) isr_button_left_stack_zone[500/sizeof(tpl_stack_word)];
#define APP_ISR_isr_button_left_STOP_SEC_STACK
#include "tpl_memmap.h"

#define isr_button_left_STACK {isr_button_left_stack_zone, 500}

/*
 * ISR isr_button_left context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_context, OS_VAR) isr_button_left_int_context;

#define isr_button_left_CONTEXT &isr_button_left_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"



/*
  No timing protection
 */

#if WITH_AUTOSAR_TIMING_PROTECTION == YES
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
#endif

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of ISR isr_button_left
 */
CONST(tpl_proc_static, OS_CONST) isr_button_left_isr_stat_desc = {
  /* context                  */  isr_button_left_CONTEXT,
  /* stack                    */  isr_button_left_STACK,
  /* entry point (function)   */  isr_button_left_function,
  /* internal ressource       */  NULL,
  /* ISR id                   */  isr_button_left_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  3,
  /* max activation count     */  1,
  /* task type                */  IS_ROUTINE,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* pointer to the timing
     protection descriptor    */  $TIMING_PROT_REF$
#endif
};

CONST(tpl_isr_static, OS_CONST) isr_button_left_isr_helper = {
  /* helper */ NULL,
  /* next */   NULL,
  /* id */     isr_button_left_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of ISR isr_button_left
 */
VAR(tpl_proc, OS_VAR) isr_button_left_isr_desc = {
  /* resources                      */  NULL,
#if WITH_MEMORY_PROTECTION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_MEMORY_PROTECTION */
  /* activate count                 */  0,
  /* ISR priority                   */  3,
  /* ISR state                      */  SUSPENDED,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* activation allowed             */  ,TRUE
#endif
};
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * ISR isr_button_right descriptor
 */
#define APP_ISR_isr_button_right_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * ISR isr_button_right function prototype
 */
FUNC(void, OS_APPL_CODE) isr_button_right_function(void);
#define APP_ISR_isr_button_right_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * ISR isr_button_right stack
 */
#define APP_ISR_isr_button_right_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) isr_button_right_stack_zone[500/sizeof(tpl_stack_word)];
#define APP_ISR_isr_button_right_STOP_SEC_STACK
#include "tpl_memmap.h"

#define isr_button_right_STACK {isr_button_right_stack_zone, 500}

/*
 * ISR isr_button_right context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_context, OS_VAR) isr_button_right_int_context;

#define isr_button_right_CONTEXT &isr_button_right_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"



/*
  No timing protection
 */

#if WITH_AUTOSAR_TIMING_PROTECTION == YES
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
#endif

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of ISR isr_button_right
 */
CONST(tpl_proc_static, OS_CONST) isr_button_right_isr_stat_desc = {
  /* context                  */  isr_button_right_CONTEXT,
  /* stack                    */  isr_button_right_STACK,
  /* entry point (function)   */  isr_button_right_function,
  /* internal ressource       */  NULL,
  /* ISR id                   */  isr_button_right_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  3,
  /* max activation count     */  1,
  /* task type                */  IS_ROUTINE,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* pointer to the timing
     protection descriptor    */  $TIMING_PROT_REF$
#endif
};

CONST(tpl_isr_static, OS_CONST) isr_button_right_isr_helper = {
  /* helper */ NULL,
  /* next */   NULL,
  /* id */     isr_button_right_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of ISR isr_button_right
 */
VAR(tpl_proc, OS_VAR) isr_button_right_isr_desc = {
  /* resources                      */  NULL,
#if WITH_MEMORY_PROTECTION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_MEMORY_PROTECTION */
  /* activate count                 */  0,
  /* ISR priority                   */  3,
  /* ISR state                      */  SUSPENDED,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* activation allowed             */  ,TRUE
#endif
};
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * ISR isr_button_start descriptor
 */
#define APP_ISR_isr_button_start_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * ISR isr_button_start function prototype
 */
FUNC(void, OS_APPL_CODE) isr_button_start_function(void);
#define APP_ISR_isr_button_start_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * ISR isr_button_start stack
 */
#define APP_ISR_isr_button_start_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) isr_button_start_stack_zone[500/sizeof(tpl_stack_word)];
#define APP_ISR_isr_button_start_STOP_SEC_STACK
#include "tpl_memmap.h"

#define isr_button_start_STACK {isr_button_start_stack_zone, 500}

/*
 * ISR isr_button_start context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_context, OS_VAR) isr_button_start_int_context;

#define isr_button_start_CONTEXT &isr_button_start_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"



/*
  No timing protection
 */

#if WITH_AUTOSAR_TIMING_PROTECTION == YES
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
#endif

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of ISR isr_button_start
 */
CONST(tpl_proc_static, OS_CONST) isr_button_start_isr_stat_desc = {
  /* context                  */  isr_button_start_CONTEXT,
  /* stack                    */  isr_button_start_STACK,
  /* entry point (function)   */  isr_button_start_function,
  /* internal ressource       */  NULL,
  /* ISR id                   */  isr_button_start_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  3,
  /* max activation count     */  1,
  /* task type                */  IS_ROUTINE,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* pointer to the timing
     protection descriptor    */  $TIMING_PROT_REF$
#endif
};

CONST(tpl_isr_static, OS_CONST) isr_button_start_isr_helper = {
  /* helper */ NULL,
  /* next */   NULL,
  /* id */     isr_button_start_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of ISR isr_button_start
 */
VAR(tpl_proc, OS_VAR) isr_button_start_isr_desc = {
  /* resources                      */  NULL,
#if WITH_MEMORY_PROTECTION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_MEMORY_PROTECTION */
  /* activate count                 */  0,
  /* ISR priority                   */  3,
  /* ISR state                      */  SUSPENDED,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* activation allowed             */  ,TRUE
#endif
};
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * ISR isr_button_stop descriptor
 */
#define APP_ISR_isr_button_stop_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * ISR isr_button_stop function prototype
 */
FUNC(void, OS_APPL_CODE) isr_button_stop_function(void);
#define APP_ISR_isr_button_stop_STOP_SEC_CODE
#include "tpl_memmap.h"

/*-----------------------------------------------------------------------------
 * Target specific structures
 */
/*
 * ISR isr_button_stop stack
 */
#define APP_ISR_isr_button_stop_START_SEC_STACK
#include "tpl_memmap.h"
VAR(tpl_stack_word, OS_APPL_DATA) isr_button_stop_stack_zone[500/sizeof(tpl_stack_word)];
#define APP_ISR_isr_button_stop_STOP_SEC_STACK
#include "tpl_memmap.h"

#define isr_button_stop_STACK {isr_button_stop_stack_zone, 500}

/*
 * ISR isr_button_stop context
 */
#define OS_START_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"
VAR(arm_context, OS_VAR) isr_button_stop_int_context;

#define isr_button_stop_CONTEXT &isr_button_stop_int_context

#define OS_STOP_SEC_VAR_NOINIT_32BIT
#include "tpl_memmap.h"



/*
  No timing protection
 */

#if WITH_AUTOSAR_TIMING_PROTECTION == YES
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
#endif

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*
 * Static descriptor of ISR isr_button_stop
 */
CONST(tpl_proc_static, OS_CONST) isr_button_stop_isr_stat_desc = {
  /* context                  */  isr_button_stop_CONTEXT,
  /* stack                    */  isr_button_stop_STACK,
  /* entry point (function)   */  isr_button_stop_function,
  /* internal ressource       */  NULL,
  /* ISR id                   */  isr_button_stop_id,
#if WITH_OSAPPLICATION == YES
  /* OS application id        */  
#endif
  /* task base priority       */  3,
  /* max activation count     */  1,
  /* task type                */  IS_ROUTINE,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* pointer to the timing
     protection descriptor    */  $TIMING_PROT_REF$
#endif
};

CONST(tpl_isr_static, OS_CONST) isr_button_stop_isr_helper = {
  /* helper */ NULL,
  /* next */   NULL,
  /* id */     isr_button_stop_id
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of ISR isr_button_stop
 */
VAR(tpl_proc, OS_VAR) isr_button_stop_isr_desc = {
  /* resources                      */  NULL,
#if WITH_MEMORY_PROTECTION == YES
  /* if > 0 the process is trusted  */  0,    
#endif /* WITH_MEMORY_PROTECTION */
  /* activate count                 */  0,
  /* ISR priority                   */  3,
  /* ISR state                      */  SUSPENDED,
#if WITH_AUTOSAR_TIMING_PROTECTION == YES
  /* activation allowed             */  ,TRUE
#endif
};
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#include "tpl_machine.h"


/* Interrupt functions */

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

FUNC(void, OS_CODE) tpl_interrupt_source_1()
{

  tpl_tick_it_timer1();

  systick_isr_C_function(); 
}

FUNC(void, OS_CODE) tpl_interrupt_source_2()
{

  nxt_motor_isr_C_function(); 
}

FUNC(void, OS_CODE) tpl_interrupt_source_5()
{

  spi_isr_C_function(); 
}

FUNC(void, OS_CODE) tpl_interrupt_source_7()
{

  bt_isr_C_function(); 
}

FUNC(void, OS_CODE) tpl_interrupt_source_9()
{

  twi_isr_C_function(); 
}

FUNC(void, OS_CODE) tpl_interrupt_source_10()
{

  systick_low_priority_C_function(); 
}

FUNC(void, OS_CODE) tpl_interrupt_source_12()
{

  i2c_timer_isr_C_function(); 
}

FUNC(void, OS_CODE) tpl_interrupt_source_15()
{

  tpl_central_interrupt_handler(7); 
}

FUNC(void, OS_CODE) tpl_interrupt_source_16()
{

  tpl_central_interrupt_handler(5); 
}

FUNC(void, OS_CODE) tpl_interrupt_source_17()
{

  tpl_central_interrupt_handler(6); 
}

FUNC(void, OS_CODE) tpl_interrupt_source_18()
{

  tpl_central_interrupt_handler(8); 
}

FUNC(void, OS_CODE) tpl_interrupt_source_30()
{

  check_buttons_status_function(); 
}

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"


/* Interrupt table vector */

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONST(tpl_it_vector_entry, OS_CONST) tpl_it_vector[31] = {
  { tpl_null_it, (void *)NULL },
  { tpl_interrupt_source_1, (void *)NULL },
  { tpl_interrupt_source_2, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_interrupt_source_5, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_interrupt_source_7, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_interrupt_source_9, (void *)NULL },
  { tpl_interrupt_source_10, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_interrupt_source_12, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_interrupt_source_15, (void *)NULL },
  { tpl_interrupt_source_16, (void *)NULL },
  { tpl_interrupt_source_17, (void *)NULL },
  { tpl_interrupt_source_18, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_null_it, (void *)NULL },
  { tpl_interrupt_source_30, (void *)NULL }
};
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/*=============================================================================
 * Definition and initialization of process tables (tasks and isrs)
 */
CONSTP2CONST(tpl_proc_static, AUTOMATIC, OS_APPL_DATA)
tpl_stat_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &task0_task_stat_desc,
  &task1_task_stat_desc,
  &task2_task_stat_desc,
  &task3_task_stat_desc,
  &task4_task_stat_desc,
  &isr_button_left_isr_stat_desc,
  &isr_button_right_isr_stat_desc,
  &isr_button_start_isr_stat_desc,
  &isr_button_stop_isr_stat_desc,
  &idle_task_static
};

CONSTP2VAR(tpl_proc, AUTOMATIC, OS_APPL_DATA)
tpl_dyn_proc_table[TASK_COUNT+ISR_COUNT+1] = {
  &task0_task_desc,
  &task1_task_desc,
  &task2_task_desc,
  &task3_task_desc,
  &task4_task_desc,
  &isr_button_left_isr_desc,
  &isr_button_right_isr_desc,
  &isr_button_start_isr_desc,
  &isr_button_stop_isr_desc,
  &idle_task
};

CONSTP2CONST(tpl_isr_static, AUTOMATIC, OS_APPL_DATA)
tpl_isr_stat_table[ISR_COUNT] = {
  &isr_button_left_isr_helper,
  &isr_button_right_isr_helper,
  &isr_button_start_isr_helper,
  &isr_button_stop_isr_helper
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


/*=============================================================================
 * Declaration of flags functions
 */
/* $FLAGSFUNCTIONS$ */


/*=============================================================================
 * Definition and initialization of Ready List structures
 */
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_proc_id, OS_VAR) tpl_priority_0_fifo[1];
VAR(tpl_proc_id, OS_VAR) tpl_priority_1_fifo[3];
VAR(tpl_proc_id, OS_VAR) tpl_priority_2_fifo[3];
VAR(tpl_proc_id, OS_VAR) tpl_priority_3_fifo[12];

VAR(tpl_fifo_state, OS_VAR) tpl_fifo_rw[4] = {
  { 0 , 0 },
  { 0 , 0 },
  { 0 , 0 },
  { 0 , 0 }
};

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

CONST(tpl_priority_level, OS_CONST) tpl_ready_list[4] = {
  { tpl_priority_0_fifo, 1 },
  { tpl_priority_1_fifo, 3 },
  { tpl_priority_2_fifo, 3 },
  { tpl_priority_3_fifo, 12 }
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define API_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
CONSTP2CONST(char, AUTOMATIC, OS_APPL_DATA) proc_name_table[TASK_COUNT + ISR_COUNT] = {
  "task0",
  "task1",
  "task2",
  "task3",
  "task4",
  "isr_button_left",
  "isr_button_right",
  "isr_button_start",
  "isr_button_stop"
};
#define API_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

/* End of file tpl_app_config.c */
