# Cactus

Cactus is a software 3D rendering library written in clean C/C++ and is a port of Peter Walser's idx3dIII engine in Java (currently nowhere to be found on the internet...). Although it is outperformed by 3D hardware of today, it is a nice project to learn 3D principles from.

## Building for WebAssembly

[Install EMCC](https://emscripten.org/docs/getting_started/downloads.html), tl;dr:

````sh
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
git pull
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
````

Then, to build:

````sh
emcc -DCACTUS_API="" -DNO_LWO_IMPORTER -D__CACTUS_FPUTWEAK src/*.cpp -O3 ./main.cpp -o index.html
````