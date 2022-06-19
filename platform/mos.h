#ifndef __MOS_H__
#define __MOS_H__
/***************************************************************
 *
 *                 This code is part of LVGL-Qt-Simulator
 *
 * Copyrights 2021 - Varanda Labs Inc.
 *
 * License:
 *   Creative Commons: CC BY-NC-SA 4.0
 *   Attribution-NonCommercial-ShareAlike 4.0 International
 *   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
 *
 *   Note: for purchasing a commertial license contact:
 *     m@varanda.ca
 *
 ***************************************************************
 */

//#include "filesys.h"
#include <stdint.h>
#include <stdbool.h>
#include "log.h"

#ifdef MOS_DESKTOP
  #define MOS_PASS    0
  #define MOS_ERROR   -1
  #define MOS_WAIT_FOREVER 0xffffffff
#else
  #include "FreeRTOS.h"
  #define MOS_WAIT_FOREVER portMAX_DELAY
  #define MOS_PASS         pdPASS
  #define MOS_FAIL         pdFAIL
  #define MOS_ERROR        pdFAIL
  #define MOS_TRUE         pdTRUE
  #define MOS_FALSE        pdFALSE
#endif

void * mos_malloc (size_t size);
void * mos_calloc (size_t num, size_t size);
void mos_free (void * p);

#if 1
  #define MOS_MALLOC(s) mos_malloc (s)
  #define MOS_CALLOC(n,s) mos_calloc (n,s)
  #define MOS_FREE(p) mos_free(p)
#else
  #define MOS_MALLOC(s) NATIVE_MALLOC(s)
  #define MOS_CALLOC(n,s) NATIVE_CALLOC (n,s)
  #define MOS_FREE(p) NATIVE_FREE(p)
#endif

//----- MOS types
typedef uint32_t mos_timer_id_t;
typedef void * mos_timer_h_t;
typedef void * mos_queue_h_t;
typedef void * mos_thread_h_t;
typedef void * mos_mutex_h_t;

typedef void (*thread_func_t)(void * arg);
typedef void (*timer_func_t)(mos_timer_id_t timer_id);

#define MOS_GET_ELAPSE_TIME(start_time) (mos_get_ms_timestamp() - start_time)


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Inicialize OS
 *
 *
 * @return None
 */
void mos_init(void);

//------------ thread funcs --------------

/**
 * @brief Create a thread
 *
 * Starts a new thread with priority "prio" that will begin its
 * execution in the function "thread_func()". The "arg" argument will be
 * passed as an argument to the thread_func() function. The id of the new
 * thread is returned. Both the id and the priority are system
 * dependent.
 *
 * @param name Name of thread
 * @param thread_func Pointer to function to run.
 * @param arg Argument passed into function
 * @param stacksize Required stack amount in bytes
 * @param prio Thread priority
 *
 * @return upon success returns a valid mos_thread_h_t. NULL if error.
 */
mos_thread_h_t mos_thread_new( const char *name, thread_func_t thread_func, void *arg, uint32_t iStackSize, uint32_t iPriority );

/**
 * @brief Return the thread ID of the caller thread.
 *
 *
 * @return thread ID.
 */
mos_thread_h_t mos_thread_get_id (void);

/**
 * @brief Delete a thread
 *
 * Starts a new thread with priority "prio" that will begin its
 * execution in the function "thread_func()". The "arg" argument will be
 * passed as an argument to the thread_func() function. The id of the new
 * thread is returned. Both the id and the priority are system
 * dependent.
 *
 * @param thread Thread ID. A NULL can be used for a self-delete operation.
 *
 * @return None.
 */
void mos_thread_delete(mos_thread_h_t thread);

/**
 * @brief Suspend a thread
 *
 * Places a thread into the Suspended state. A thread that is in the Suspended state will never be selected to enter the Running state.
 * The only way of removing a thread from the Suspended state is to make it the subject of a call to mos_thread_resume().
 *
 * @param thread Thread ID. A NULL can be used for a self-delete operation.
 *
 * @return None.
 */
void mos_thread_suspend(mos_thread_h_t thread);

/**
 * @brief Resume a Suspended thread
 *
 *
 * Transition a thread from the Suspended state to the Ready state.
 * The thread must have previously been placed into the Suspended state using a call to mos_thread_suspend
 *
 * @param thread Thread ID.
 *
 * @return None.
 */
void mos_thread_resume(mos_thread_h_t thread);

/**
 * @brief thread sleep (in milliseconds)
 *
 *
 * Places the thread that calls mos_thread_sleep() into the Blocked state for a fixed number of time.
 *
 * @param time_milliseconds Duration that the thread will be blocked (sleeping).
 *
 * @return None.
 */
void mos_thread_sleep( uint32_t time_milliseconds);

//------------- queue ----------------

/**
 * @brief Create a Queue
 *
 *
 * Creates a new queue and returns an id by which the queue can be referenced.
 * Each queue requires RAM that is used to hold the queue state, and to hold the items that are contained
 * in the queue (the queue storage area). the the required RAM
 * is automatically allocated from the orbos heap.
 *
 * @param len The maximum number of items that the queue being created can hold at any one time.
 * @param item_size The size, in bytes, of each data item that can be stored in the queue.
 *
 * @return upon success returns a valid mos_queue_h_t. NULL if error.
 */
mos_queue_h_t mos_queue_create ( uint32_t len, uint32_t item_size);

/**
 * @brief place an item at the end of a queue
 *
 * @param queue_id The ID of the queue to which the item is being placed (written).
 *        The queue ID will have been returned from the call to mos_queue_create()
 *        or mos_queue_create_static() used to create the queue.
 * @param item_to_queue A pointer to the data to be copied into the queue.
 *        The size of each item the queue can hold is set when the queue is created,
 *        and that many bytes will be copied from pvItemToQueue into the queue storage area.
 *
 * @return MOS_PASS if OK.
 */
int mos_queue_put (mos_queue_h_t queue_id, const void * item_to_queue);

/**
 * @brief place an item at the end of a queue
 *
 * Same than mos_queue_put but mos_queue_put_from_isr can be called inside an ISR.
 *
 * @see mos_queue_put
 */
int mos_queue_put_from_isr (mos_queue_h_t xQueue, const void * pvItemToQueue);

/**
 * @brief get an item from a queue
 *
 * @param queue_id The ID of the queue from which the data is being received (read).
 *        The queue ID will have been returned from the call to mos_queue_create()
 *        or mos_queue_create_static() used to create the queue.
 * @param item_buf A pointer to the memory into which the received data will be copied to.
 *        The length of the buffer must be at least equal to the queue item size.
 *        The item size will have been set by the item_size parameter of the call to mos_queue_create()
 *        or mos_queue_create_static() used to create the queue.
 * @param timeout_milliseconds The maximum amount of time the thread should remain in the Blocked state
 *        to wait for data to become available on the queue, should the queue already be empty.
 *        If timeout_milliseconds is zero, then mos_queue_get() will return immediately if the queue is already empty.
 *        timeout_milliseconds = MOS_WAIT_FOREVER will cause the thread to wait indefinitely (without timing out).
 *
 * @return MOS_TRUE if an item was. Otherwise, either timeout or error.
 * @note called must be sure that it is providing a valid queue ID as there is no distinction between timeout and error.
 */
int mos_queue_get (mos_queue_h_t queue_id, void *item_buf, uint32_t timeout_milliseconds);

/**
 * @brief return num entries queued
 *
 * @return num entries queued.
 *
 */
int mos_queue_waiting (mos_queue_h_t xQueue);

//--------------- RTC -------------------
#if 0
/**
 * @brief get a time-of-the-day structure
 *
 * @param rtc_time structure for time-of-the-day.
 *
 * @return None.
 */
void mos_get_rtc_time ( mos_rtc_time_t * rtc_time);

/**
 * @brief get a time-of-the-day in seconds
 *
 * @return RTC time-of-the-day in seconds.
 */
uint32_t mos_get_rtc_time_in_seconds(void);

/**
 * @brief convert a time in a time-of-the-day structure to seconds
 *
 * @return RTC time-of-the-day in seconds.
 */
uint32_t mos_rtc_time_to_seconds(const mos_rtc_time_t *datetime);

/**
 * @brief convert a time in seconds to a time-of-the-day structure
 *
 * @return None
 */
void mos_seconds_to_rtc_time(uint32_t seconds, mos_rtc_time_t *datetime);

/**
 * @brief get a time in seconds since the system was initialized.
 *
 * @return time in seconds since power up.
 */
uint32_t mos_get_uptime_in_secs( void );

/**
 * @brief get a time in milliseconds since the system was initialized.
 *
 * @return time in seconds since power up.
 */
uint64_t mos_get_ms_timestamp(void);

#endif
//---------- timers ----------

/**
 * @brief Create and start a single shot timer
 *
 * After the time expires the callback function is called. The timer self destroys once it expires.
 * A call for mos_timer_delete can be performed in case there is a need to prevent the timer to expire.
 *
 * @param time_milliseconds Expiring time (max 2,900,000 milliseconds)
 * @param callback Function called upon time expiring
 * @param id Generic user defined identifier passed to the callback.
 *
 * @return timer ID or NULL if error.
 *
 * @note system timer roll after 994 days.
 */
bool mos_timer_create_single_shot( uint32_t time_milliseconds, timer_func_t callback, mos_timer_id_t id );

/**
 * @brief Create and start a single shot timer
 *
 * After the time expires the callback function is called. Timer restarts
 * A call for mos_timer_delete can be performed in case there is a need to prevent the timer to expire.
 *
 * @param time_milliseconds periodic Expiring time (max 2,900,000 milliseconds)
 * @param callback Function called upon time expiring
 * @param arg Generic user defined argument passed to the callback.
 *
 * @return timer ID or NULL if error.
 *
 */
mos_timer_h_t mos_timer_create_periodic( uint32_t time_milliseconds, timer_func_t callback, void * arg );


/**
 * @brief Create and start a single shot SLOW timer
 *
 * After the time expires the callback function is called. The timer self destroys once it expires.
 * A call for mos_timer_delete can be performed in case there is a need to prevent the timer to expire.
 *
 * @param time_minutes Expiring time in minutes
 * @param callback Function called upon time expiring
 * @param arg Generic user defined argument passed to the callback.
 *
 * @return timer ID or NULL if error.
 * @note this timer has a (low) precision of +/- 1 minute.
 *
 */
bool mos_slow_timer_create_single_shot( uint64_t time_minutes, timer_func_t callback, mos_timer_id_t id);

/**
 * @brief Delete a timer
 *
 *
 * @param timer_id Timer ID
 *
 * @return None
 */
void mos_timer_delete ( mos_timer_id_t timer_id );

/**
 * @brief Delete a timer
 *
 *
 * @param timer_id Timer ID
 *
 * @return Remaining time to expire: in milliseconds for regular timer or in minutes for slow timers. -1 if given an invalid timer ID.
 */
int mos_timer_get_remaining ( mos_timer_id_t timer_id );

//--------- counters -------
/**
 * @brief Get a timestamp from a freerunner counter.
 *
 * @return timestamp incremented 32768 per second.
 */
uint64_t mos_get_raw_timestamp(void);

/**
 * @brief Get a float timestamp.
 *
 * @return float timestamp wher its granularity is based on mos_get_raw_timestamp.
 */
float mos_get_timestamp(void); // second

//----------- Mutex -----------
/**
 * @brief Create a mutex object.
 *
 * @return mutex ID.
 */
mos_mutex_h_t mos_mutex_create(void);

/**
 * @brief Lock a mutex.
 *
 * *param mutex Mutex ID to be locked
 *
 * @return mutex None.
 */
void mos_mutex_lock(mos_mutex_h_t mutex);

/**
 * @brief destroy a mutex.
 *
 * *param mutex Mutex ID to be locked
 *
 * @return mutex None.
 */
void mos_mutex_destroy(mos_mutex_h_t mutex);


/**
 * @brief Unlock a mutex.
 *
 * *param mutex Mutex ID to be unlocked
 *
 * @return mutex None.
 */
void mos_mutex_unlock(mos_mutex_h_t mutex);

//------------------------------------------

void mos_loop(void);

//__noreturn void mos_reset(void);

void mos_shutdown(void);


#ifdef __cplusplus
}
#endif


//----------------------------
#endif
