#ifndef __WRITE_H__
#define __WRITE_H__

#include <Rinternals.h>

struct Header {
  SEXPTYPE type;
  size_t size;
  short element_size;
};

void _write(const char* path, Header* header, const char* buf);

void _readHeader(const char* path, Header* header);

void _read(const char* path, char* buf);

#endif //__WRITE_H__