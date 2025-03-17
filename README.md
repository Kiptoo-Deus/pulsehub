# PulseHub

PulseHub is a system monitoring tool developed to showcase Rust and C++ integration, featuring a graphical user interface built with Dear ImGui, SDL2, and OpenGL. 

## Project Overview

PulseHub aims to be a portfolio-worthy demonstration of:
- **Rust-C++ Interoperability**: Rust for the UI, C++ for system-level logic.
- **GUI Development**: Dear ImGui with SDL2 and OpenGL for a modern interface.
- **System Monitoring**: Starting with CPU usage, expanding to memory and more.

## Features (Current)

- Displays "CPU Usage" in a Dear ImGui window.
- Built with SDL2 (`0.34.5`), ImGui (`0.11.0`), and OpenGL 3.3.
- Placeholder C++ backend, ready for real metrics.

## Prerequisites

- **Rust**: Install via [rustup](https://rustup.rs/).
- **CMake**: Download from [cmake.org](https://cmake.org/download/).
- **vcpkg**: Get from [vcpkg.io](https://vcpkg.io/) for SDL2.
- **MSVC**: Visual Studio 2022 (Community) with C++ build tools.
- **Git**: For cloning.

## Initial Setup

Clone the repo and set up SDL2:

```bash
git clone https://github.com/[YOUR_GITHUB_USERNAME]/pulsehub.git
cd pulsehub/pulsehub
cd C:\vcpkg
.\vcpkg install sdl2:x64-windows
.\vcpkg integrate install