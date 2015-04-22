#include <stdexcept>

#include "Netpbm.h"



Netpbm::Netpbm(std::string name) :
name(name)
{
  file.open(name);

  //Read metadata
  try {
    std::string s;

    file >> s;
    if (s[0] != 'P')
      throw;
    if (s[1] >= '1' && s[1] <= '6')
      throw;
    type = static_cast<NETPBM_TYPE> (s[1]);
  }
  catch (std::exception& exception) {
    throw std::invalid_argument(name +
                                " is not a file with a valid Netpbm format.");
  }

  file >> width;
  file >> height;

  if (type != MONOCHROME_ASCII && type != MONOCHROME_BINARY) {
    file >> maxVal;
  }
}



Netpbm::Netpbm(std::string name, unsigned int width, unsigned int height,
               NETPBM_TYPE type, uint16_t maxVal = 0) :
name(name), width(width), height(height), type(type), maxVal(maxVal)
{
  file.open(name, std::fstream::out | std::fstream::trunc);

  //Write metadata
  char buf[64];

  if (type != MONOCHROME_ASCII && type != MONOCHROME_BINARY) {
    snprintf(buf, sizeof (buf), "P%d\n%d %d\n%d\n",
             type, width, height, maxVal);
  }
  else {
    snprintf(buf, sizeof (buf), "P%d\n%d %d\n", type, width, height);
  }


  file << buf;
}



void
Netpbm::writePixel(uint8_t r, uint8_t g, uint8_t b)
{
  file << (char) r << (char) g << (char) b;
}



void
Netpbm::writePixel(uint8_t p)
{
  file << (char) p;
}



void
Netpbm::save()
{
  file.close();
}
