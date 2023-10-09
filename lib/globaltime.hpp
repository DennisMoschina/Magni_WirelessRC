#ifndef GLOBALTIME_HPP
#define GLOBALTIME_HPP


#include <stdint.h>

class GlobalTime {
public:
  uint32_t getTimeMS() {
    return currentTimeMS;
  }
  
  void advanceTime(uint32_t ms) {
    currentTimeMS += ms;
  }

private:
  uint32_t currentTimeMS = 0;
};

#endif
