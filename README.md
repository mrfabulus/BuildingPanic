Building Panic
=====================

Requirements
------------

* CMake
* Compiler that supports C++14 (recent version of `g++` or `clang++`)
* SDL2
* ninja (or `make`, just drop the `-GNinja` flag and build with `make`)

Original homepages
------------------
Yamada's old page:

https://translate.google.com/translate?sl=ja&tl=en&js=y&prev=_t&hl=en&ie=UTF-8&u=https%3A%2F%2Fweb.archive.org%2Fweb%2F20040825185032%2Fvillage.infoweb.ne.jp%2F%7Eyamaana%2F&edit-text=&act=url

Yamada's new page:

https://translate.google.com/translate?hl=en&sl=ja&tl=en&u=https%3A%2F%2Fweb.archive.org%2Fweb%2F20161103150542%2Fhttp%3A%2F%2Fhomepage3.nifty.com%2Fyamaana%2Flib_%2Flibrary.htm

One way of building with C++14, SDL2, CMake and ninja
-----------------------------------------------------

    mkdir -p build
    cd build
    cmake -GNinja ..
    ninja
    cd ..

Running
-------

    build/main

Cleaning up the binary file and build directory
-----------------------------------------------

    rm -rf build/

