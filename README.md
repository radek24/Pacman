# Pacman

A modern implementation of the classic Pacman game, developed as part of the Introduction to Programming (UPR) course at VŠB-TUO (Technical University of Ostrava).

## Getting Started

### Quick Start

1. Clone the repository:
   ```bash
   gh repo clone radek24/Pacman
   cd pacman
   ```

2. Generate project files:
   - Run `GenerateProjectFiles.bat`
   - Select your preferred IDE when prompted
   - Open the generated project files in your chosen IDE
   - If you have any problems with building on linux look into CI/CD workflow

### Manual Setup

For unsoported project files or if you prefer manual configuration:

1. Navigate to the project directory
2. Run the appropriate Premake command for your project files
   ```bash
   premake5 [action]
   ```
   For available actions, consult the [Premake documentation](https://premake.github.io/docs/).

## Build Configurations

The project supports three build configurations:

| Configuration | Description                                          | Macro Defined    |
|--------------|------------------------------------------------------|-----------------|
| Debug        | Unoptimized build with full logging and debug info   | PAC_DEBUG      |
| Development  | Optimized build with logging for testing             | PAC_DEVELOPMENT|
| Shipping     | Fully optimized release build without logging        | PAC_SHIPPING    |

## CI / CD workflow
This project supports simple CI/CD workflow to check if projects compiles on linux (because noone will ever force me to use linux). You can look into `.github/workflows/main.yml` to check how it works.

## Development Environment

### Supported Project files
- **Visual Studio 2024** (Primary development IDE)
- **GNU Make** (gmake)

### Platform Support
While the project aims to be cross-platform, Windows is the primary development and testing platform. Other platforms may not have feature parity or could be broken idk.

## Dependencies

### External Libraries
- [SDL2](https://github.com/libsdl-org/SDL) - Graphics library
  - Used for rendering the game and loading fonts or images

- [rxi/log](https://github.com/rxi/log.c) - Logging library for C
  - Used for prettier logs that can also be outputed to a file

- [ClecioJung/ini](https://github.com/ClecioJung/ini) - Library for manipulating with .ini files
  - Used for saving and loading settings and leaderboards in .ini file format

---
Feel free to expore the code and build!
For questions or support, please open an issue in the repository.
