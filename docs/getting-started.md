# Getting Started:
Hello and welcome to the Lazarus Project. \

Before jumping into the project, make sure the following libraries / tools are accessible on your machine:
- gcc (compiler)
- gl.h
- glfw3.h
- glm.hpp
- glew.h
- stb_image.h

If any of these are unavailable to you, downloads can be found in the resources section. \
*Note: gcc, glfw, glm & glew are available for macOS using* `homebrew` *and should be installed from there.*

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

## Usage:
Move the library and required headers.
```
sudo mv lib/liblazarus.so /usr/local/lib/
sudo mv include/* /usr/local/include/
```

Update the loader.
```
sudo ldconfig
```

You should now be able to use Lazarus with your project like so:
```cpp
#include <lazarus.h>

int main()
{
    Lazarus::WindowManager window = Lazarus::WindowManager(800, 600, "Game Window", nullptr, nullptr);
    window.initialise();

    return 0;
}
```

When compiling your project you will need to pass the following linker flags:
```
g++ main.cpp -lGL -lGLEW -lglfw -lfmod -llazarus
```

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
sudo mv ./stb_image.h /usr/local/include/
```

3. FMOD core API: \
`FMOD` is an audio engine built by Firelight Technologies Pty Ltd. The software operates under multiple distribution liscences dependant on the project's use-case, take a look at https://www.fmod.com/licensing/ to determine which liscence you need for your project.

Before `FMOD` can be used, you need to register an account on their website here https://www.fmod.com/profile/register.

Once that's done, navigate to https://www.fmod.com/download#fmodengine and download version `2.02.21` for your target OS.

Once the download is complete, extract the packages from the `.zip`.

`FMOD` libraries are available for a number of different architectures. Check which architecture your OS is running with:
```
lscpu
```
The first line should print the system's architecture, for me it's `x86_64`.

Move the *contents* of the FMOD architecture sub-directory to your `lib` folder, e.g:
```
sudo mv ./fmodstudioapi2022<OS>/api/core/lib/<your_architecture>/* /usr/local/lib
```

Do the same for the `FMOD` headers:
```
sudo mv ./fmodstudioapi2022<OS>/api/core/inc/* /usr/local/include
```

Finally, if you're running linux you will need to update your loaders' scoped libraries with:
```
sudo ldconfig
```

**If you're installing FMOD on macOS and encounter the following message:**

*“libfmod.dylib” can’t be opened because Apple cannot check it for malicious software.*

Run the following commands:
```
xattr -d com.apple.quarantine /usr/local/lib/libfmod.dylib
xattr -d com.apple.quarantine /usr/local/lib/libfmodL.dylib
```

## Known caveats and limitations:
1. 3D Mesh assets must be exported to `wavefront` (.obj) file format before being loaded into a scene.
2. 3D mesh assets have to be **triangulated**, this can be done prior to or on export. *Faces made up of 5 vertex coordinates (polygons) are not supported.*
3. Materials that appear in `wavefront` (.mtl) material files **must** appear in order they were created. A safe way to ensure this is to number any *named* materials during the modeling process (e.g. `myColor5.mtl`). This is because named materials are often exported in alphabetical order by modeling software which can lead to undesired behaviour.
4. Upon initialising the render loop and loading of assets, there is an observable "hump" in performance for about 3-5 seconds. A full scene with lights, camera, meshes etc causes a decrease in the framerate by about 12.5% (60 frames becomes 50).
5. When running Lazarus on OSX the program recieves an OpenGL 1280 (Invalid enum) error, thrown by `Mesh::initialiseMesh`. Apple stopped maintenance for `OpenGL` long ago in favor of their `Metal` API. \
The repurcussions of this are that we must now use the `GLFW_OPENGL_CORE_PROFILE` to be granted access the modern OpenGL (shader driven) API. The core profile has some gripes with `GLEW`, whatever the issue between them may be - they currently seem inconsequential to this project.
6. Texture images used in any scene must all have the same pixel width and height. If not the scene will still render but you can expect to find holes in your texture.