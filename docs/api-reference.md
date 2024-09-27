# API Reference:
This API reference contains brief descriptions of each of the Lazarus classes; their contructors, functions and members and \
destructors. Private functions and members are currently omitted from this guide.

All of the Lazarus status codes can be found at the bottom of this document.

For a comprehensive usage guide, visit [Lazarus by Example](./lazarus-by-example.md)

## GlobalsManager:

### Functions:
#### void setMaxImageSize(int width, int height)
Sets the value of `LAZARUS_MAX_IMAGE_WIDTH` and `LAZARUS_MAX_IMAGE_HEIGHT`. Used to determine the rescale size for all images loaded with `FileReader::readFromImage()` from hereafter.

*Notes:* 
- *Has no effect if the value returned by `GlobalsManager::getEnforceImageSanity()`* is `true`.
- *The `width` and `height` parameters must have values higher than 0 and no higher that 2048.*
- *Also effects the cursor image. Load your cursors first!*

Params:
>**width:** *The width in pixels to be used for image resizing.*
>**height:** *The height in pixels to be used for image resizing.*

#### int getMaxImageWidth()
Returns the current value of `LAZARUS_MAX_IMAGE_WIDTH`.

#### int getMaxImageHeight()
Returns the current value of `LAZARUS_MAX_IMAGE_HEIGHT`.

#### void setEnforceImageSanity(bool shouldEnforce)
Sets the value of `LAZARUS_ENFORCE_IMAGE_SANITY` and allows calls to `GlobalsManager::setMaxImageSize()` to take effect. Also ensures all images are flipped vertically on load.

Params:
>**shouldEnforce:** *Whether or not vertical flipping and image resizing is enforced on all images.*

#### bool getEnforceImageSanity()
Returns the current value of `LAZARUS_ENFORCE_IMAGE_SANITY`.

#### void setCursorHidden(bool shouldHide)
Sets the value of `LAZARUS_DISABLE_CURSOR_VISIBILITY`. When `true` the cursor pointer will become transparent when hovered over the active game window.

*Notes:*
- *Must be set prior to creation of a window with `WindowManager::initialise()`*
- *Cursor X and Y coordinates continue to update following a call to `EventManager::monitorEvents()` as if it were opaque.*

params:
>**shouldHide:** *Whether or not cursor opacity should be set to 0.*

#### bool getCursorHidden()
Returns the current value of `LAZARUS_DISABLE_CURSOR_VISIBILITY`.

#### void setBackFaceCulling(bool shouldCull)
Sets the value of `LAZARUS_CULL_BACK_FACES`. I don't reccomend disabling this optimisation but if you want to you can... Ensures that faces opposite to the camera aren't rendered. Front face culling is currently unsupported through lazarus but you can enable it yourself using OpenGL (prior to window creation) like so:

```cpp
glEnable(GL_CULL_FACE);
glCullFace(GL_FRONT);
```

params:
>**shouldCull:** *Whether or not to disable the rendering of faces that are currently out of sight.*

#### bool getBackFaceCulling()
Returns the current value of `LAZARUS_CULL_BACK_FACES`.

#### void setDepthTest(bool shouldTest)
Sets the value of `LAZARUS_DEPTH_TEST_FRAGS`. Again, I don't reccomend disabling this setting. Informs OpenGL that we want it to perform a depth test on the current fragment that is being drawn against the rest of the frame buffers contents. Determines what is in-front or behind. Turning this off can have a disastrous effect on the render result.

params:
>**shouldTest:** *Whether or not OpenGL should should check which fragments are in-front or behind of eachother.*

#### getDepthTest()
Returns the current value of `LAZARUS_DEPTH_TEST_FRAGS`.

#### void setExecutionState(int state)
This will eventually be made private but right now it isn't which is why I'm documenting it here. Sets the value of `LAZARUS_EXECUTION_STATUS` which; in an error-free program should always(!) be 0.

*(Note: Seriously, no point in touching this. you're just shooting yourself in the foot).*

params:
>**state:** *The desired execution-status (status code).*

#### int getExecutionState()
Returns the current value of `LAZARUS_EXECUTION_STATUS`. Any errors that occur inside the engine should update this value to be one of any lazarus status code.

## WindowManager:
A class for making and managing the program's window(s). 

### Constructor:
#### WindowManager(int h, int w, const char *t, GLFWmonitor *m = NULL, GLFWwindow *win = NULL)

Params:
> **h**: *The height of the window* \
> **w**: *The width of the window* \
> **t**: *The window's title* \
> **m**: *A pointer to which monitor this window should popup in. (optional)* \
> **win**: *A pointer to another window used when the user enters fullscreen. (optional)*

### Functions:
#### int initialise()
Creates a new instance of a window, initialises OpenGL and creates a GL context.

#### int loadConfig(GLuint shader)
Binds a shader program to the current active window's OpenGL Context and loads a render configuration based on values set in the global scope (see: `GlobalsManager`).

Params:
> **shader:** *The id of the engine's shader program. This can be acquired from a call to `Shader::initialiseShader()` or by compiling your own shader program. (default: `0`)* 


#### int open()
Opens the active window.

#### int close()
Closes the active window.

#### int createCursor(int sizeX, int sizeY, int hotX, int hotY, unsigned char *cursorImage)
Builds a unique cursor for the window from an image loaded in by the user.

Params:
> **sizeX:** *Cursor image width.* \
> **sizeY:** *Cursor image height.* \
> **hotX:** *The x-axis cursor hotspot.* \
> **hotY:** *The y-axis cursor hotspot.* \
> **cursorImage:** *The encoded image with the following properties: 32bit-depth, RGBA color, 32x32 resolution, png file format. Can be acquired from a call to `FileReader::readFromImage()`.* 

#### int handleBuffers()
Bring the back buffer to the front (into user view) and moves the front buffer to the back. \
Clears the back buffer's depth and color bits so that they can be given new values for the next draw.

### Members:
> **isOpen:** *Whether or not the active window is open. See also: `GlobalsManager::getContextWindowOpen()`. (type: `bool`, default: `false`)* \

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

#### void resizeImagesOnLoad(bool shouldResize)
Updates the `LAZARUS_ENFORCE_IMAGE_SANITY` global flag *(default: `false`)*. Informs the image loader that it should resize all images to the dimensions of `LAZARUS_MAX_IMAGE_WIDTH`x`LAZARUS_MAX_IMAGE_HEIGHT` prior to adding the image to the texture stack.

Params:
>**shouldResize:** *If true use max image height & width global values, otherwise use image raw size.*

#### void setMaxImageSize(int width, int height)
Sets values for the global `LAZARUS_MAX_IMAGE_WIDTH` and `LAZARUS_MAX_IMAGE_HEIGHT` flags.

Params:
>**height:** *The desired height to enforce accross all images, must be higher than 0 when `LAZARUS_ENFORCE_IMAGE_SANITY` is set. Cant be set beyond 2048.* \
>**width:** *The desired width to enforce accross all images, must be higher than 0 when `LAZARUS_ENFORCE_IMAGE_SANITY` is set. Cant be set beyond 2048.*

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
Returns a shared pointer to the mesh object.

Params:
> **mesh:** *A pointer to the mesh asset to be acted upon. (type: `std::shared_ptr<Mesh::TriangulatedMesh>`)* \
> **x:** *A floating point number used to increment / decrement the x-axis locative value of the mesh.* \
> **y:** *A floating point number used to increment / decrement the y-axis locative value of the mesh.* \
> **z:** *A floating point number used to increment / decrement the z-axis locative value of the mesh.*

#### shared_ptr\<Mesh::TriangulatedMesh> rotateMeshAsset(shared_ptr\<Mesh::TriangulatedMesh> mesh, float x, float y, float z)
Applies a rotation transformation to a mesh asset on it's x, y and z axis from an offset of 0.0. \
This rotation affects the yaw, pitch and roll of the mesh. Not to be confused with an orbital rotation. \
Returns a shared pointer to the mesh object.

Params:
> **mesh:** *A pointer to the mesh asset to be acted upon. (type: `std::shared_ptr<Mesh::TriangulatedMesh>`)* \
> **x:** *A floating point number used to increment / decrement the x-axis (yaw) rotational value of the mesh.* \
> **y:** *A floating point number used to increment / decrement the y-axis (pitch) rotational value of the mesh.* \
> **z:** *A floating point number used to increment / decrement the z-axis (roll) rotational value of the mesh.*

#### shared_ptr\<Camera::FixedCamera> translateCameraAsset(shared_ptr\<Camera::FixedCamera> camera, float x, float y, float z)
Applies a translation transformation (movement) to a camera asset along the x, y and z axis from an offset of 0.0. \
Updates the `locationX`, `locationY` and `locationZ` properties of a `Camera::FixedCamera` object in real time. \
Returns a shared pointer to the camera object.

Params:
> **camera:** *A pointer to the camera asset to be acted upon. (type: `std::shared_ptr<Camera::FixedCamera>`)* \
> **x:** *A floating point number used to increment / decrement the x-axis locative value of the camera.* \
> **y:** *A floating point number used to increment / decrement the y-axis locative value of the camera.* \
> **z:** *A floating point number used to increment / decrement the z-axis locative value of the camera.*

#### shared_ptr\<Camera::FixedCamera> rotateCameraAsset(shared_ptr\<Camera::FixedCamera> camera, float x, float y, float z)
Applies a rotation transformation to a camera asset on it's x, y and z axis from an offset of 0.0. \
This rotation affects the yaw, pitch and roll of the camera. Not to be confused with an orbital rotation. \
Returns a shared pointer to the camera object.

Params:
> **camera:** *A pointer to the camera asset to be acted upon. (type: `std::shared_ptr<Camera::FixedCamera>`)* \
> **x:** *A floating point number used to increment / decrement the x-axis locative value of the camera.* \
> **y:** *A floating point number used to increment / decrement the y-axis locative value of the camera.* \
> **z:** *A floating point number used to increment / decrement the z-axis locative value of the camera.*

#### shared_ptr\<Light::AmbientLight> translateLightAsset(shared_ptr\<Light::AmbientLight> light, float x, float y, float z)
Applies a translation transformation (movement) to a light asset along the x, y and z axis from an offset of 0.0. \
Updates the `locationX`, `locationY` and `locationZ` properties of a `Light::AmbientLight` object in real time. \
Returns a shared pointer to the light object.


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
#### shared_ptr\<TriangulatedMesh> create3DAsset(std::string meshPath, std::string materialPath, std::string texturePath)
Finds and reads a wavefront (obj) file located at `meshPath`. \
Creates a new instance of a `TriangulatedMesh`, initialises the values of its properties and returns it. \
Invokes the `MaterialLoader::loadMaterial()` function and passes on the `materialPath`.

Returns a shared pointer to the mesh object.

Params:
> **meshPath:** *The relative path to the wavefront mesh asset you wish to render.* 
> **materialPath:** *The relative path to the wavefront material asset you wish to render.*
> **texturePath:** *The relative path to the texture image. (optional)*

#### shared_ptr\<TriangulatedMesh> createQuad(float width, float height, std::string texturePath)
Creates a quad (2D plane) to the size of the specified height and width. \
Textures loaded into a quad have their fragments discarded where the texture opacity is 0.0 - used for sprites.

Returns a shared pointer to the mesh object.

Params:
> **width:** *The relative path to the wavefront mesh asset you wish to render.* 
> **height:** *The relative path to the wavefront material asset you wish to render.*
> **texturePath:** *The relative path to the texture image. (optional)*

#### shared_ptr\<TriangulatedMesh> initialiseMesh(shared_ptr\<TriangulatedMesh> meshData)
Generates a new vertex array object and binds it to the current OpenGL context. \
Generates and binds a vertex buffer object to the array object for each of the mesh's properties, these are:
- vertex coordinates
- vertex normals
- diffuse colours

Returns a shared pointer to the mesh object.

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
>	- **textureId:** *The serialised id of the mesh objects texture. The layer depth of the texture. (type: `int`)* 
>   - **is3D:** *Literal 0 (false) or 1 (true). Flags the shader to treat the mesh as a sprite, discarding fragments with an alpha value higher than 0.1 (type: `int`)*
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
#### bool parseWavefrontObj(const char* path, std::vector\<glm::vec3> &outAttributes, std::vector\<glm::vec3> &outDiffuse, GLuint &outTextureId, FileReader::Image &imageData, const char *meshPath, const char *materialPath, const char *texturePath = "")
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

Returns a shared pointer to the camera object.

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

Returns a shared pointer to the camera object.

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

Returns a shared pointer to the light object.

Params:
> **x:** *The x-axis starting coordinate of the light in world-space.* \
> **y:** *The y-axis starting coordinate of the light in world-space.* \
> **z:** *The z-axis starting coordinate of the light in world-space.* \
> **r:** *This light's red colour value.* \
> **g:** *This light's green colour value.* \
> **b:** *This light's blue colour value.* 

#### void loadLightSource(shared_ptr\<AmbientLight> &lightData)
Passes the light object's locative (x,y,z) values into the vertex shader and its' colour (r,g,b) values into the fragment shader.

Params:
> **lightData:** *A reference to the light asset you would like to render.*

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

Returns a shared pointer to the audio object.

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

## Status Codes:
- **LAZARUS_OK** *The engines default state. No problems. (Code: 0)* 
- **LAZARUS_FILE_NOT_FOUND** *The specified asset couldn't be found (Code: 101)* 
- **LAZARUS_FILE_UNREADABLE** *The located file cannot be read. (Code: 102)* 
- **LAZARUS_FILESTREAM_CLOSED** *The filestream input closed unexpectedly. (Code: 103)* 
- **LAZARUS_SHADER_ERROR** *OpenGL does not regard the output from shader compilation to be a valid shader program. (Code: 201)* 
- **LAZARUS_VSHADER_COMPILE_FAILURE** *The vertex shader failed to compile. (Code: 202)*
- **LAZARUS_FSHADER_COMPILE_FAILURE** *The fragment shader failed to compile. (Code: 203)
- **LAZARUS_SHADER_LINKING_FAILURE** *OpenGL failed to link the shaders. (Code: 204)*
- **LAZARUS_OPENGL_ERROR** *An error occured in the OpenGL graphics pipeline. (Code: 301)*
- **LAZARUS_AUDIO_ERROR** *An error occured in the FMOD audio backend. (Code: 302)*
- **LAZARUS_WINDOW_ERROR** *An error occured in the GLFW window API. (Code: 303)*
- **LAZARUS_IMAGE_LOAD_FAILURE** *STB was unable to load the contents of the given image file into a 8_8_8_8 (RGBA) buffer. (Code: 401)*
- **LAZARUS_IMAGE_RESIZE_FAILURE** *STB was unable to resize the image to the height and width specified at `LAZARUS_MAX_IMAGE_WIDTH` / `LAZARUS_MAX_IMAGE_HEIGHT` (Code: 402)*