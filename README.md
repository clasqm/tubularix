# tubularix

**Description:** Tetris with a twist

[![tubularix.png](https://i.postimg.cc/HnhYxHt9/tubularix.png)](https://postimg.cc/9wy586KD)

Tubularix is a free opensource game similar to Tetris seen from a tubular perspective. Game's rules and behavior are very similar to Tetris.

Ported from Qt 4 to Qt 5 for Haiku (and RenkuOS), based on an abandoned SourceForge project 

**Packager's note**: I take no responsibility for any brain damage caused by this game!

**Requires:** QT5  
**Original Source:** http://tubularix.sourceforge.net/  
**License:** GNU GPL v3

## Building

Requires Qt 5 (Widgets and Network) and CMake:

```sh
mkdir build
cd build
cmake ..
make
```

The resulting `tubularix` binary can be run from the build directory.
`make clean` removes the generated files.

The translation files are compiled with `lrelease` (part of `qt5_tools`) into
the build directory; if `lrelease` is not available the pre-built `.qm` files
from `src/translations` are used instead.

See [src/README](src/README) for game controls and configuration details.
