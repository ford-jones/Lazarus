LDFLAGS := -lGLEW -lglfw -lfmod
ifeq ($(shell uname),Linux)
	LDFLAGS += -lGL 
else ifeq ($(shell uname),Darwin)
	LDFLAGS += -framework OpenGL
endif

OBJECTS = src/globalsManager.o src/shader.o src/light.o src/camera.o \
					src/mesh.o src/transforms.o \
					src/meshLoader.o src/materialLoader.o src/textureLoader.o \
					src/WindowManager.o src/fileReader.o src/eventManager.o \
					src/fpsCounter.o src/imageLoader.o src/imageResize.o src/soundManager.o 

CXX = g++

CXXFLAGS = -std=c++17 -fPIC -shared

ifeq ($(shell uname),Linux)
	CXX += -lstdc++fs
endif


run : build
	$(shell mv src/*.o build/)

build : $(OBJECTS)
	$(shell mkdir build && mkdir lib)
	$(CXX) $(CXXFLAGS) -o lib/liblazarus.so $(OBJECTS) $(LDFLAGS)

globalsManager.o := include/globalsManager.h
shader.o := include/shader.h
light.o := include/light.h
camera.o := include/camera.h
mesh.o := include/mesh.h
transforms.o := include/transforms.h
meshLoader.o := include/meshLoader.h
materialLoader.o := include/materialLoader.h
fileReader.o := include/fileReader.h
WindowManager.o := include/WindowManager.h
eventManager.o := include/eventManager.h
fpsCounter.o := include/fpsCounter.h
soundManager.o := include/soundManager.h
textureLoader.o := include/texture.h
imageLoader.o := /usr/local/include/stb_image.h
imageResize.o := /usr/local/include/stb_image_resize.h

clean : 
	rm -R lib/ && rm -R build/