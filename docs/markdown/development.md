# Development

## CMake tutorials

```
Compilation process: 
1 - *.cpp/*.h (source)=> *.i (preprocessed)=> *.s (assembly) => *.o (machine code)=> *.a/*.so (libraries, machine code)=> *.exe (executable, machine code)
2 - Compiler needs include-directories where to look for the includes => (-Idir)
3 - Linker needs the library-paths where to look for the libraries => (-Ldir)
4 - Linker needs the library name "libxxx.a" => (-lxxx)  
Tools: cpp / g++ -E, gcc -S / g++ -S, as, ld
Utilities: file (File Type), nm (Symbol Table), ldd (Dynamic-Link)
https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html

Note: 
- Headers should not be fed to the compiler unless they contain active code (macros or templates)

Tutorial:
https://medium.com/@onur.dundar1/cmake-tutorial-585dd180109b

Coding style:
https://community.kde.org/Policies/CMake_Coding_Style

Environment variables:
https://cmake.org/cmake/help/latest/manual/cmake-env-variables.7.html

Short tutorial: (Series: 1,2,3)
https://medium.com/heuristics/c-application-development-part-1-project-structure-454b00f9eddc
```

## Requirements

Use the conda environment, or install these additional packages:

```
sudo apt-get install -y doxygen
pip install sphinx
pip install sphinx_rtd_theme
pip install breathe
```

## Documentation

### Doxygen

```
cd docs/doxygen
doxygen
```

### Sphinx

```
cd docs/source
make clean; make html
```

## Badges tool

Generated using: [shields.io](https://shields.io/)

## Compute sha256

```
# MacOS
shasum -a 256 <file>
openssl dgst -sha256 <file>

# Linux
sha256sum <file>
```

## Test Brew formulas

Drop the `formulas/brew/eddl.rb` file at `/usr/local/Homebrew/Library/Taps/homebrew/homebrew-core/Formula/`, and the run `brew install eddl`
Then you can also execute; `brew`


## Build conda package

```
cd formulas/conda/eddl
conda build .

# Test installation
conda activate
conda install --use-local eddl

# Test cpp example
# rm -rf ./*; cmake ..; make; ./main
cmake ..; make; ./main

# Convert to platforms
conda convert --platform all ... -o ~/precompiled

# Upload
anaconda upload ~/anaconda3/conda-bld/...

# Upload all
find ~/precompiled -name "*.bz2" -type f -exec anaconda upload "{}" \;
```

## Install protobuf on MacOS from source

```
brew install autoconf && brew install automake
(donwload repo: https://github.com/protocolbuffers/protobuf/releases)
cd protobuf/
./autogen.sh && ./configure && make
sudo make install
```