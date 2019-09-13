/* 
* RingBuffer.h
*
* Created: 10.03.2019 16:35:38
* Author: stenkelfled
*/


#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

#include <stddef.h>

template <class T> class RingBuffer
{
//variables
public:
protected:
private:
  T * const mBuf;
  size_t const mBuflen;

//functions
public:
	RingBuffer(T * const buf, size_t const len): mBuf(buf), mBuflen(len){};
	~RingBuffer();
protected:
private:
	RingBuffer( const RingBuffer &c );
	RingBuffer& operator=( const RingBuffer &c );

}; //RingBuffer

#endif //__RINGBUFFER_H__
