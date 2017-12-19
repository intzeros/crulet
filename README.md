# Crulet
Crulet is a static analysis tool aimed at analysing C code based on rule checking (like Misra rules) and written by using Clang LibTooling.

### Usage

```shell
$ ./crulet test.c --
```

### Building from Sources

1. [Obtaining LLVM and Clang](http://clang.llvm.org/get_started.html).

```
cd ~
git clone http://llvm.org/git/llvm.git
cd llvm/tools
git clone http://llvm.org/git/clang.git
cd clang/tools
git clone http://llvm.org/git/clang-tools-extra.git extra
cd ~/llvm
mkdir build && cd build
cmake -G "Unix Makefiles" ../
make
```

2. Building Crulet.

```
cd ~/llvm/tools/clang/tools/extra
git clone https://github.com/lszero/crulet.git
echo 'add_subdirectory(crulet)' >> tools/extra/CMakeLists.txt
cd ~/llvm/build
cmake -G "Unix Makefiles" ../
make crulet
```

