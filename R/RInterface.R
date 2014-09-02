#'@importFrom Rcpp evalCpp
#'@useDynLib RSaveBigObj
#'@export
Write <- function(list_obj, dir_name) {
  tryCatch(dir.create(dir_name), warning = function(w) stop(conditionMessage(w)))
  saveRDS(attributes(list_obj), out.attr <- normalizePath(sprintf("%s/.attributes", dir_name), mustWork = FALSE))
  ompWrite(list_obj, out <- normalizePath(paste(dir_name, seq_along(list_obj), sep="/"), mustWork = FALSE))
  for(i in seq_along(list_obj)) {
    if (is.null(attributes(list_obj))) next
    saveRDS(attributes(list_obj), normalizePath(sprintf("%s/.attributes%d", dir_name, i), mustWork = FALSE))
  }
  attr(out, "attr") <- out.attr
  saveRDS(out, normalizePath(sprintf("%s/.metadata", dir_name), mustWork = FALSE))
}

#'@export
Read <- function(dir_name) {
  out <- readRDS(normalizePath(sprintf("%s/.metadata", dir_name), mustWork = FALSE))
  list_obj <- ompRead(out)
  for(i in seq_along(list_obj)) {
    if (file.exists(normalizePath(sprintf("%s/.attributes%d", dir_name, i), mustWork = FALSE))) {
      attributes(list_obj[[i]]) <- readRDS(normalizePath(sprintf("%s/.attributes%d", dir_name, i), mustWork = FALSE))
    }
  }
  attributes(list_obj) <- readRDS(normalizePath(attr(out, "attr"), mustWork = FALSE))
  list_obj
}