
Use Linux for building, or WSL if on Windows.
1. Follow these instructions to install devkitpro: https://devkitpro.org/wiki/Getting_Started
2. Install the switch-dev tools with `sudo dkp-pacman -S switch-dev`
3. make sure your devkitpro tool chain is updated with `sudo dkp-pacman -Syu`
4. `git clone` this project and run `git submodule update --init --recursive` to clone submodules
5. run `make`
