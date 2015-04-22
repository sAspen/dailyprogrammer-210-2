#ifndef NETPBM_H
#define	NETPBM_H

#include <cstdint>
#include <fstream>
#include <tuple>

enum NETPBM_TYPE {
  INVALID,
  MONOCHROME_ASCII,
  GRAYSCALE_ASCII,
  RGB_ASCII,
  MONOCHROME_BINARY,
  GRAYSCALE_BINARY,
  RGB_BINARY
};

class Netpbm {
private:
  std::fstream file;
  std::string name;
  unsigned int width, height;
  NETPBM_TYPE type;
  uint16_t maxVal;

protected:

public:
  Netpbm(std::string name);
  Netpbm(std::string name, unsigned int width, unsigned int height,
          NETPBM_TYPE type, uint16_t maxVal);

  void writePixel(uint8_t r, uint8_t g, uint8_t b);
  void writePixel(uint8_t p);
  void save(void);
};

#endif	/* NETPBM_H */

