#!/bin/bash

# Install Homebrew if it's not installed
if ! command -v brew &> /dev/null
then
    echo "Homebrew not found. Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

# Update Homebrew
echo "Updating Homebrew..."
brew update

# Install SDL, SDL_ttf, and SDL_image
echo "Installing SDL2, SDL2_ttf, and SDL2_image..."
brew install sdl2 sdl2_ttf sdl2_image

# Check if installation was successful
if brew list sdl2 &> /dev/null && brew list sdl2_ttf &> /dev/null && brew list sdl2_image &> /dev/null
then
    echo "SDL2, SDL2_ttf, and SDL2_image installed successfully."
else
    echo "Failed to install SDL2 libraries."
    exit 1
fi

# Run Premake to generate gmake2 project files
echo "Running Premake..."
Vendor/bin/premake/premake5 gmake2

# Check if Premake command was successful
if [ $? -eq 0 ]; then
    echo "Premake gmake2 files generated successfully."
else
    echo "Failed to run Premake."
    exit 1
fi

echo "Setup completed!"