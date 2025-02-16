# BigIneger library
__Dependencies:__
* git 
* GTest

## Build BigInteger
```bash
mkdir build
cmake ..
make --jobs=$(nproc --all)
```

## Test BigInteger

To build and run tests, add the `-DENABLE_TESTS=ON` flag when building.
