#include <stdio.h>
#include "bitreader.h"

static void fill_reservoir(BitReader *reader)
{
  uint8_t i;

  reader->reservoir = 0;
  for(i=0; reader->size > 0 && i < 4; ++i){
    reader->reservoir = (reader->reservoir << 8) | *(reader->data);
    reader->data += 1;
    reader->size -= 1;
  }

  reader->leftbits = i * 8;
  reader->reservoir <<= 32 - reader->leftbits;
}



int8_t bitreader_init(BitReader *reader, const uint8_t *data, uint32_t size)
{
  if(!reader || !data || !size)
    return -1;

  reader->data = data;
  reader->size = size;
  reader->reservoir = 0;
  reader->leftbits = 0;
  return 0;
}


uint32_t get_bits(BitReader *reader, uint8_t n)
{
  uint32_t result = 0;
  uint8_t m = 0;

  while(n > 0){
    if(reader->leftbits == 0)
      fill_reservoir(reader);

    m = n;
    if(m > reader->leftbits)
      m = reader->leftbits;

    result = (result << m) | (reader->reservoir >> (32 - m));
    reader->reservoir <<= m;
    reader->leftbits -= m;
    n -= m;
  }

  return result;
}


void skip_bits(BitReader *reader, uint32_t n)
{
  while(n > 32){
    get_bits(reader, 32);
    n -= 32;
  }

  if(n > 0)
    get_bits(reader, n);
}


uint32_t bitreader_size(BitReader *reader)
{
  return reader->size * 8 + reader->leftbits;
}


const uint8_t* bitreader_data(BitReader *reader)
{
  return reader->data - (reader->leftbits / 8);
}
