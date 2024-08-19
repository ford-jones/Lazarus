# API Reference:
This API reference contains brief descriptions of each of the Lazarus classes; their contructors, functions and members. \
Destructors, as well as private functions and members have been omitted from this guide.

For a comprehensive usage guide, visit [Lazarus by Example](./lazarus-by-example.md)

## WindowManager:
A class for making and managing the program's window(s). 

### Constructor:
#### WindowManager(int h, int w, const char *t, GLFWmonitor *m, GLFWwindow *win)

Params:
> **h**: *The height of the window* \
> **w**: *The width of the window* \
> **t**: *The window's title* \
> **m**: *A pointer to which monitor this window should popup in.* \
> **win**: *A pointer to another window used when the user enters fullscreen.*

### Functions:
#### int loadConfig(GLuint shader, bool enableCursor, bool cullFaces, bool testDepth)
Creates a configuration for the window's render pipeline.

Params:
> **shader:** *The id of the engine's shader program. This can be acquired from a call to `Shader::initialiseShader()` or by compiling your own shader program. (default: `0`)* \
> **enableCursor:** *Whether or not the cursor should be visible on the screen or disabled. (deafult: `true`)* \
> **cullFaces:** *Enables face culling. When active; faces which are not currently in eyespace are not rendered. (default: `true`)* \
> **testDepth:** *Enables depth testing. Renders fragments in order of perspective rather than the order they're drawn in. (default `true`)* \

#### int createCursor(int sizeX, int sizeY, int hotX, int hotY, unsigned char *cursorImage)
Builds a unique cursor for the window from an image loaded in by the user.

Params:
> **sizeX:** *Cursor image width.* \
> **sizeY:** *Cursor image height.* \
> **hotX:** *The x-axis cursor hotspot.* \
> **hotY:** *The y-axis cursor hotspot.* \
> **cursorImage:** *The encoded image with the following properties: 32bit-depth, RGBA color, 32x32 resolution, png file format. Can be acquired from a call to `FileReader::readFromImage()`.* 

#### int initialise()
Creates a new instance of a window, initialises OpenGL and creates a GL context.

#### int handleBuffers()
Bring the back buffer to the front (into user view) and moves the front buffer to the back. \
Clears the back buffer's depth and color bits so that they can be given new values for the next draw.

## EventManager
A class for tracking, storing and managing window events as well as their values.

### Functions:
#### void monitorEvents()
Sets up the following input-event handlers and loads them into the current window: 
- keydown 
- mousedown 
- mousemove 
- scroll

Each of these handlers are passed into the window's event loop as a callback. 
Upon calling this function, members of this class will begin being updated in real time.

### Members:
> **keyString:** *The key currently being pressed, expressed as a string. (type: `std::string`)* \
> **keyCode:** *The openGL code of the string currently being pressed. (type: `int`)* \
> **osCode:** *The operating-system specific "scancode" of the key currently being pressed. (type `int`)* \
> **mouseCode:** *An integer in the range of 0 to 8 expressing which mouse button is currently being clicked / pressed. (type: `int`)* \
> **mouseX:** *The current x-axis coordinate of the cursor. (type: `int`)* \
> **mouseY:** *The current y-axis coordinate of the cursor. (type: `int`)* \
> **scrollCode:** *An integer in the range of -1 to 1 expressing the scrollwheel's y-offset.* 

## Shader:
A class for the lazarus default shader program which, simply maps vertex positions to their coordinates and draws the fragments; following the lambertian lighting model.

### Constructor:
#### Shader()
Default-initialises this classes members.

### Functions:
#### GLuint initialiseShader()
Invokes the parsing, compiling, attatching and linking of the Lazarus vert and frag shaders. \
Returns the Id (OpenGL unsigned integer) of the shader program which can then be passed to the various constructors which need it.

*Note:* \
*Failure to pass the return value of this function as an argument into `WindowManager::loadConfig()` will cause the program to use the GL default shader program.* \
*While this may still render graphics in some limitted capacity, it is not reccomended to do so.* \
*Loading your own program should work fine, so long as you note the return GLuint value of the call to `glCreateProgram()`*

## FpsCounter:
A simple frames-per-second listener class.

### Functions:
#### void calculateFramesPerSec();
Calculates the current frames per second, as well as the number of milliseconds taken to render a single frame.

### Members:
> **framesPerSecond:** *Current number of frames being drawn per second. (type: `double`)* \
> **durationTillRendered:** *The duration of time taken in milliseconds to draw a single frame. (type: `double`)* 

## FileReader:
A utility class for locating files and reading their contents.

### Constructor:
#### FileReader()
Default-initialises this classes members.

### Functions:
#### std::string relativePathToAbsolute(std::string filepath)
Finds the absolute path (from root) to the `filepath` and returns it as `std::string`.

Params:
> **filepath**: The relative path to the file you would like to find the absolute path of.

#### const char *readFromText(std::string filepath)
Reads a file who's contents are expressed in ascii. Stores the files contents in a variable and returns it.

Params:
> **filepath**: The relative path to the file you would like to read from.

#### FileReader::Image readFromImage(std::string filename)
Reads and parses the contents of an image file (.png, .jpg, .tga, .pic; view `stb_image` documentation for the full list). 
Returns the image data in the form of an `unsigned char*`.

Params:
> **filename**: The relative path to the file you would like to read from.

### Members:
> **Image:** *The properties of an image returned from stb_image. (type: `struct`)* 
>	- **width:** *The images pixel-width.. (type: `int`)* 
>	- **height:** *The images pixel-height. (type: `int`)* 
>	- **pixelData:** *The actual image data / texels tightly packed in RGBA order. (type: `unsigned char *`)* 
## Transform:
A class built to handle transformations of different world assets such as mesh, cameras and lights.

### Functions:
#### shared_ptr\<Mesh::TriangulatedMesh> translateMeshAsset(shared_ptr\<Mesh::TriangulatedMesh> mesh, float x, float y, float z)
Applies a translation transformation (movement) to a mesh asset along the x, y and z axis from an offset of 0.0. \
Updates the `locationX`, `locationY` and `locationZ` properties of a `Mesh::TriangulatedMesh` object in real time. \
Returns a shared pointer to the mesh object. It is recommended you use `std::move()` to reclaim ownership of the returned object to improve performance by reducing the number of registered owners.

Params:
> **mesh:** *A pointer to the mesh asset to be acted upon. (type: `std::shared_ptr<Mesh::TriangulatedMesh>`)* \
> **x:** *A floating point number used to increment / decrement the x-axis locative value of the mesh.* \
> **y:** *A floating point number used to increment / decrement the y-axis locative value of the mesh.* \
> **z:** *A floating point number used to increment / decrement the z-axis locative value of the mesh.*

#### shared_ptr\<Mesh::TriangulatedMesh> rotateMeshAsset(shared_ptr\<Mesh::TriangulatedMesh> mesh, float x, float y, float z)
Applies a rotation transformation to a mesh asset on it's x, y and z axis from an offset of 0.0. \
This rotation affects the yaw, pitch and roll of the mesh. Not to be confused with an orbital rotation. \
Returns a shared pointer to the mesh object. It is recommended you use `std::move()` to reclaim ownership of the returned object to improve performance by reducing the number of registered owners.

Params:
> **mesh:** *A pointer to the mesh asset to be acted upon. (type: `std::shared_ptr<Mesh::TriangulatedMesh>`)* \
> **x:** *A floating point number used to increment / decrement the x-axis (yaw) rotational value of the mesh.* \
> **y:** *A floating point number used to increment / decrement the y-axis (pitch) rotational value of the mesh.* \
> **z:** *A floating point number used to increment / decrement the z-axis (roll) rotational value of the mesh.*

#### shared_ptr\<Camera::FixedCamera> translateCameraAsset(shared_ptr\<Camera::FixedCamera> camera, float x, float y, float z)
Applies a translation transformation (movement) to a camera asset along the x, y and z axis from an offset of 0.0. \
Updates the `locationX`, `locationY` and `locationZ` properties of a `Camera::FixedCamera` object in real time. \
Returns a shared pointer to the camera object. It is recommended you use `std::move()` to reclaim ownership of the returned object to improve performance by reducing the number of registered owners.

Params:
> **camera:** *A pointer to the camera asset to be acted upon. (type: `std::shared_ptr<Camera::FixedCamera>`)* \
> **x:** *A floating point number used to increment / decrement the x-axis locative value of the camera.* \
> **y:** *A floating point number used to increment / decrement the y-axis locative value of the camera.* \
> **z:** *A floating point number used to increment / decrement the z-axis locative value of the camera.*

#### shared_ptr\<Camera::FixedCamera> rotateCameraAsset(shared_ptr\<Camera::FixedCamera> camera, float x, float y, float z)
Applies a rotation transformation to a camera asset on it's x, y and z axis from an offset of 0.0. \
This rotation affects the yaw, pitch and roll of the camera. Not to be confused with an orbital rotation. \
Returns a shared pointer to the camera object. It is recommended you use `std::move()` to reclaim ownership of the returned object to improve performance by reducing the number of registered owners.

Params:
> **camera:** *A pointer to the camera asset to be acted upon. (type: `std::shared_ptr<Camera::FixedCamera>`)* \
> **x:** *A floating point number used to increment / decrement the x-axis locative value of the camera.* \
> **y:** *A floating point number used to increment / decrement the y-axis locative value of the camera.* \
> **z:** *A floating point number used to increment / decrement the z-axis locative value of the camera.*

#### shared_ptr\<Light::AmbientLight> translateLightAsset(shared_ptr\<Light::AmbientLight> light, float x, float y, float z)
Applies a translation transformation (movement) to a light asset along the x, y and z axis from an offset of 0.0. \
Updates the `locationX`, `locationY` and `locationZ` properties of a `Light::AmbientLight` object in real time. \
Returns a shared pointer to the light object. It is recommended you use `std::move()` to reclaim ownership of the returned object to improve performance by reducing the number of registered owners.


Params:
> **light:** *A pointer to the light asset to be acted upon. (type: `std::shared_ptr<Light::AmbientLight>`)* \
> **x:** *A floating point number used to increment / decrement the x-axis locative value of the light.* \
> **y:** *A floating point number used to increment / decrement the y-axis locative value of the light.* \
> **z:** *A floating point number used to increment / decrement the z-axis locative value of the light.*

## Mesh:
A management class for mesh assets and their properties.

### Constructor:
#### Mesh(GLuint shader)

Params:
> **shader:** *The id of the shader program used to render this mesh. Acquired from the return value of `Shader::initialiseShader()`*

### Functions:
#### shared_ptr\<TriangulatedMesh> createTriangulatedMesh(std::string meshPath, std::string materialPath)
Finds and reads a wavefront (obj) file located at `meshPath` by invoking `FileReader::readFromText()`. \
Creates a new instance of a `TriangulatedMesh`, initialises the values of its properties and returns it. \
Invokes the `MaterialLoader::loadMaterial()` function and passes on the `materialPath`.

Returns a shared pointer to the mesh object. It is recommended you use `std::move()` to reclaim ownership of the returned object to improve performance by reducing the number of registered owners.

Params:
> **meshPath:** *The relative path to the wavefront mesh asset you wish to render.* 
> **materialPath:** *The relative path to the wavefront material asset you wish to render.*

#### shared_ptr\<TriangulatedMesh> initialiseMesh(shared_ptr\<TriangulatedMesh> meshData)
Generates a new vertex array object and binds it to the current OpenGL context. \
Generates and binds a vertex buffer object to the array object for each of the mesh's properties, these are:
- vertex coordinates
- vertex normals
- diffuse colours

Returns a shared pointer to the mesh object. It is recommended you use `std::move()` to reclaim ownership of the returned object to improve performance by reducing the number of registered owners.

Params:
> **meshData:** *A pointer to the mesh object who's data you wish to write to buffers.*

#### shared_ptr\<TriangulatedMesh> loadMesh(shared_ptr<TriangulatedMesh> meshData)
Loads a mesh object's buffer data into their correct GPU uniform positions located inside the shader program that was referenced in the class constructor.

Params:
> **meshData:** *A pointer to the mesh object who's buffer data you wish to pass into the shader program.*

#### shared_ptr\<TriangulatedMesh> drawMesh(shared_ptr<TriangulatedMesh> meshData)
Draws the mesh object contents of the shader program's uniforms onto the render loops back buffer (see: `WindowManager::handleBuffers()`). \
Be sure to bring the back buffer forward to see the draw result.

> Params:
> **meshData:** *A pointer to the mesh object you wish to draw.*

### Members:
> **TriangulatedMesh:** *A collection of properties which make up a mesh object. (type: `struct`)* 
>	- **id:** *The unique id of the mesh object. (type: `int`)* 
>	- **id:** *The serialised id of the mesh objects texture. The layer depth of the texture. (type: `int`)* 
>	- **numOfFaces:** *The number of faces that make up the mesh. (type: `int`)* 
>	- **numOfVertices:** *The number of vertices that make up the mesh. (type: `int`)* 
>	- **meshFilepath:** *The absolute path (from system root) to the wavefront file containing this mesh's vertex data. (type: `std::string`)*
>	- **materialFilepath:** *The absolute path (from system root) to the wavefront file containing this mesh's material data. (type: `std::string*`)*
>	- **textureFilepath:** *The absolute path (from system root) to the wavefront file containing this mesh's texture image. (type: `std::string`)*
>	- **locationX:** *The x-axis coordinate of the mesh's position in world space. (type: float)*
>	- **locationY:** *The y-axis coordinate of the mesh's position in world space. (type: float)*
>	- **locationZ:** *The z-axis coordinate of the mesh's position in world space. (type: float)*
>	- **attributes:** *This mesh's vertex attributes interleaved in order of position, diffuse color, normal coords and finally uv coords. (type: `glm::vector<glm::vec3>>`)*
>	- **diffuse:** *Diffuse material (colour) data extracted from the wavefront material (mtl) file. (type: `glm::vector<glm::vec3>>`)*
>   - **textureData:** *A struct containing image data. (type: `FileReader::Image`)*
>	- **modelViewMatrix:** *A 4x4 modelview matrix to be passed into the shader program at the uniform location of `modelViewUniformLocation`. (type: `glm::mat4`)*
>	- **modelViewUniformLocation:** *The uniform location / index of the vert shader's modelview matrice. (type: GLuint)*
>   - **samplerUniformLocation:** *The location inside of the shader program of the texture array uniform which holds this mesh's texture data (if any). (type: `GLint`)*
>   - **textureLayerUniformLocation:** *The location inside of the shader program of the uniform in which the active texture layer is passed.*

## MeshLoader:
A simple loader class for loading wavefront (obj) files and marshalling their contents into variables.

### Contructor:
#### MeshLoader()
Default-initialises this classes members.

### Functions:
#### bool loadMesh(const char* path, std::vector\<glm::vec3> &outAttributes, std::vector\<glm::vec3> &outDiffuse, GLuint &outTextureId, FileReader::Image &imageData, const char *meshPath, const char *materialPath, const char *texturePath = "")
Parses a wavefront (obj) file.

Returns a boolean, if an error occurs or the file cannot be loaded this value will be `false`.

Params:
> **outAttributes:** *A vector to store interleaved vertex attribute data in AOS format in the following order: vertex positions, diffuse colors, normal coordinates, uv coordinates.* \
> **outDiffuse:** *A vector for storing diffuse color data. Literal `-0.01f` values indicate the use of an image texture.* \
> **outTextureId:** *The serialised ID of a valid named texture. Returns 0 if no textures are used. Otherwise returns an integer used to indicate where the texture is stored in the shader programs texture array.* \
> **imageData:** *A struct containing texel data, image width and height.* \
> **meshPath:** *The absolute path to this mesh's wavefront (.obj) file* \
> **materialPath:** *The absolute path to this mesh's wavefront material (.mtl) file.* \
> **texturePath:** *The absolute path to this mesh's texture file (optional).* 

### Members:
> **foundMaterial:** *The absolute path to this mesh's matertial (.mtl) file. (type: `std::string`)* \
> **file:** *A pointer to the material file stored in your local filesystem. (type: `std::ifstream*`)* \
> **vertexIndices:** *Grouped indexes / locations of relevant vertex coordinate data who's values make up the geometry of one of the mesh's faces. (type: `std::vector<unsigned int>`)* \
> **uvIndices:** *Grouped indexes / locations of relevant vertex texture data who's values make up the texture wrap of one of the mesh's faces. (type: `std::vector<unsigned int>`)* \
> **normalIndices:** *Grouped indexes / locations of relevant vertex normal data who's values make up the direction that one of the mesh's faces is facing. (type: `std::vector<unsigned int>`)* \
> **tempVertices:** *A vector to store the actual vertex coordinate values found at the `vertexIndices` indexes. (type: `std::vector<glm::vec3>`)* \
> **tempUvs:** *A vector to store the actual texture values found at the `uvIndices` indexes. (type: `std::vector<glm::vec2>`)* \
> **tempNormals:** *A vector to store the actual vertex normal values found at the `normalIndices` indexes. (type: `std::vector<glm::vec3>`)* \
> **tempDiffuse:** *A vector to store diffuse colour data returned from a call to `MaterialLoader::loadMaterial()`. (type: `std::vector<glm::vec3>`)*

## MaterialLoader:
A simple loader class for loading wavefront (obj) files and marshalling their contents into variables.

### Contructor:
#### MaterialLoader()
Default-initialises this classes members.

### Functions: 
#### bool loadMaterial(std::vector\<glm::vec3> &out, std::vector<std::vector<int>> data, std::string materialPath, GLuint &textureId, FileReader::Image &imageData, std::string texturePath = "")
Parses a wavefront material (mtl) file for it's diffuse colour values, which are converted to `float` and stored inside a `glm::vec3`. \

Returns a boolean, if an error occurs or the file cannot be loaded this value will be `false`.

Params:
> **out:** *A vector for storing diffuse colour data.* \
> **data:** *another vector which; at index 0 holds a material id and at index 1 is the number of faces using it.*
> **materialPath:** *The absolute path to this mesh's matertial (.mtl) file.* \
> **textureId:** *The serialised ID of a valid named texture. Returns 0 if no textures are used. Otherwise returns an integer used to indicate where the texture is stored in the shader programs texture array.* \
> **imageData:** *A struct containing texel data, image width and height.* \
> **texturePath:** *The absolute path to this mesh's texture file (optional).*

## TextureLoader:
A management class for the handling of a mesh's texture assets.

### Constructor:
Default initialises this class's members.

### Functions:
#### void storeTexture(std::string texturePath, GLuint &textureLayer, FileReader::Image &imageData)
Loads the image file, invokes the generation of a new texture unit and allocates / realocates the programs texture image storage.

Params:
> **texturePath:** *The absolute path to this mesh's texture file.* \
> **textureLayer:** *The serialised ID of a valid named texture. Returns 0 if no textures are used. Otherwise returns an integer used to indicate where the texture is stored in the shader programs texture array.* \
> **imageData:** *A struct containing texel data, image width and height.* \

#### void loadTexture(FileReader::Image imageData, GLuint textureLayer)
Passes texel data into the target texture layer, generates a mipmap for it and sets the textures parameters.

Params:
> **imageData:** *A struct containing texel data, image width and height.* \
> **textureLayer:** *The serialised ID of a valid named texture. Returns 0 if no textures are used. Otherwise returns an integer used to indicate where the texture is stored in the shader programs texture array.* \

## Camera:

### Constructor:
Default initialises this class's members.

#### Camera(GLuint shader)

Params:
> **shader:** *The id of the shader program used to render this camera. Acquired from the return value of `Shader::initialiseShader()`*

### Functions: 
#### shared_ptr\<FixedCamera> createFixedCamera(int arX, int arY, double pX, double pY, double pZ, double tX, double tY, double tZ, double uX, double uY, double uZ)
Creates a new instance of a `FixedCamera`, initialises the values of its properties and returns it.

Returns a shared pointer to the camera object. It is recommended you use `std::move()` to reclaim ownership of the returned object to improve performance by reducing the number of registered owners.

Params:
> **arX:** *The x-axis aspect ratio / width of the viewport.* \
> **arY:** *The y-axis aspect ratio / height of the viewport.* \
> **pX:** *The x-axis starting position / location of the camera.* \
> **pY:** *The y-axis starting position / location of the camera.* \
> **pZ:** *The z-axis starting position / location of the camera.* \
> **tX:** *The x-axis target / lookat coordinate.* \
> **tY:** *The y-axis target / lookat coordinate.* \
> **tZ:** *The z-axis target / lookat coordinate.* \
> **uX:** *The x-axis "up" vector. (Which way is up).* \
> **uY:** *The y-axis "up" vector. (Which way is up).* \
> **uZ:** *The z-axis "up" vector. (Which way is up).*

#### shared_ptr\<FixedCamera> loadCamera(shared_ptr\<FixedCamera> cameraData)
Passes the camera's projection matrix and view matrix into the shader program's corresponding uniform locations.

Returns a shared pointer to the camera object. It is recommended you use `std::move()` to reclaim ownership of the returned object to improve performance by reducing the number of registered owners.

Params:
> **cameraData:** *A pointer to the camera asset you would like to render.*

### Members:
> **FixedCamera:** *A collection of properties which make up a camera asset. (type: `struct`)* 
>	- **id:** *This camera's unique id. (type: `int`)* 
>	- **locationX:** *The x-axis coordinate of the camera's position in world space. (type: `float`)*
>	- **locationY:** *The y-axis coordinate of the camera's position in world space. (type: `float`)*
>	- **locationZ:** *The z-axis coordinate of the camera's position in world space. (type: `float`)*
>	- **cameraPosition:** *The x, y, z location of the camera. (type: `glm::vec3`)*
>	- **targetPosition:** *The x, y, z location of the camera's target. (type: `glm::vec3`)*
>	- **upVector:** *Which way is considered up. (type: `glm::vec3`)*
>	- **aspectRatio:** *The camera's aspect ratio. (type: `float`)*
>	- **viewLocation:** *The uniform location / index vert shader's view matrice. (type: `GLuint`)*
>	- **projectionLocation:** *The uniform location / index vert shader's projection matrice. (type: `GLuint`)*
>	- **viewMatrix:** *The view matrix to be passed into the shader program at the uniform location of `viewLocation`. (type: `glm::mat4`)*
>	- **projectionMatrix:** *The projection matrix to be passed into the shader program at the uniform location of `projectionLocation`. (type: `glm::mat4`)*

## Light:
A management class for light assets and their properties. 

### Constructor:
#### Light(GLuint shader)

Params:
> **shader:** *The id of the shader program used to render this light. Acquired from the return value of `Shader::initialiseShader()`*

### Functions: 
#### shared_ptr\<AmbientLight> createAmbientLight(double x, double y, double z, double r, double g, double b)
Creates a new instance of an `AmbientLight`, initialises the values of its properties and returns it.

Returns a shared pointer to the light object. It is recommended you use `std::move()` to reclaim ownership of the returned object to improve performance by reducing the number of registered owners.

Params:
> **x:** *The x-axis starting coordinate of the light in world-space.* \
> **y:** *The y-axis starting coordinate of the light in world-space.* \
> **z:** *The z-axis starting coordinate of the light in world-space.* \
> **r:** *This light's red colour value.* \
> **g:** *This light's green colour value.* \
> **b:** *This light's blue colour value.* 

#### shared_ptr\<AmbientLight> initialiseLight(shared_ptr\<AmbientLight> lightData)
Passes the light object's locative (x,y,z) values into the vertex shader and its' colour (r,g,b) values into the fragment shader.

Params:
> **lightData:** *A pointer to the light asset you would like to render.*

### Members:
> **AmbientLight:** *A collection of properties which make up a light asset. (type: `struct`)*
>	- **id:** *This light's unique id. (type: `int`)*
>	- **locationX:** *The x-axis coordinate of the light's position in world space. (type: `float`)*
>	- **locationY:** *The y-axis coordinate of the light's position in world space. (type: `float`)*
>	- **locationZ:** *The z-axis coordinate of the light's position in world space. (type: `float`)*
>	- **lightPosition:** *The x, y, z location of the light. (type: glm::vec3)*
>	- **lightColor:** *The r, g, b color values of the light. (type: glm::vec3)*
>	- **lightPositionUniformLocation:** *The location / index of the vertex shader position uniform. (type: `GLuint`)*
>	- **lightColorUniformLocation:** *The location / index of the fragment shader diffuse uniform. (type: `GLuint`)*

## SoundManager:
A management class using an `FMOD` backend for loading audio, as well as handling audio locations and listeners. 

### Constructor:
#### SoundManager()

### Functions:
#### void initialise()
Initialises `FMOD` core and instantiates a new system for interfacing with up to 512 unique audio channels. 

#### shared_ptr\<Audio> createAudio(string filepath, bool is3D, int loopCount)
Creates a new instance of `SoundManager::Audio`, initialises the values of its properties and returns it.

Returns a shared pointer to the audio object. It is recommended you use `std::move()` to reclaim ownership of the returned object to improve performance by reducing the number of registered owners.

Params:
> **filepath:** *The relative path to the audio (mp3 / wav) asset.* \
> **is3D:** *Indicates whether the sound has locative properties or it plays ambiently.* \
> **loopCount:** *The number of times the audio should loop. Use -1 to loop infinitely. (default: `0`)*

#### shared_ptr\<Audio> loadAudio(shared_ptr\<Audio> audioIn)
Loads an instance of `SoundManager::Audio` into memory and prepares it for playback with `FMOD`.

Params:
> **audioIn:** *The audio object you want to load.*

#### shared_ptr\<Audio> playAudio(shared_ptr\<Audio> audioIn)
Plays a `SoundManager::Audio` instance from memory which has been previously loaded with `SoundManager::loadAudio()`.

Params:
> **audioIn:** *The audio object you want to start playing.*

#### shared_ptr\<Audio> pauseAudio(shared_ptr\<Audio> audioIn)
Pauses an `SoundManager::Audio` instance from memory which has been previously played with `SoundManager::playAudio()`.

Params:
> **audioIn:** *The audio object you want to pause / stop playing.*


#### shared_ptr\<Audio> updateSourceLocation(shared_ptr\<Audio> audioIn, float x, float y, float z)
Updates the location in 3D of a `SoundManager::Audio` source; using `FMOD` to calculate the sound's doppler, relative to the listener's current positioning (*see*: `SoundManager::listenerLocationX`, `SoundManager::listenerLocationY` and `SoundManager::listenerLocationZ`).

Params:
> **audioIn**: *The audio sample to be updated.* \
> **x**: *The desired audio source location on the x-axis.* \
> **y**: *The desired audio source location on the y-axis.* \
> **z**: *The desired audio source location on the z-axis.* 

#### void updateListenerLocation(float x, float y, float z)
Updates the location in 3D space of the audio's listener; using `FMOD` to calculate the doppler level, relative to the `SoundManager::Audio` current positioning. 

Params:
> **x**: *The desired audio listener location on the x-axis.* \
> **y**: *The desired audio listener location on the y-axis.* \
> **z**: *The desired audio listener location on the z-axis.* 

### Members:
> **Audio:** *A collection of properties which make up a sound asset. (type: `struct`)*
>	- **id:** *This audio's unique id. (type: `int`)*
>	- **sourceLocationX:** *The x-axis coordinate of the audio's position in world space. (type: `float`)*
>	- **sourceLocationY:** *The y-axis coordinate of the audio's position in world space. (type: `float`)*
>	- **sourceLocationZ:** *The z-axis coordinate of the audio's position in world space. (type: `float`)*
>   - **is3D:** *Signifies whether the sound should be played in relation to the space or ambiently. (type: `bool`)*
>   - **isPaused:** *Signifies whether the sound is currently playing or not (type: `bool`)*
>   - **loopCount:** *The number of times that this audio sample should loop. Use -1 to loop indefinitely. (type: `int`), (default: `0`)*
>   - **audioIndex:** *Used internally to identify the audio object's location in the audio vector. (type: `int`)* 
> 
> **listenerLocationX:** *The audio listener's location on the x-axis.* \
> **listenerLocationY:** *The audio listener's location on the y-axis.* \
> **listenerLocationZ:** *The audio listener's location on the z-axis.*