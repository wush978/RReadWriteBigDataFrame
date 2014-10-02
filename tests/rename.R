library(RReadWriteBigDataFrame)
Write(iris, "test2", TRUE)
if (file.exists("test22")) {
  file.remove(dir("test22", all.files = TRUE, full.names = TRUE, recursive = TRUE))
  file.remove("test22")
}
file.rename("test2", "test22")
iris2 <- Read("test22")
stopifnot(isTRUE(all.equal(iris, iris2)))