### DEPENDENCIES:
- SDL2
- SDL2_Image
- SDL2_TTF
### BUILD:

------------

CMake: 
1. Download dependencies
2. Download cmake and make
3. Clone source code from github
4. Create build folder
5. Run CMake script
6. Run generated Make script and run the project

##### *Example:*
1. `sudo pacman -S sdl2-compat sdl2_image sdl2_ttf `

2. `sudo pacman -S cmake make`

3. `git clone https://github.com/Upsidedrop/Swipe-Visual-Coding.git`

4. `cd Swipe-Visual-Coding && mkdir build`

5. `cd build && cmake ..`

6. `make && cd .. && ./build/Swipe`

------------

#### Common package names:

Apt:
- apt-get install libsdl2-dev
- apt-get install libsdl2-image-dev
- apt-get install libsdl2-ttf-dev

Pacman:
- sudo pacman -S sdl2-compat
- sudo pacman -S sdl2_image
- sudo pacman -S sdl2_ttf

Yum:
- yum install SDL2-devel
- yum install SDL2_image-devel
- yum install SDL2_ttf-devel