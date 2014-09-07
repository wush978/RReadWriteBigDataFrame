#include <cerrno>
#include <memory>
#include <fstream>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <Rcpp.h>

using namespace Rcpp;

struct Header {
  SEXPTYPE type;
  size_t size;
  short element_size;
};

//'@export
//[[Rcpp::export]]
SEXP readSingle(const std::string& path) {
  char temp;
  std::ifstream f(path.c_str(), std::ios_base::in | std::ios_base::binary);
  if (!f) {
    throw new std::runtime_error(strerror(errno));
  }
  Header header;
  f >> header.type >> temp >> header.size >> temp >> header.element_size >> temp;
  if (!f) {
    throw new std::runtime_error(strerror(errno));
  }
  std::auto_ptr<RObject> r(NULL);
  switch(header.type) {
    case LGLSXP:
      r.reset(new RObject(wrap(LogicalVector(header.size))));
      break;
    case INTSXP:
      r.reset(new RObject(wrap(IntegerVector(header.size))));
      break;
    case REALSXP:
      r.reset(new RObject(wrap(NumericVector(header.size))));
      break;
    case RAWSXP:
      r.reset(new RObject(wrap(RawVector(header.size))));
      break;
    case STRSXP:
    default:
      throw std::logic_error("Not Supported Type!");
  }
  char* buf = reinterpret_cast<char*>(dataptr(wrap(*r)));
  boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
  in.push(boost::iostreams::gzip_decompressor());
  in.push(f);
  boost::iostreams::copy(in, boost::iostreams::array_sink(buf, header.size * header.element_size));
  return wrap(*r);
}