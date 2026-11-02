# tubularix

Tetris with a twist.

Ported from Qt 4 to Qt 5 for Haiku (and RenkuOS), based on the abandoned
SourceForge project <https://sourceforge.net/projects/tubularix/>.

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

## Haiku notes

Qt 5 on Haiku is packaged as `qt5`, `qt5_devel`, `qt5_tools`, `qt5_script` and
`qt5_script_devel`. Settings and high scores are stored through `QSettings`
in `~/config/settings/tubularix/`. If you install the game by hand, put the
compiled translations in `~/config/non-packaged/data/tubularix/`.

See [src/README](src/README) for game controls and configuration details.
