#ifndef __EUGENE_TASK_TOOL__
#define __EUGENE_TASK_TOOL__

#include <Arduino.h>

typedef void (*stdfunc)(void);

typedef struct tsktool_buffer {
  bool active;
  bool repeat;
  unsigned long init;
  unsigned long time;
  stdfunc cbfunc;
  void* next;
};

class TasksTool {

  private:

	tsktool_buffer* buffer; // first task element
    unsigned long last_task_walk = 0; // last hit to tasks time

    tsktool_buffer* create(tsktool_buffer* owner);
    tsktool_buffer* empty();

  public:

    TasksTool();
    void every(unsigned long time, stdfunc func);
    void once(unsigned long time, stdfunc func);
    unsigned short tasks();
    void loop();

};

#endif