# Getting Started:
Hello and welcome to the Lazarus Project. \

Before jumping into the project, make sure the following libraries / tools are accessible on your machine:
- gcc (compiler)
- gdb (debugger)
- valgrind (debugger)
- GL/gl.h
- GLFW/glfw3.h
- glm/glm.hpp
- GL/glew.h
- stb_image

If any of these are unavailable to you, downloads can be found in the resources section.

## Compiling the application:
Compile using the makefile: 
```
make run
```

At any time, if you want to cleanup the object files:
```
make clean
```

To compile the project with debugging information enabled:
```
make debug
```

To compile an exectutable from a specific file on its own run:
```
g++ -o run ./[filepath]/[file]
```

## Running the project:
Launch the executable using:
```
./run
```

Launching the project with the debugger (after compiling with `make debug`):
```
valgrind <flags> ./run
```
or
```
gdb ./run
```

To use valgrind and gdb together, launch with:
```
valgrind -q --vgdb-error=0 ./run
```
Follow the in-terminal prompts to continue.

*Note: A list of valgrind's flags can be found in the manual pages. Simply run `man valgrind`*

## Installation Notes:
1. gcc / g++: \
If you are installing gcc / g++ on mac using homebrew, make sure to create a new symlink in your `$PATH`. It needs to occur *before* your `clang` compiler which is used as the compiler for macOS systems by default. Once your install is complete, this can be done like so; 

Mac (intel):
```
sudo ln -sf /usr/local/bin/gcc-11 /usr/local/bin/gcc
```

Mac (silicone): 
```
sudo ln -s /opt/homebrew/bin/gcc-11 /usr/local/bin/gcc
```


If you are using a silicone-based chip (M1 / M2), you may need to log out of your shell by running: 
```
exit
```
Once thats' done, restart your terminal for the change to take effect.

2. stb_image : \
`stb_image` is a public domain single header library for parsing and loading image files. \

Get the source from github. (*If you don't have `curl` visit the url and download it manually.*):
```
curl -o ./stb_image.h https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
```

Move the file into your include folder:
```
sudo mv ./stb_image.h /usr/include/
```

## Known caveats and limitations:
1. 3D Mesh assets must be exported to `wavefront` (.obj) file format before being loaded into a scene.
2. 3D mesh assets have to be **triangulated**, this can be done prior to or on export. *Faces made up of 5 vertex coordinates (polygons) are not supported.*
3. Materials that appear in `wavefront` (.mtl) material files **must** appear in order they were created. A safe way to ensure this is to number any *named* materials during the modeling process (e.g. `myColor5.mtl`). This is because named materials are often exported in alphabetical order by modeling software which can lead to undesired behaviour.
4. Upon initialising the render loop and loading of assets, there is an observable "hump" in performance for about 3-5 seconds. A full scene with lights, camera, meshes etc causes a decrease in the framerate by about 12.5% (60 frames becomes 50).
