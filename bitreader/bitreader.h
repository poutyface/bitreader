#ifndef _bitreader_h
#define _bitreader_h

#include <stdint.h>

typedef struct BitReader{
  const uint8_t *data;
  uint32_t size;
  uint32_t reservoir;
  uint32_t leftbits;
}BitReader;


int8_t bitreader_init(BitReader *reader, const uint8_t *data, uint32_t size);

/*
 this function return range n value of bits
 uint8_t n: this parameter range is 0 <= n <= 32.
*/
uint32_t get_bits(BitReader *reader, uint8_t n);

/*
  this function skip bits from current position.
*/
void skip_bits(BitReader *reader, uint32_t n);

/*
  this function return num of bits that BitReader contains
*/
uint32_t bitreader_size(BitReader *reader);

/*
  this function return current position pointer of data (carefully: pointer is per bytes)
 */
const uint8_t* bitreader_data(BitReader *reader);

#endif
