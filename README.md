# peek

A simple C-based CLI utility to display file contents, similar to Unix `cat`.

## Overview

`peek` is a small, educational (for me) utility written in C that reads and prints the contents of files to stdout. It uses block-based reading for performance and handles errors like missing files without crashing. This project demonstrates basic C file I/O, CLI parsing, and memory handling.

---

## Features
- Display contents of one or multiple files
- Works with text and binary files
- Handles non-existent files gracefully
- Buffered reading for efficient output

---


## Build
```bash
make
```

---

## Usage
```bash
./peek <file1> <file2>... 
```
Example:
```bash
./peel file.txt
```
Output:
```bash
Hello from peek!
```

---

## Run tests
```bash
make test
```


# Future improvements
- Support for flags like `-n` (number lines), `-e` (show `$` at end of lines)

- Support reading from stdin (`./peek -`) and pipes (`echo "hello" | ./peek`)

- Configurable buffer size
