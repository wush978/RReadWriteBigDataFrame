n <- 10^8
x <- list(
  numeric(n),
  logical(n),
  raw(n),
  integer(n)
  )

system.time(saveRDS(x, "test1"))
system.time(ompWrite(x, paste0("test2", 1:4)))
system.time(x2 <- readRDS("test1"))
system.time(x3 <- ompRead(paste0("test2", 1:4)))
