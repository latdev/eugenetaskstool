
#include <ectask.h>

TasksTool::TasksTool() {
  buffer = (tsktool_buffer*) malloc(sizeof(tsktool_buffer));
  buffer->active = false;
  buffer->next = NULL;
};

tsktool_buffer* TasksTool::create(tsktool_buffer* owner) {
  tsktool_buffer* result = (tsktool_buffer*) malloc(sizeof(tsktool_buffer));
  result->active = false;
  result->next = NULL;
  return owner->next = result;
}

tsktool_buffer* TasksTool::empty() {
  tsktool_buffer* owner = NULL;
  tsktool_buffer* cursor = buffer;
  while ( cursor != NULL ) {
    if ( cursor->active == false ) return cursor;
    owner = cursor;
    cursor = cursor->next;
  }
  if ( cursor == NULL ) {
    return create(owner);
  }
}

void TasksTool::every(unsigned long time, stdfunc func) {
  if ( func == NULL ) return;
  tsktool_buffer* item = empty();
  item->active = true;
  item->repeat = true;
  item->init = millis();
  item->time = time;
  item->cbfunc = func;
}

void TasksTool::once(unsigned long time, stdfunc func) {
  if ( func == NULL ) return;
  tsktool_buffer* item = empty();
  item->active = true;
  item->repeat = false;
  item->init = millis();
  item->time = time;
  item->cbfunc = func;
}

unsigned short TasksTool::tasks() {
  unsigned short result = 0;
  tsktool_buffer* cursor = buffer;
  while ( cursor != NULL ) {
    if ( cursor->active ) {
      result += 1;
    }
    cursor = cursor->next;
  }
  return result;
}

void TasksTool::loop() {
  unsigned long now = millis();
  tsktool_buffer* cursor = buffer;
  while ( cursor != NULL ) {
    if (( cursor->active ) && (cursor->init + cursor->time < now)) {
      if ( cursor->repeat == false ) {
        cursor->active = false;
      } else {
        cursor->init = now;
      }
      cursor->cbfunc();
    }
    cursor = cursor->next;
  }
}
