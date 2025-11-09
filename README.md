# pipex

Reimplementation of a simple Unix shell pipeline in C. Given an input file, two or more commands, and an output file, `pipex` connects the commands with pipes (like the shell `|`) and redirects input/output to mimic behavior such as:
```
< infile cmd1 | cmd2 > outfile
```
Bonus includes support for `here_doc` and multiple commands.

## Table of contents
- Overview
- Features
- Build
- Usage
  - Mandatory
  - Bonus (here_doc, multi-cmd)
- Examples
- Project structure
- Implementation notes
- Error handling
- Compatibility

## Overview

`pipex` demonstrates core Unix process and IPC concepts:
- creating pipes to connect processes
- `fork`/`execve` to spawn and run commands
- `dup2` to redirect stdin/stdout
- resolving executables via `PATH`
- robust error propagation and exit statuses

## Features

- Mandatory:
  - Two-command pipeline: `infile "cmd1" "cmd2" outfile`
  - Input redirection from `infile`, output redirection to `outfile`
  - PATH lookup for commands and argument parsing

- Bonus:
  - `here_doc LIMITER cmd1 cmd2 ... outfile`
  - Multiple commands chained with pipes: `infile cmd1 cmd2 ... cmdN outfile`
  - Proper handling of temporary here-doc input

## Build

Requirements:
- A POSIX-like environment (Linux or macOS)
- `make` and a C compiler (e.g., `cc`/`gcc`)
- The project may use a local `libft` for utility functions.

Targets:
```
make        # build mandatory part
make bonus  # build bonus
make clean  # remove objects
make fclean # remove objects and binaries
make re     # full rebuild
```

## Usage

After building, you will get a binary (often named `pipex`).

### Mandatory
```
./pipex infile "cmd1 [args...]" "cmd2 [args...]" outfile
```
Equivalent to:
```
< infile cmd1 | cmd2 > outfile
```

- `infile` must be readable.
- `outfile` is created/truncated.
- Commands are searched in `PATH` unless given with an absolute/relative path.

### Bonus (here_doc and multi-cmd)
```
./pipex here_doc LIMITER "cmd1 [args...]" "cmd2 [args...]" ... "cmdN [args...]" outfile
```
Equivalent to:
```
<< LIMITER cmd1 | cmd2 | ... | cmdN >> outfile
```
- `here_doc` reads from stdin until a line exactly matching `LIMITER`.
- `outfile` is opened in append mode for `here_doc`.

Or multi-cmd with infile:
```
./pipex infile "cmd1" "cmd2" ... "cmdN" outfile
```

## Examples

- Mandatory:
```
./pipex input.txt "grep hello" "wc -l" output.txt
# Roughly: < input.txt grep hello | wc -l > output.txt
```

- Bonus: here_doc
```
./pipex here_doc EOF "cat -e" "wc -l" out.txt
# Then type lines; finish by entering EOF on its own line.
```

- Bonus: multiple commands
```
./pipex input.txt "tr a-z A-Z" "sed s/FOO/BAR/g" "wc -w" out.txt
```

## Project structure

- `src/` — core source files for the mandatory part
- `bonus/` — bonus-specific sources (here_doc, multi-cmd)
- `includes/` — headers
- `libft/` — optional utility library (if used)
- `Makefile` — build targets and rules

## Implementation notes

Typical syscalls and library functions:
- Process & IPC: `pipe`, `fork`, `execve`, `wait`, `waitpid`
- FD management: `dup`, `dup2`, `close`
- Files & errors: `open`, `perror`, `strerror`, `access`
- Memory & utils: `malloc`, `free`

Key steps:
1. Parse arguments and detect `here_doc` mode.
2. Instead of allocating all pipes up front, create them lazily as you walk the command list: for every command that is not the last, open a new pipe and direct the child’s output into its write end; when you reach the final command, bypass pipe creation and connect its output directly to the outfile (opened in truncate or append mode depending on `here_doc`).
3. For each command:
   - `fork` a child
   - Set up stdin/stdout with `dup2` from the appropriate pipe ends or files
   - Resolve the executable using `PATH`
   - `execve` the command
4. In the parent, close all pipe FDs and `wait` for children.
5. Propagate exit status appropriately.

## Error handling

- Descriptive messages via `perror`/custom errors
- Non-zero exit on failures (open/pipe/fork/execve/path lookup)
- Proper cleanup of file descriptors and allocated memory

## Compatibility

- Tested on Linux/macOS (behavior should be POSIX-compliant)
- Requires a functional `PATH` for command resolution unless absolute paths are used
