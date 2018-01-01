# Crulet
Crulet is a static analysis tool aimed at analysing C code based on rule checking (like Misra rules) and written by using Clang LibTooling.

### Usage

```shell
$ ./crulet -help
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
cd ~
git clone https://github.com/lszero/crulet.git
cd ~/llvm/tools/clang/tools/extra
mkdir crulet && cp -r ~/crulet/src/* ./crulet
echo 'add_subdirectory(crulet)' >> CMakeLists.txt
cd ~/llvm/build
cmake -G "Unix Makefiles" ../
make crulet
```

