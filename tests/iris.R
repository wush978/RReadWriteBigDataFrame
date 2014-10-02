library(RReadWriteBigDataFrame)
Write(iris, "test2", TRUE)
iris2 <- Read("test2")
stopifnot(isTRUE(all.equal(iris, iris2)))
