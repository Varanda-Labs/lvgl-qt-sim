/****************************************************************************/
//
//  Module:          $URL: $
//  Created By:      Marcelo Varanda
//  Revision:        $Revision: $
//  Last Updated By: $Author: $
//  Last Updated:    $Date:  $
//
//  Description: Part of M-OS 
//
//  Copyright (c) 2021 Marcelo Varanda, all rights reserved.
//
//
/****************************************************************************/

/* mos_thread_new

  mos_queue_create
  mos_queue_get
  mos_queue_put
  mos_queue_waiting
  mos_timer_create_single_shot */

#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "mos.h"


#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

void * mos_malloc (size_t size) { return malloc(size); }
void * mos_calloc (size_t num, size_t size) {
    void * p = mos_malloc(num * size);
    if (p) memset(p, 0, num * size);
    return p;
}
void mos_free (void * p) { return free(p); }

mos_thread_h_t mos_thread_new( const char *pcName, thread_func_t thread_func, void *pvArg, uint32_t iStackSize, uint32_t iPriority )
{
    pthread_t thread;
    int t = pthread_create(&thread, NULL,
                              (void *(*) (void *)) thread_func, NULL);
    if (t) {
        return NULL;
    }
    return thread;
}

typedef struct queue_st {
    uint8_t *       buffer;
    mos_mutex_h_t   mutex;
    pthread_cond_t  cond;
    uint32_t        item_size;
    uint32_t        max_num_items;
    uint32_t        num_items;
    uint32_t        head_idx;
    uint32_t        tail_idx;
} queue_t;

mos_queue_h_t mos_queue_create ( uint32_t len, uint32_t item_size)
{
  // return xQueueCreate( len, item_size);
  queue_t * h = (queue_t *) MOS_MALLOC(sizeof(queue_t));
  if ( ! h) {
      LOG_E("mos_queue_create: no memo for handle");
      return NULL;
  }
  h->buffer = MOS_CALLOC(len, item_size);
  if ( ! h->buffer) {
      LOG_E("mos_queue_create: no memo for buffer");
      MOS_FREE(h);
      return NULL;
  }

  if (pthread_cond_init(&h->cond, NULL) != 0) {
      LOG_E("mos_queue_create: fail to create condvar");
      return NULL;
  }
  h->mutex = mos_mutex_create();
  h->item_size = item_size;
  h->max_num_items = len;
  h->num_items = 0;
  h->head_idx = 0;
  h->tail_idx = 0;

  return h;
}

int mos_queue_put (mos_queue_h_t queue_id, const void * item_to_queue)
{
  queue_t * q = (queue_t *) queue_id;
  mos_mutex_lock(q->mutex);
  if (q->num_items >= q->max_num_items) {
    LOG_W("mos_queue_put: queue full");
    pthread_cond_signal(&q->cond);
    mos_mutex_unlock(q->mutex);
    return MOS_ERROR;
  }

  uint8_t * byte_ptr = q->buffer + (q->item_size * q->head_idx);
  memcpy(byte_ptr, item_to_queue, q->item_size);
  q->num_items++;
  q->head_idx++;
  if (q->head_idx >= q->max_num_items) {
      q->head_idx = 0;
  }
  pthread_cond_signal(&q->cond);
  mos_mutex_unlock(q->mutex);
  return MOS_PASS;
}
#include "errno.h"

int mos_queue_get (mos_queue_h_t queue_id, void *item_buf, uint32_t timeout_milliseconds)
{
    queue_t * q = (queue_t *) queue_id;
    mos_mutex_lock(q->mutex);


    if (q->num_items == 0) {
      // TODO: add timeout_milliseconds wait
      if (timeout_milliseconds == 0) {
        mos_mutex_unlock(q->mutex);
        return MOS_ERROR;
      }

      // block
      //LOG("mos_queue_get: blocking");
      int err = pthread_cond_wait(&q->cond, q->mutex) ;
      if (err != 0) {
          LOG_E("mos_queue_get: pthread_cond_wait ret: %d", err);
          switch(err) {
          case ETIMEDOUT: //             The time specified by abstime to pthread_cond_timedwait() has passed.
                          //             The pthread_cond_timedwait() and pthread_cond_wait() functions may fail if:
              LOG_E("ETIMEDOUT");
              break;

          case EINVAL: //                The value specified by cond, mutex, or abstime is invalid.
                       //                Different mutexes were supplied for concurrent pthread_cond_timedwait() or pthread_cond_wait() operations on the same condition variable.
              LOG_E("EINVAL");
              break;

          case EPERM://                  The mutex was not owned by the current thread at the time of the call.
              LOG_E("EPERM");
              break;
          default:
              LOG_E("unknown");
              break;

          }
      }
      //LOG("mos_queue_get: unblocked");
    }

    uint8_t * byte_ptr = q->buffer + (q->item_size * q->tail_idx);
    memcpy(item_buf, byte_ptr, q->item_size);
    q->num_items--;
    q->tail_idx++;
    if (q->tail_idx >= q->max_num_items) {
        q->tail_idx = 0;
    }

    mos_mutex_unlock(q->mutex);
    return MOS_PASS;
}

int mos_queue_waiting (mos_queue_h_t queue_id)
{
  int v = 0;
  queue_t * q = (queue_t *) queue_id;
  mos_mutex_lock(q->mutex);
  v = q->num_items;
  mos_mutex_unlock(q->mutex);
  return v; //
}

//----------------- Mutex ------------------
mos_mutex_h_t mos_mutex_create(void)
{
    pthread_mutex_t * mutex_ptr = (pthread_mutex_t *) MOS_MALLOC(sizeof(pthread_mutex_t));
    if ( ! mutex_ptr) {
        LOG_E("mos_mutex_create: no memo for mutex");
        return NULL;
    }
    pthread_mutex_init(mutex_ptr, NULL);
    return mutex_ptr;
}

void mos_mutex_lock(mos_mutex_h_t mutex)
{
    if (pthread_mutex_lock(mutex)) {
        LOG_E("mos_mutex_lock: fail");
    }
}

void mos_mutex_unlock(mos_mutex_h_t mutex)
{
    if (pthread_mutex_unlock(mutex)) {
        LOG_E("mos_mutex_unlock: fail");
    }
}

void mos_mutex_destroy(mos_mutex_h_t mutex)
{
    pthread_mutex_destroy(mutex);
    MOS_FREE(mutex);
}

void mos_thread_sleep( uint32_t time_milliseconds)
{
  usleep(time_milliseconds * 1000);
}



#ifdef __cplusplus
  }
#endif


