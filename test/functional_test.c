#include "test_helper.h"
#include "bitreader.h"

int main()
{
  BitReader reader;
  uint8_t data[2] = {0xF0, 0xF0};
  uint8_t data2[4] = {0xF0, 0xF0, 0xF0, 0xF0};
  uint32_t value = 0;

  BitReader_init(&reader, data, 2);

  value = BitReader_get_size(&reader);
  check(value == 2 * 8, "should be equal 2 * 8");

  value = BitReader_get_bits(&reader, 1);
  check(value == 1, "should be equal 1");
  value = BitReader_get_bits(&reader, 2);
  check(value == 3, "should be equal 3");
  value = BitReader_get_bits(&reader, 2);
  check(value == 2, "should be equal 2");
  value = BitReader_get_bits(&reader, 4);
  check(value == 1, "should be equal 1");
  value = BitReader_get_bits(&reader, 7);
  check(value == 0x70, "should be equal 0x70");
  value = BitReader_get_size(&reader);
  check(value == 0, "should be equal 0");


  BitReader_init(&reader, data2, 4);
  value = BitReader_get_size(&reader);
  check(value == 4 * 8, "should be equal 32");
  value = BitReader_get_bits(&reader, 32);
  check(value == 0xF0F0F0F0, "should be equal 0xF0F0F0F0");
  value = BitReader_get_size(&reader);
  check(value == 0, "should be equal 0");


  BitReader_init(&reader, data2, 4);
  BitReader_skip_bits(&reader, 8);
  value = BitReader_get_size(&reader);
  check(value == 24, "should be equal 24");
  value = BitReader_get_bits(&reader, 24);
  check(value == 0xF0F0F0, "should be equal 0xF0F0F0");
  return 0;

 error:
  return -1;
}
