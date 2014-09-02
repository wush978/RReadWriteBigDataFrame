n <- 10^8
x <- list(
  numeric(n),
  logical(n),
  raw(n),
  integer(n)
  )

system.time(saveRDS(x, "test1"))
Write(x, "test2")

system.time(saveRDS(x, "test1"))
system.time(Write(x, "test2"))
# system.time(x2 <- readRDS("test1"))
# system.time(x3 <- ompRead(paste0("test2", 1:4)))
