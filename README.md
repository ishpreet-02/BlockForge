# BlockForge

A terminal-based Tetris-style game written in C, using a modular game engine and POSIX terminal APIs for Linux and WSL.

Players arrange falling Tetrominoes on a 20 × 10 board, clear horizontal lines, and earn points. The current implementation includes movement, rotation, automatic gravity, a 7-bag piece randomizer, line clearing, and scoring. It is a playable development version; game-over detection is still planned.

## Project Proposal

### Problem Statement and Motivation

An interactive terminal game must coordinate keyboard input, timing, rendering, and changes to shared game state without waiting indefinitely for user input. BlockForge explores this problem through a falling-block puzzle whose rules are simple to explain but require careful implementation.

The project follows the journey of a Tetromino: generation, spawning, movement, collision checking, locking, and line clearing. Each stage introduces a concrete programming problem, from representing shapes in arrays to updating a board without losing existing blocks.

### Goals

1. Build a Tetris-style game whose implementation is entirely in C.
2. Separate responsibilities into modules with clear header interfaces.
3. Represent the board and pieces using arrays, structures, and enumerations.
4. Prevent invalid movement and rotation through collision detection.
5. Combine keyboard input with time-based gravity.
6. Generate pieces using a shuffled 7-bag randomizer.
7. Detect completed rows, shift remaining rows, and calculate scores.
8. Produce a documented repository suitable for demonstrating design decisions and implementation skills in interviews.

### Specifications

| Area | Specification |
| --- | --- |
| Language | C11 |
| Target environment | Linux or a Linux distribution running in WSL |
| Interface | Interactive terminal with ANSI escape-sequence support |
| Board | 20 rows × 10 columns; integer cells represent empty or occupied positions |
| Pieces | I, O, T, S, Z, J, and L, each stored in a 4 × 4 matrix |
| Generation | One of each piece per bag, shuffled using Fisher–Yates |
| Spawn position | Matrix origin at column 3, row 0, using zero-based coordinates |
| Movement | Left, right, and downward movement, subject to collision checks |
| Rotation | 90 degrees clockwise; rejected on collision; O piece stays unchanged |
| Gravity | One downward movement attempt every 500 milliseconds |
| Input | Character input with a `select()` timeout of up to 50 milliseconds |
| Locking | A failed downward move stores the active piece in the board |
| Line clearing | Full rows are removed and rows above them shift downward |
| Scoring | 100, 300, 500, or 800 points for clearing 1, 2, 3, or 4 lines together |
| Dependencies | C/POSIX APIs; no external game or graphics libraries |

### Design and Architecture

`main.c` starts the game, runs it, and invokes shutdown. `game.c` coordinates the other modules and owns the active piece during the game loop.

| Module | Responsibility |
| --- | --- |
| `main.c` | Application entry point and lifecycle |
| `game.c` | Initialization, game loop, input dispatch, gravity, and scoring integration |
| `board.c` | Board storage, rendering, piece locking, line clearing, and screen management |
| `piece.c` | Shape definitions, bag randomization, spawning, movement, and rotation |
| `collision.c` | Boundary and occupied-cell collision checks |
| `input.c` | Terminal input configuration, polling, and restoration |
| `score.c` | Current score and total cleared-line count |

The board stores locked blocks. Rendering overlays the active piece without writing it into the board. Movement and rotation apply a tentative change, check for collisions, and restore the previous state when the change is invalid.

The game proceeds through these steps:

1. Reset the board, piece generator, and score.
2. Create and spawn the first piece; configure terminal input and the alternate screen.
3. Render the board, score, and cleared-line count.
4. Read a key and apply the corresponding action.
5. Attempt a gravity step when the interval expires.
6. After a failed downward move, lock the piece, clear completed rows, update the score, and spawn another piece.
7. Repeat until the player presses `q`, then restore input settings and leave the alternate screen.

## Repository Layout

```text
BlockForge/
├── include/          # Public module headers (.h)
├── src/              # C implementation files (.c)
├── .gitignore        # Generated files and local configuration exclusions
├── LICENSE           # MIT license
├── Makefile          # Build automation
└── README.md         # Project proposal and usage documentation
```

The generated `blockforge` executable is a local build output and is ignored by Git.

## Prerequisites

- Linux or WSL with a Linux distribution.
- GCC with C11 support and POSIX headers.
- GNU Make.
- An interactive terminal supporting ANSI escape sequences; allow approximately 30 rows for the board, score, and controls.
- Git, if cloning the repository.

On Windows, run the build and game inside WSL. Native Windows compilation is not supported by the current terminal implementation.

## Build and Run

1. Clone the repository using its GitHub clone URL, or download and extract its source. Open a terminal in the `BlockForge` directory.
2. Compile the game:

   ```sh
   make
   ```

3. Start the game in the same terminal:

   ```sh
   ./blockforge
   ```

4. Press `q` to exit. To remove the generated executable:

   ```sh
   make clean
   ```

The Makefile compiles all seven source files with warnings enabled, C11 mode, POSIX feature definitions, and the `include/` header path. After changing a header, use `make clean` followed by `make`, since the current Makefile does not track header dependencies.

## Controls and Scoring

Use lowercase keys; pressing Enter is not required.

| Key | Action |
| --- | --- |
| `a` | Move left |
| `d` | Move right |
| `w` | Rotate clockwise |
| `s` | Move down one row; lock if downward movement is blocked |
| `q` | Quit and restore the terminal |

Pieces also fall automatically. `#` represents occupied cells, including the active piece; `.` represents empty cells. Score and total cleared lines appear above the board.

| Lines cleared in one locking event | Points earned |
| --- | --- |
| 1 | 100 |
| 2 | 300 |
| 3 | 500 |
| 4 | 800 |

For example, clearing two rows together adds 300 points and increases the line count by two. Movement and soft drops do not award points. Both manual locking and gravity locking update the score.

## Milestones and Current Status

These milestones describe implementation progress; submission dates and instructor-specific milestone criteria have not been supplied.

| Milestone | Deliverable | Status |
| --- | --- | --- |
| 1 | Project structure, entry point, and board representation | Implemented |
| 2 | Piece spawning, rendering, movement, and collision detection | Implemented |
| 3 | Piece locking, automatic gravity, and rotation | Implemented |
| 4 | Seven Tetrominoes and 7-bag randomization | Implemented |
| 5 | Line clearing, scoring, and score display | Implemented |
| 6 | README proposal, build instructions, ignore rules, and license | Included |
| 7 | Game-over detection, terminal cleanup improvements, and gameplay validation | Planned |

## Known Limitations and Planned Improvements

- Spawn collisions do not end the game yet. When the board fills to the spawn area, pieces can overlap existing blocks.
- Rotation has no wall kicks and uses the full 4 × 4 matrix as its rotation frame.
- Gravity stays at a fixed speed; levels, pause, hard drop, hold, and next-piece preview are not implemented.
- Manual locking does not reset the gravity timer, so a newly spawned piece may fall immediately.
- `q` restores terminal settings. The Ctrl+C handler restores the screen but currently skips input-setting restoration. If the terminal is left without echo or normal input, run `stty sane`.
- Terminal API errors are not handled comprehensively, and no automated test suite is included yet.

## Development and Repository Practices

- Keep `.c` files in `src/` and public `.h` files in `include/`. Add new source files to the Makefile.
- Exclude executables, object files, build directories, IDE settings, and OS metadata using `.gitignore`.
- Keep credentials and private configuration out of source control. Before a commit, inspect `git status`, `git diff --cached`, and `git diff --cached --check`. Ignore rules do not protect files that are already tracked.
- Make focused commits for individual changes. Use messages that explain the behavior or purpose, such as `Add game-over detection when the spawn position is blocked`.
- Build and validate affected behavior before committing. Check movement at boundaries, rejected rotations, consecutive line clearing, score updates, and normal terminal restoration when those areas change.

The repository history records incremental implementation of movement, collision detection, locking, gravity, rotation, randomization, line clearing, and scoring. Keep this approach as development continues.

## License

BlockForge is distributed under the [MIT License](LICENSE).
