/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include "stm32f4_discovery.h"
/* Kernel includes. */
#include "stm32f4xx.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"
#include "../FreeRTOS_Source/include/semphr.h"
#include "../FreeRTOS_Source/include/task.h"
#include "../FreeRTOS_Source/include/timers.h"

#define mainREGION_1_SIZE                     8201
#define mainREGION_2_SIZE                     23905
#define mainREGION_3_SIZE                     16807
#define mainCREATE_SIMPLE_BLINKY_DEMO_ONLY    1

static void prvInitialiseHeap( void );

extern void main_DDS( void );


int main( void )
    {
    prvInitialiseHeap();

    #if ( mainCREATE_SIMPLE_BLINKY_DEMO_ONLY == 1 )
        {
            main_DDS();
        }
    #else
        {
            //main_full();
        }
    #endif /* if ( mainCREATE_SIMPLE_BLINKY_DEMO_ONLY == 1 ) */

    return 0;
}



   static void prvInitialiseHeap( void )
    {
    /* The Windows demo could create one large heap region, in which case it would
     * be appropriate to use heap_4.  However, purely for demonstration purposes,
     * heap_5 is used instead, so start by defining some heap regions.  No
     * initialisation is required when any other heap implementation is used.  See
     * http://www.freertos.org/a00111.html for more information.
     *
     * The xHeapRegions structure requires the regions to be defined in start address
     * order, so this just creates one big array, then populates the structure with
     * offsets into the array - with gaps in between and messy alignment just for test
     * purposes. */
        static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
        volatile uint32_t ulAdditionalOffset = 19; /* Just to prevent 'condition is always true' warnings in configASSERT(). */
        const HeapRegion_t xHeapRegions[] =
        {
            /* Start address with dummy offsets						Size */
            { ucHeap + 1,                                          mainREGION_1_SIZE },
            { ucHeap + 15 + mainREGION_1_SIZE,                     mainREGION_2_SIZE },
            { ucHeap + 19 + mainREGION_1_SIZE + mainREGION_2_SIZE, mainREGION_3_SIZE },
            { NULL,                                                0                 }
        };

        /* Sanity check that the sizes and offsets defined actually fit into the
         * array. */
        configASSERT( ( ulAdditionalOffset + mainREGION_1_SIZE + mainREGION_2_SIZE + mainREGION_3_SIZE ) < configTOTAL_HEAP_SIZE );

        /* Prevent compiler warnings when configASSERT() is not defined. */
        ( void ) ulAdditionalOffset;

        vPortDefineHeapRegions( xHeapRegions );
    }




/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* The malloc failed hook is enabled by setting
	configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.

	Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software 
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected.  pxCurrentTCB can be
	inspected in the debugger if the task name passed into this function is
	corrupt. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
volatile size_t xFreeStackSpace;

	/* The idle task hook is enabled by setting configUSE_IDLE_HOOK to 1 in
	FreeRTOSConfig.h.

	This function is called on each cycle of the idle task.  In this case it
	does nothing useful, other than report the amount of FreeRTOS heap that
	remains unallocated. */
	xFreeStackSpace = xPortGetFreeHeapSize();

	if( xFreeStackSpace > 100 )
	{
		/* By now, the kernel has allocated everything it is going to, so
		if there is a lot of heap remaining unallocated then
		the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
		reduced accordingly. */
	}
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
	/* Ensure all priority bits are assigned as preemption priority bits.
	http://www.freertos.org/RTOS-Cortex-M3-M4.html */
	NVIC_SetPriorityGrouping( 0 );

	/* TODO: Setup the clocks, etc. here, if they were not configured before
	main() was called. */
}
