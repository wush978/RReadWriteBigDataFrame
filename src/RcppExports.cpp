// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// ompWrite
void ompWrite(List objs, CharacterVector paths);
RcppExport SEXP RReadWriteBigDataFrame_ompWrite(SEXP objsSEXP, SEXP pathsSEXP) {
BEGIN_RCPP
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< List >::type objs(objsSEXP );
        Rcpp::traits::input_parameter< CharacterVector >::type paths(pathsSEXP );
        ompWrite(objs, paths);
    }
    return R_NilValue;
END_RCPP
}
// ompRead
SEXP ompRead(CharacterVector paths);
RcppExport SEXP RReadWriteBigDataFrame_ompRead(SEXP pathsSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< CharacterVector >::type paths(pathsSEXP );
        SEXP __result = ompRead(paths);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// readSingle
SEXP readSingle(const std::string& path);
RcppExport SEXP RReadWriteBigDataFrame_readSingle(SEXP pathSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< const std::string& >::type path(pathSEXP );
        SEXP __result = readSingle(path);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
