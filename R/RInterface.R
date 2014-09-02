#'@export
Write <- function(list_obj, dir_name) {
  saveRDS(attributes(list_obj), out.attr <- normalizePath(sprintf("%s/.attributes", dir_name)))
  ompWrite(list_obj, out <- normalizePath(paste(dir_name, seq_along(list_obj), sep="/"), mustWork = FALSE))
  attr(out, "attr") <- out.attr
  saveRDS(out, normalizePath(sprintf("%s/.metadata", dir_name)))
}

#'@export
Read <- function(dir_name) {
  out <- readRDS(normalizePath(sprintf("%s/.metadata")))
  list_obj <- ompRead(out)
  attributes(list_obj) <- readRDS(normalizePath(attr(out, "attr")))
  list_obj
}