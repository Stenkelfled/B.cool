/*
 * BeerTimer.h
 *
 * Created: 02.12.2018 16:52:54
 *  Author: stenkelfled
 */ 


#ifndef BEERTIMER_H_
#define BEERTIMER_H_

#define BEERTIMER_TICK_DURATION   1 //in seconds

class BeerTimer
{
public:
  union uTime
  {
    uint32_t full;
    struct
    {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
      uint16_t rtc;
      uint16_t extend;
#else
#error byte order not implemented!
#endif
    } split;
  };
  
  BeerTimer();
  void update();
  
  void rfcOvfHdl();
  
protected:
private:
  static uTime global_time;
  uTime my_time;
  
};



#endif /* BEERTIMER_H_ */