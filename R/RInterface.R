convert_s4 <- function(s4obj) {
  glue <- list()
  for(name in slotNames(s4obj)) {
    glue[[name]] <- slot(s4obj, name)
  }
  attr(glue, "class") <- class(s4obj)
  glue
}

#'@importFrom Rcpp evalCpp
#'@useDynLib RSaveBigObj
#'@export
Write <- function(list_obj, dir_name, overwrite = TRUE) {
  if (isS4(list_obj)) list_obj <- convert_s4(list_obj)
  if (overwrite) {
    if (file.exists(dir_name)) {
      file.remove(dir(dir_name, all.files = TRUE, full.names = TRUE, recursive = TRUE))
      file.remove(dir_name)
    }
  }
  tryCatch(dir.create(dir_name), warning = function(w) stop(conditionMessage(w)))
  saveRDS(attributes(list_obj), out.attr <- normalizePath(sprintf("%s/.attributes", dir_name), mustWork = FALSE))
  ompWrite(list_obj, out <- normalizePath(paste(dir_name, seq_along(list_obj), sep="/"), mustWork = FALSE))
  for(i in seq_along(list_obj)) {
    if (is.null(attributes(list_obj[[i]]))) next
    saveRDS(attributes(list_obj[[i]]), normalizePath(sprintf("%s/.attributes%d", dir_name, i), mustWork = FALSE))
  }
  attr(out, "attr") <- out.attr
  saveRDS(out, normalizePath(sprintf("%s/.metadata", dir_name), mustWork = FALSE))
}

#'@export
Read <- function(dir_name) {
  out <- readRDS(normalizePath(sprintf("%s/.metadata", dir_name), mustWork = FALSE))
  obj.attr <- readRDS(normalizePath(attr(out, "attr"), mustWork = FALSE))
#   if (!is.null(obj.attr$class$package)) library(obj.attr$class$package, character.only = TRUE)
  list_obj <- ompRead(out)
  for(i in seq_along(list_obj)) {
    if (file.exists(normalizePath(sprintf("%s/.attributes%d", dir_name, i), mustWork = FALSE))) {
      attributes(list_obj[[i]]) <- readRDS(normalizePath(sprintf("%s/.attributes%d", dir_name, i), mustWork = FALSE))
    }
  }
  attributes(list_obj) <- obj.attr
  list_obj
}