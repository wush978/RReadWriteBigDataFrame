#include <memory>
#include <Rcpp.h>
#include "readwrite.h"

using namespace Rcpp;

template<typename ElementType>
void write(Header* header, SEXP obj, const char* path) {
  header->size = Rf_length(obj);
  header->element_size = sizeof(ElementType);
  _write(path, header, reinterpret_cast<char*>(dataptr(obj)));
}

void ompWrite(SEXP obj, const char* path) {
  std::auto_ptr<Header> header(new Header());
  header->type = TYPEOF(obj);
  switch(TYPEOF(obj)) {
    case LGLSXP:
    case INTSXP:
      write<int>(header.get(), obj, path);
      break;
    case REALSXP:
      write<double>(header.get(), obj, path);
      break;
    case RAWSXP:
      write<Rbyte>(header.get(), obj, path);
      break;
    case STRSXP:
    default:
      throw std::logic_error("Not Supported Type!");
  }
  
}

//[[Rcpp::export]]
void ompWrite(List objs, CharacterVector paths) {
  if (objs.size() != paths.size()) throw std::invalid_argument("Inconsistent Size!");
  SEXP ppaths = wrap(paths);
  #pragma omp parallel for
  for(int i = 0;i < objs.size();i++) {
    ompWrite(wrap(objs[i]), CHAR(STRING_ELT(ppaths, i)));
  }
}

template<int RTYPE>
void read(Header* header, List& objs, const char* path, const int i) {
  std::auto_ptr< Vector<RTYPE> > p(NULL);
  #pragma omp critical
  {
    p.reset(new Vector<RTYPE>(header->size));
  }
  _read(path, reinterpret_cast<char*>(dataptr(wrap(*p))));
  #pragma omp critical
  {
    objs[i] = *p;
  }
}

//[[Rcpp::export]]
SEXP ompRead(CharacterVector paths) {
  List objs(paths.size());
  SEXP ppath = wrap(paths);
  #pragma omp parallel for
  for(int i = 0;i < paths.size();i++) {
    const char* path = CHAR(STRING_ELT(ppath, i));
    std::auto_ptr<Header> header(new Header());
    _readHeader(path, header.get());
    switch(header->type) {
      case LGLSXP:
        read<LGLSXP>(header.get(), objs, path, i); 
        break;
      case INTSXP:
        read<INTSXP>(header.get(), objs, path, i); 
        break;
      case REALSXP:
        read<REALSXP>(header.get(), objs, path, i); 
        break;
      case RAWSXP:
        read<RAWSXP>(header.get(), objs, path, i); 
        break;
      case STRSXP:
      default:
        throw std::logic_error("Not Supported Type!");
    }
  }
  return objs;
}