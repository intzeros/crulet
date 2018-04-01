# Crulet
Crulet is a static analysis tool aimed at analysing C/C++ code based on rule checking (like Misra rules) and written by using Clang LibTooling.

### Usage

```shell
$ ./crulet -help
$ ./crulet test.c --

# enable or disable checkers
$ ./crulet -check="*,-GJB-rule-3.1.3" test.c --

# for project with compile_commands.json
$ ./run-crulet.py -d report_dir

# create HTML bug report files
$ ./html-bug-report-writer.py -d report_dir
```

### Bug Report

HTML report demo:

<img src="https://github.com/lszero/crulet/blob/master/img/demo1.png" height = "400" align=center />

### Building from Sources

1. [Obtain LLVM and Clang](http://clang.llvm.org/get_started.html).

(a) Check out LLVM:

```
cd ~
wget http://releases.llvm.org/5.0.0/llvm-5.0.0.src.tar.xz
tar -xJf llvm-5.0.0.src.tar.xz
mv llvm-5.0.0.src llvm-5.0.0
```

(b) Check out Clang:

```
wget http://releases.llvm.org/5.0.0/cfe-5.0.0.src.tar.xz
tar -xJf cfe-5.0.0.src.tar.xz -C llvm-5.0.0/tools/
mv llvm-5.0.0/tools/cfe-5.0.0.src/ llvm-5.0.0/tools/clang
```

(c) Check out Extra Clang Tools:

```
wget http://releases.llvm.org/5.0.0/clang-tools-extra-5.0.0.src.tar.xz
tar -xJf clang-tools-extra-5.0.0.src.tar.xz -C llvm-5.0.0/tools/clang/tools/
mv llvm-5.0.0/tools/clang/tools/clang-tools-extra-5.0.0.src/ llvm-5.0.0/tools/clang/tools/extra
```

2. Obtain and build Crulet.

```
git clone https://github.com/lszero/crulet.git
cd ~/llvm-5.0.0/tools/clang/tools/extra
mkdir crulet && cp -r ~/crulet/src/* ./crulet
echo 'add_subdirectory(crulet)' >> CMakeLists.txt
cd ~/llvm-5.0.0
mkdir build && cd build
cmake -G "Unix Makefiles" ../
make crulet
```

