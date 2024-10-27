# Pacman

A modern implementation of the classic Pacman game, developed as part of the Introduction to Programming (UPR) course at VŠB-TUO (Technical University of Ostrava).


## Prerequisites

- Windows OS (primary development platform)
- Visual Studio 2022 or GNU Make
- Premake5 (included in the repository)

## Getting Started

### Quick Start

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/pacman.git
   cd pacman
   ```

2. Generate project files:
   - Run `GenerateProjectFiles.bat`
   - Select your preferred IDE when prompted
   - Open the generated project files in your chosen IDE

### Manual Setup

For platforms other than Windows or if you prefer manual configuration:

1. Navigate to the project directory
2. Run the appropriate Premake command for your platform
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

## Development Environment

### Supported IDEs
- **Visual Studio 2022** (Primary development IDE)
- **GNU Make** (gmake)

### Platform Support
While the project aims to be cross-platform, Windows is the primary development and testing platform. Other platforms may require additional configuration or modifications.

## Dependencies

### External Libraries
- [SDL2](https://github.com/libsdl-org/SDL) - Graphics library
  - Used for rendering the game and loading fonts or images

- [rxi/log](https://github.com/rxi/log.c) - A feature-rich logging library for C
  - Used for enhanced logging capabilities
  - Included as a submodule in the project

---
Feel free to expore the code and build!
For questions or support, please open an issue in the repository.
