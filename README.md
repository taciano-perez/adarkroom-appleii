# A Dark Room - Apple II Port

This project is a port of the browser-based text adventure game [A Dark Room](https://github.com/doublespeakgames/adarkroom) to the Apple II platform, written in C using the **cc65** cross-compiler.

## Design & Architecture

Unlike the JavaScript original which is event-driven and runs in a browser DOM, this port runs on the bare metal (or DOS 3.3) of the MOS 6502 processor.

### Core Components
*   **Language:** C (C89 standard) via the `cc65` compiler.
*   **Input:** Non-blocking polling using `kbhit()` and `cgetc()` to allow real-time game loops (essential for the future "Space" module integration).
*   **Display:** 40-column text mode using the standard `conio.h` library. The DOM manipulation of the original is replaced by direct cursor positioning and buffer redraws.
*   **State Management:** The simplified `GameState` struct (in `game.h`) replaces the JSON-based `state_manager.js`. It uses fixed-width integers (`uint16_t`) instead of floating-point numbers for performance on the 8-bit CPU.

### File Structure
*   `main.c`: Contains the game loop, input handling, and timing logic.
*   `logic.c`: Implements the game rules (e.g., fire cooling, resource gathering).
*   `ui.c`: Handles screen rendering and the scrolling message log.
*   `game.h`: Shared data structures and function prototypes.

## Prerequisites & Installation

To build this project, you need **cc65**, a cross-development package for 6502 systems.

### Windows
1.  Download the Windows Snapshot (zip) from the [cc65 GitHub releases](https://sourceforge.net/projects/cc65/) or the [SourceForge page](https://sourceforge.net/projects/cc65/).
2.  Extract the zip file to a folder (e.g., `C:\cc65`).
3.  Add the `C:\cc65\bin` directory to your System PATH environment variable.
4.  Open a new terminal and type `cl65 --version` to verify.

### macOS
Using Homebrew:
```bash
brew install cc65
```

### Linux (Debian/Ubuntu)
```bash
sudo apt-get update
sudo apt-get install cc65
```

### Recommended Emulator
To run the resulting binary, you will need an Apple II emulator:
*   **Windows:** [AppleWin](https://github.com/AppleWin/AppleWin)
*   **macOS:** [Virtual II](https://www.virtualii.com/) or [LinApple](https://github.com/linappleii/linapple)
*   **Linux:** [LinApple](https://github.com/linappleii/linapple)

## Building the Game

1.  Open your terminal/command prompt.
2.  Navigate to this folder (`appleii-cc65`).
3.  Run `make` (or `nmake` on Windows if you have Visual Studio tools, otherwise you can run the compiler command manually).

**Manual Build Command:**
If you don't have `make` installed:
```bash
cl65 -t apple2 -o adarkroom main.c logic.c ui.c
```

This will produce a binary file named `adarkroom`.

## Running on an Emulator

The output file `adarkroom` is a raw binary executable. The standard Apple II DOS 3.3 expects this file to be on a disk image.

### Option A: Using AppleCommander (Recommended)
1.  Download [AppleCommander](https://github.com/AppleCommander/AppleCommander).
2.  Get a blank DOS 3.3 disk image (search for `blank_dos33.dsk`).
3.  Add the binary to the disk:
    ```bash
    java -jar ac.jar -p blank_dos33.dsk adarkroom B 0x803 < adarkroom
    ```
    *(Note: 0x803 is the default start address for cc65 programs).*
4.  Load `blank_dos33.dsk` in your emulator.
5.  At the BASIC prompt, type: `BRUN ADARKROOM`

### Option B: Quick Test (Virtual II / Some Emulators)
Some emulators allow you to strictly "Inject" a binary into memory and run it, but creating a disk image is the most reliable method for a persistent game.
