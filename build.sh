#!/usr/bin/env bash
set -e

# Build script for the Tic-Tac-Toe project (native Linux build).
# Needs the Linux SDL2 dev packages (not the mingw-w64 libs under lib/,
# which are Windows-only): sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev

cd "$(dirname "${BASH_SOURCE[0]}")"

CXX=g++
OUT=tictactoe

for h in SDL2/SDL.h SDL2/SDL_image.h SDL2/SDL_ttf.h; do
    if ! echo "#include <$h>" | "$CXX" -E - >/dev/null 2>&1; then
        echo "error: $h not found." >&2
        echo "Install the SDL2 dev packages, e.g.:" >&2
        echo "    sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev" >&2
        exit 1
    fi
done

SOURCES=(
    src/ui/text.cpp
    src/ui/buttons.cpp
    src/ui/dialogBox.cpp
    src/ui/menu.cpp
    src/Play/play.cpp
    src/Play/board.cpp
    src/Play/ai.cpp
    src/ui/main.cpp
    src/Play/check_win.cpp
)

LIBS=(-lSDL2 -lSDL2_image -lSDL2_ttf)

echo "Compiling ${#SOURCES[@]} source files -> $OUT"
"$CXX" -std=c++17 -o "$OUT" "${SOURCES[@]}" "${LIBS[@]}"

echo "Built ./$OUT"

./tictactoe