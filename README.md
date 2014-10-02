# Read and Write Big List, Data Frame and S4 Object

- Column-based Serialization
- Faster IO spead due to openmp parallization and comprression


```r
library(RReadWriteBigDataFrame)
```

```
## Loading required package: methods
```

```r
n <- 10^8
x <- list(
  numeric(n),
  logical(n),
  raw(n),
  integer(n)
  )
print("saveRDS")
```

```
## [1] "saveRDS"
```

```r
system.time(saveRDS(x, "test1"))
```

```
##    user  system elapsed 
##  12.465   0.014  12.467
```

```r
print("Write")
```

```
## [1] "Write"
```

```r
system.time(Write(x, "test2"))
```

```
##    user  system elapsed 
##  10.292   0.017   4.425
```

```r
print("readRDS")
```

```
## [1] "readRDS"
```

```r
system.time(r1 <- readRDS("test1"))
```

```
##    user  system elapsed 
##   5.266   0.096   5.356
```

```r
print("Read")
```

```
## [1] "Read"
```

```r
system.time(r2 <- Read(dir_name = "test2"))
```

```
##    user  system elapsed 
##   4.998   0.106   2.257
```

```r
all.equal(r1, r2)
```

```
## [1] TRUE
```

- Not support to `CharacterVector`
