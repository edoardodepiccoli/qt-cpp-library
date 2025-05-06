# Clear previous outputs
clear

#!/bin/bash
set -e

# Create build and bin directories
mkdir -p build

# Move into build dir and run qmake referencing the .pro in root
cd build
qmake ../qt-library.pro

# Compile
make

# Move the built binary to bin/ if not already configured via DESTDIR
# Not needed if DESTDIR works correctly
