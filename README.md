<div align="center">
    <img src="assets/gomoku.png" width="300">
</div>

# Gomoku 🎮

_[Gomoku](https://en.wikipedia.org/wiki/Gomoku),_ also called Five in a Row is an an abstract strategy board game. The goal of this game is to exactly place five pieces in a row, horizontally, vertically or diagonally.

## Prerequisites

- `clang` as a **C** compiler (**GCC** is also file)

- `pkg-config` as it is being used to quickly include and link libraries

- `gtk+ 3.0` as it is the **GUI** library used in this project
  
  > If you happen to not have GTK+ 3.0, on Debian based distributions you can install it with `sudo apt install libgtk-3-dev`

## Installation

Suffice it to say... *make*

```bash
make
```

## Generating Docs

Make sure you have installed `doxygen`.
Once you do, run:
```bash
./docs.sh
```

## Usage

1. Open two Gomoku windows.

2. Choose a color in one of them

3. Click **Join Game** on the second one

4. Play 🎉
