OSFLAGS :=
ifeq ($(shell uname),Linux)
	OSFLAGS += -lGL -lGLEW -lglfw
endif

OBJECTS = main.o src/shaders/shaderProgram/src/shader.o src/lights/src/light.o src/cameras/src/camera.o \
					src/mesh/src/mesh.o src/transforms/src/transforms.o \
					src/mesh/src/meshLoader.o src/materials/src/materialLoader.o \
					src/window/src/WindowManager.o src/utils/src/fileReader.o src/window/src/eventManager.o \
					src/utils/src/fpsCounter.o src/utils/src/stb_image.o

CXX = g++ -lstdc++fs -std=c++17

run: $(OBJECTS)
		$(CXX) -o run $(OBJECTS) $(CXXFLAGS) $(LDLIBS) $(GLLIBS) $(OSFLAGS) $(SQLFLAGS)

debug: $(OBJECTS)
		$(CXX) -g -o run $(OBJECTS) $(CXXFLAGS) $(LDLIBS) $(GLLIBS) $(OSFLAGS) $(SQLFLAGS)

main.o := main.h
shader.o := src/shaders/shaderProgram/hdr/shader.h
light.o := src/lights/hdr/light.h
camera.o := src/cameras/hdr/camera.h
mesh.o := src/mesh/hdr/mesh.h
transforms.o := src/transforms/hdr/transforms.h
meshLoader.o := src/mesh/hdr/meshLoader.h
materialLoader.o := src/materials/hdr/materialLoader.h
fileReader.o := src/utils/hdr/fileReader.h
WindowManager.o := src/window/hdr/WindowManager.h
eventManager.o := src/window/hdr/eventManager.h
fpsCounter.o := src/utils/hdr/fpsCounter.h

clean : 
		rm run $(OBJECTS)
