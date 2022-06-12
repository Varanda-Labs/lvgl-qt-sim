#include <QtTest>
#include <unistd.h>
#include "mos_desktop_timer.h"

extern "C" {
//-------- mos_desktop_timer variables ------
extern uint64_t tick_counter;
extern list_entry_t list[NUM_MAX_TIMERS];
extern uint32_t list_num_entries;
extern list_entry_t * head;
static mos_timer_id_t expired_timer_id = 0;

//-------- mos_desktop_timer functions ------
extern list_entry_t * insert( uint64_t expire, timer_func_t callback, mos_timer_id_t id);
extern bool mos_timer_create_single_shot( uint32_t time_minutes, timer_func_t callback, mos_timer_id_t id);


//------- local test functions -------

static void reset_list(void){
    memset (list, 0, sizeof(list)); //[NUM_MAX_TIMERS];
    list_num_entries = 0;
    head = NULL;
}

static void timer_callback(mos_timer_id_t timer_id) {
    //LOG("Test timer callback called");
    expired_timer_id = timer_id;
}

static bool dumplist(void)  {
    list_entry_t * entry = head;
    uint64_t last_expire = 0;
    while (entry) {
        LOG("entry expire = %d", entry->expire);
        if (entry->expire < last_expire) {
            LOG_E("expire %d is lower than last_expire", entry->expire, last_expire);
            return false;
        }
        last_expire = entry->expire;
        entry = entry->next;
    }
    return true;
}

}

// add necessary includes here

class testMos : public QObject
{
    Q_OBJECT

public:
    testMos();
    ~testMos();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

testMos::testMos()
{

}

testMos::~testMos()
{

}

void testMos::initTestCase()
{

}

void testMos::cleanupTestCase()
{

}



void testMos::test_case1()
{
  list_entry_t * entry;// = insert( 1000, timer_callback, NULL);
  uint32_t i;

#if 1
  //-------- check if list gets full -----
  for (i=0; i< NUM_MAX_TIMERS; i++) {
    entry = insert( 1000 * i+1, timer_callback, NULL);
    LOG("added entry %d", i+1);
    QVERIFY(entry != NULL);
  }
  entry = insert( 20000, timer_callback, NULL);
  QVERIFY(entry == NULL); // must fail

#endif


  //--------- test add lowest expire -----
  // fill half list
  reset_list(); // clear list
  for (i=0; i< NUM_MAX_TIMERS / 2; i++) {
    entry = insert( 1000 * i, timer_callback, NULL);
    QVERIFY(entry != NULL);
  }
  LOG("\nAdd lowest expire value = 500");
  entry = insert( 500, timer_callback, NULL);
  QVERIFY(dumplist());

  //--------- test add middle expire value-----
  LOG("\nAdd middle expire value = 2500");
  entry = insert( 2500, timer_callback, NULL);
  QVERIFY(dumplist());

  //--------- test add high expire value-----
  LOG("\nAdd highest expire value = 12500");
  entry = insert( 12500, timer_callback, NULL);
  QVERIFY(dumplist());

  //----- test timers ------
#define TEST_TM  200 // 200 ms
#define SLEEP_60_PERCENT MILLISEC_TO_TICK( ((TEST_TM * 6) / 10))
  LOG("Start timer service and test 20 timers");
  reset_list();
  mos_timer_init();
  bool r;
  for (i = 1; i <= 20; i++) {
    QVERIFY( mos_timer_create_single_shot( TEST_TM, timer_callback, i));
    usleep (SLEEP_60_PERCENT  * TICK_PERIOD);
    QVERIFY2(i != expired_timer_id, "Timer id has already been updated even before expiring time"); // must be different
    usleep (SLEEP_60_PERCENT  * TICK_PERIOD);
    //LOG("Expected id = %d, got %d", i, expired_timer_id);
    QVERIFY2(i == expired_timer_id, "mismatch timer id"); // must be equal
  }
  QVERIFY2(list_num_entries == 0, "list_num_entries must be zero");
  LOG("Timers are fine.");

}

QTEST_APPLESS_MAIN(testMos)

#include "tst_testmos.moc"
