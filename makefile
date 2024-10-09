TARGET :=

LDFLAGS := -lGLEW -lglfw -lfmod

CXX = g++

CXXFLAGS = -std=c++17 -fPIC

# OS-specifics
ifeq ($(shell uname),Linux)
	CXX += -lstdc++fs
	CXXFLAGS += -shared
	LDFLAGS += -lGL 
	TARGET += liblazarus.so
else ifeq ($(shell uname),Darwin)
	CXXFLAGS += -dynamiclib
	LDFLAGS += -framework OpenGL
	TARGET += liblazarus.dylib
endif

# Remove whitespace from "lib/ liblazarus.*"
OUT := $(addprefix lib/,$(TARGET))

OBJECTS = src/globalsManager.o src/shader.o src/light.o src/camera.o \
					src/mesh.o src/transforms.o \
					src/meshLoader.o src/materialLoader.o src/textureLoader.o \
					src/WindowManager.o src/fileReader.o src/eventManager.o \
					src/fpsCounter.o src/imageLoader.o src/imageResize.o src/soundManager.o \
					src/textManager.o src/fontLoader.o

run : build
	$(shell mv src/*.o build/)

build : $(OBJECTS)
	$(shell mkdir build && mkdir lib)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(OBJECTS) $(LDFLAGS)

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
textManager.o := include/textManager.h
fontLoader.o := include/fontLoader.h

clean : 
	rm -R lib/ && rm -R build/