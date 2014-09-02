n <- 10^8
x <- list(
  numeric(n),
  logical(n),
  raw(n),
  integer(n)
  )

system.time(saveRDS(x, "test1"))
system.time(Write(x, "test2"))

system.time(r1 <- readRDS("test1"))
system.time(r2 <- Read(dir_name = "test2"))
all.equal(r1, r2)
