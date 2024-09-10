# Mini_Shell_42
## Overview
This project is part of the 42 Network curriculum. The goal of Minishell is to create a simplified version of a Unix shell. You will implement essential shell functionalities such as command execution, redirections, pipes, signal handling, and built-in shell commands, providing a deeper understanding of how shells like Bash work.

Minishell is a collaborative project that introduces you to system calls, process management, file descriptors, and various aspects of how a shell functions.
## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Resources](#resources)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Interactive Prompt**: Presents a command-line prompt where users can input commands.
- **Command Execution**: Executes binary files by searching the system's `PATH` or using absolute paths.
- **Pipes (`|`)**: Handles inter-process communication using pipes.
- **Redirections (`<`, `>`, `>>`)**: Supports input/output redirection.
- **Environment Variables**: Expands and manages environment variables.
- **Signal Handling**: Captures signals (like `Ctrl+C`, `Ctrl+D`, `Ctrl+\`) for proper handling.
- **Built-in Commands**:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
  
## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/wadia05/Mini_Shell_42.git
