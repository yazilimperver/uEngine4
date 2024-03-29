#!/bin/bash
git clone --single-branch --branch glew-cmake-release https://github.com/Perlmint/glew-cmake.git
cd glew-cmake
cmake ..
sudo cmake --install . --prefix /usr/local --config Debug
sudo cmake --install . --prefix /usr/local --config Release