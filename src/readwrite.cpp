#include <memory>
#include <fstream>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include "readwrite.h"

void _write(const char* path, Header* header, const char* buf) {
  std::ofstream f(path, std::ios_base::out | std::ios_base::binary);
  f << header->type << "," << header->size << "," << header->element_size << ",";
  boost::iostreams::filtering_streambuf<boost::iostreams::output> out;
  out.push(boost::iostreams::gzip_compressor());
  out.push(f);
  boost::iostreams::copy(boost::iostreams::array_source(buf, header->size * header->element_size), out);
  boost::iostreams::close(out);
}

void _readHeader(const char* path, Header* header) {
  char temp;
  std::ifstream f(path, std::ios_base::in | std::ios_base::binary);
  f >> header->type >> temp >> header->size >> temp >> header->element_size >> temp;
  f.close();
}

void _read(const char* path, char* buf) {
  char temp;
  std::auto_ptr<Header> header(new Header());
  std::ifstream f(path, std::ios_base::in | std::ios_base::binary);
  f >> header->type >> temp >> header->size >> temp >> header->element_size >> temp;
  boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
  in.push(boost::iostreams::gzip_decompressor());
  in.push(f);
  boost::iostreams::copy(in, boost::iostreams::array_sink(buf, header->size * header->element_size));
}