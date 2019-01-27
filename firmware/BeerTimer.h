/*
 * BeerTimer.h
 *
 * Created: 02.12.2018 16:52:54
 *  Author: stenkelfled
 */ 


#ifndef BEERTIMER_H_
#define BEERTIMER_H_

#define BEERTIMER_TICK_DURATION   1 //in seconds

class BeerTime
{
private:  
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
  }  my_time;
  
public:
  BeerTime()
  {
    this->my_time.full = 0;
  }
  BeerTime(uint32_t start_time)
  {
    this->my_time.full = start_time;
  }
  BeerTime& operator=(const uint16_t& new_time)
  {
    //this->my_time.split.extend = 0;
    this->my_time.split.rtc = new_time;
    return *this;
  }
  BeerTime& operator=(const uint32_t& new_time)
  {
    this->my_time.full = new_time;
    return *this;
  }
  BeerTime& operator=(const BeerTime& new_time)
  {
    this->my_time = new_time.my_time;
    return *this;
  }
  /*BeerTime& operator+=(const uint16_t& rhs)
  {
    this->my_time.full += rhs;
    return *this;
  }
  BeerTime& operator+=(const uint32_t& rhs)
  {
    this->my_time.full += rhs;
    return *this;
  }*/
  BeerTime& operator+=(const BeerTime& rhs)
  {
    this->my_time.full += rhs.my_time.full;
    return *this;
  }
  /*friend BeerTime operator+(BeerTime lhs, const uint16_t& rhs)
  {
    lhs += rhs;
    return lhs;
  }
  friend BeerTime operator+(BeerTime lhs, const uint32_t& rhs)
  {
    lhs += rhs;
    return lhs;
  }*/
  friend BeerTime operator+(BeerTime lhs, const BeerTime& rhs)
  {
    lhs += rhs;
    return lhs;
  }
  BeerTime& operator-=(const BeerTime& rhs)
  {
    this->my_time.full -= rhs.my_time.full;
    return *this;
  }
  friend BeerTime operator-(BeerTime lhs, const BeerTime& rhs)
  {
    lhs -= rhs;
    return lhs;
  }
  inline bool operator<(const BeerTime& rhs)
  {
    return this->my_time.full < rhs.my_time.full;
  }
  inline bool operator>(const BeerTime& rhs)
  {
    return this->my_time.full > rhs.my_time.full;
  }
  inline bool operator<=(const BeerTime& rhs)
  {
    return this->my_time.full <= rhs.my_time.full;
  }    
  inline bool operator>=(const BeerTime& rhs)
  {
    return this->my_time.full >= rhs.my_time.full;
  }
  
  /**
   * @brief increment 16-bit extension
   */
  void incrExt()
  {
    this->my_time.full += ((uint32_t)1)<<16;
  }
  
};

class BeerTimer
{  
public:
  BeerTimer();
  void update();
  BeerTime getTime();
  
  void rtcOvfHdl();
  
protected:
private:
  BeerTime mtime;
  
};



#endif /* BEERTIMER_H_ */