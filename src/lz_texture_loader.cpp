//              .,                                                                                                          .(*      ,*,                
//                ((.     (.    ,                                                                          */*  ,%##%%%%%%%%%%%%%%%#(*           .      
//         .//**/#%%%%%%%%%%%%%%#*   .,                                                             ,**   .(%%%%%%#(******,***,/#%%%%%%%%###(/,         
//             #%%%#*.#%/***,,..,*(%(.    ,,                                                     *     /#%##/*****,,,,,,,,,.,...,,#%,  .#%#.            
//    .,     *%&#/   %#**,,*..,....,.*#,     ..                                               *     ,%#%#/*,,*,*,,,,,.,.,,.,...,...((     /#(//*/**.    
//           (%#    *#*...,.,,..........*/      ,                                          .      *#%(#(**,,,,,,,,..,..,..,,........(.     *#(          
//           *#     *(......,.............(#      ,                                       .     ,((, ##,,,.....,.................. ./       **  .,.     
//            *     ./........ ...........*#*,                                          ,      ,(,  ./*,,,..,,.................  .. *                   
//                   /, ........    ... ../(  *.                                              ,*     /,...,,.,,.....   ............**                   
//                    *... .............  /    ,                                             *,      ,*,,............  ,....     ...                    
//                     *.   ..... .... ..*                                                  .*        *...................   .  ...                     
//               *       ... ......... ,.                                                   ,          ... ..........  ...     ..       ,               
//                ((        .,.,.. ...                                                                   .  . .. .  .  ... .  ..      //                
//              ,/(#%#*                                                                                     .....  ... ......       .#*                 
//                 /((##%#(*                                                                                      .......        ,(#(*,                 
//               (.           .,,,,,                                                                                        .*#%%(                      
//                                                                                                      .***,.   . .,/##%###(/.  ...,,.      
/*  LAZARUS ENGINE */

#include "../include/lz_texture_loader.h"

TextureLoader::TextureLoader()
{
	std::cout << GREEN_TEXT << "Calling constructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;

	this->loader = nullptr;	

	this->image = {pixelData: NULL, height: 0, width: 0};
	this->bitmapTexture = 0;
	this->textureStack = 0;

	this->x = 0;
	this->y = 0;
	this->loopCount = 0;
	this->mipCount = 0;
	this->errorCode = 0;
	
	this->offset = 0;

	glGenTextures(1, &this->textureStack);
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->textureStack);

	glGenTextures(1, &this->bitmapTexture);
	glBindTexture(GL_TEXTURE_2D, this->bitmapTexture);

	glGenTextures(1, &this->cubeMapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->bitmapTexture);
};

void TextureLoader::extendTextureStack(int maxWidth, int maxHeight, int textureLayers)
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, this->textureStack);

	/* =========================================================================
		Allocate / Reallocate memory to store texture data. Doesn't actually 
		upload the texture yet, that's done later. Just (re)provisions room for 
		the incoming load.
	============================================================================ */
	glTexImage3D(
		GL_TEXTURE_2D_ARRAY, 											//	target
		0, 																//	mip level (0 because opengl is generating the mipmap)
		GL_RGBA8, 														//	internal format
		maxWidth, maxHeight,									 		//	width, height
		textureLayers, 													//	layers
		0, 																//	border, deprecated - always 0
		GL_RGBA, 														//	external format
		GL_UNSIGNED_BYTE, 												//	channel type
		NULL															//	pixel data, NULL because the texture will be subImage'd in later
	);

	this->checkErrors(__PRETTY_FUNCTION__);

	return;
};

void TextureLoader::loadImageToTextureStack(FileReader::Image imageData, GLuint textureLayer)
{	
	this->image.width = imageData.width;
	this->image.height = imageData.height;
	this->image.pixelData = imageData.pixelData;

	if(this->image.pixelData != NULL)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY, 									//	target
			0, 														// 	mipmap level (leave as 0 if openGL is generating the mipmaps)
			0, 0, 													// 	xy offset into the layer
			(textureLayer - 1), 									// 	layer depth to set this texture, zero-indexed
			this->image.width, this->image.height,					//	actual texture width / height
			1, 														// 	number of layers being passed each time this is called
			GL_RGBA, 												//	texel data format
			GL_UNSIGNED_BYTE, 										//	texel data type
			((const void *)(this->image.pixelData)) 				// 	texel data
		);
	
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	}

	this->checkErrors(__PRETTY_FUNCTION__);
};

void TextureLoader::storeCubeMap(int width, int height)
{
	glActiveTexture(GL_TEXTURE3);
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubeMapTexture);

	glTexImage2D(GL_TEXTURE_CUBE_MAP, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
};

void TextureLoader::loadCubeMap(std::vector<FileReader::Image> faces)
{
	
};

void TextureLoader::storeBitmapTexture(int maxWidth, int maxHeight)
{
	/* ===========================================
		Hardcoded because this function is used 
		specifically for glyph loading only. If 
		that ends up changing then it should be
		made dynamic. See other similar 
		glActiveTexture calls.
	============================================== */
	glActiveTexture(GL_TEXTURE1);
	
	glBindTexture(GL_TEXTURE_2D, this->bitmapTexture);

	/* ========================================================================================
		Allocate space for the texture atlas. The texture atlas hasn't been constructed yet so
		0 is passed in for the meantime. 

		Note the use of GL_R8. The glyphs are monocolour bitmaps and so are loaded into a 
		single-channel, which is later swizzled into the alpha value of a RGBA 4-channel color 
		on the GPU side. The swizzle can and probably should be done here to make it clearer.
	=========================================================================================== */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, maxWidth, maxHeight, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

	this->checkErrors(__PRETTY_FUNCTION__);

	this->offset = 0;
};

void TextureLoader::loadBitmapToTexture(FileReader::Image imageData)
{
	this->image.width = imageData.width;
	this->image.height = imageData.height;
	this->image.pixelData = imageData.pixelData;

	/* ================================================================
		Load the glyph's rendered bitmap into the previously allocated
		texture at an offset equal to the current width of the texture
		atlas.
	=================================================================== */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexSubImage2D(
		GL_TEXTURE_2D, 
		0, 
		this->offset, 
		0, 
		this->image.width, 
		this->image.height, 
		GL_RED, 
		GL_UNSIGNED_BYTE, 
		(void *)this->image.pixelData
	);

	offset += imageData.width;

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	
};

void TextureLoader::checkErrors(const char *invoker)
{
    this->errorCode = glGetError();
    
    if(this->errorCode != 0)
    {
        std::cerr << RED_TEXT << "ERROR::GL_ERROR::CODE " << RESET_TEXT << this->errorCode << std::endl;
        std::cerr << RED_TEXT << "INVOKED BY: " << RESET_TEXT << invoker << std::endl;

		globals.setExecutionState(LAZARUS_OPENGL_ERROR);
    } 

	return;
};

TextureLoader::~TextureLoader()
{
	std::cout << GREEN_TEXT << "Calling destructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;

	glDeleteTextures(1, &textureStack);
	glDeleteTextures(1, &bitmapTexture);
};
