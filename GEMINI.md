# GEMINI.md - Context & Instructions

## Project: A Dark Room - Apple II Port

### Overview
This is a port of the text-based game "A Dark Room" to the Apple II platform, utilizing the **cc65** C cross-compiler. The game runs in 40-column text mode on DOS 3.3.

### Tech Stack & Tools
-   **Language:** C (C89 standard).
-   **Compiler:** `cc65` / `cl65`.
-   **Target:** Apple II (MOS 6502).
-   **Libraries:** Standard `conio.h` for screen I/O.
-   **Utilities:** `AppleCommander` (ac.jar) for disk image manipulation.

### Architecture
-   **`game.h`**: Defines `GameState` struct and constants (integers only, no floats). Shared across modules.
-   **`main.c`**: Contains `main()`, the infinite game loop, non-blocking input handling (`kbhit`, `cgetc`), and timing loop.
-   **`logic.c`**: Implements core mechanics (`game_tick`, `action_light_fire`, `action_stoke_fire`, etc.).
-   **`ui.c`**: Handles drawing the interface (`ui_draw`) and the scrolling message log (`ui_log`) using `gotoxy` and `cprintf`.

### Build & Run
1.  **Compile:** `cl65 -t apple2 -o adarkroom main.c logic.c ui.c` (or use `make` if available).
2.  **Disk Image:** Inject the binary into `blank_dos33.dsk` using `ac.jar`.
    ```bash
    java -jar ac.jar -p blank_dos33.dsk adarkroom B 0x803 < adarkroom
    ```
3.  **Run:** Launch the `.dsk` in an Apple II emulator (e.g., AppleWin, LinApple) and run `BRUN ADARKROOM`.

### Current State
-   **Implemented:**
    -   Basic game loop.
    -   Fire mechanics (lighting, stoking, cooling, dying).
    -   Wood gathering (simple increment).
    -   UI with status bar, scrolling log, and action menu.
-   **Conventions:**
    -   **Screen:** 40x24 text. Explicitly pad strings with spaces to clear previous text.
    -   **Input:** Non-blocking to allow background events (fire cooling).
    -   **Memory:** Optimize for 6502 (use `uint8_t`/`uint16_t`, avoid large buffers).

### Development Guidelines
-   **Adding Features:**
    1.  Update `GameState` in `game.h`.
    2.  Add logic in `logic.c`.
    3.  Update input handling in `main.c`.
    4.  Update display in `ui.c`.
-   **Performance:** Keep the main loop tight. Avoid heavy computation in `ui_draw` if possible, or only redraw when state changes.
