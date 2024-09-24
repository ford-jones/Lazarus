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

#include "../include/textureLoader.h"

TextureLoader::TextureLoader()
{
	std::cout << GREEN_TEXT << "Constructing class 'Texture'" << RESET_TEXT << std::endl;

	this->loader = nullptr;	

	this->image = {pixelData: NULL, height: 0, width: 0};
	this->textures = {};

	this->x = 0;
	this->y = 0;
	this->loopCount = 0;
	this->mipCount = 0;
	this->errorCode = 0;
};

void TextureLoader::storeTexture(string texturePath, GLuint &textureLayer, FileReader::Image &imageData)
{	
	this->loader = std::make_shared<FileReader>();
	this->image = loader->readFromImage(texturePath);
	
	if(this->image.pixelData != NULL)
	{	
		/* =========================================================================
			Note that the value given to textureLayer by glGenTextures serves a 
			number of different purposes here, namely:
			
			1. To specify the total expected texture-array length when the storage 
			   size is allocated / re-alloc'd
			2. As an identifier during texel loading for which layer / position in the 
			   array the loaded texels refer to.
			3. As a Mesh::TriangulatedMesh property which is converted to floating 
			   point and passed to the fragment shader as a uniform value; used to 
			   traverse the z-axis of the array (subnote: the array is a cube).

			i.e. size, index position & uniform value
		============================================================================ */
		glGenTextures(1, &textureLayer);
		glBindTexture(GL_TEXTURE_2D_ARRAY, textureLayer);

		this->mipCount = this->calculateMipLevels(image.width, image.height);

		glTexStorage3D(
			GL_TEXTURE_2D_ARRAY, 								//	target
			this->mipCount, 									//	the expected number of levels (mips) found in each layer
			GL_RGBA8, 											//	gl internal size to store texel data
			this->image.width, this->image.height, 				// 	expected (max) image width and height
			textureLayer 										// 	the number of layers to store (max array size)
		);

		imageData.width = this->image.width;
		imageData.height = this->image.height;
		imageData.pixelData = this->image.pixelData;
	}
	else
	{
		globals.setExecutionState(LAZARUS_FILE_NOT_FOUND);
		std::cout << RED_TEXT << "LAZARUS::ERROR::TEXTURE_LOADER" << std::endl;
		std::cout << "Status: " << globals.getExecutionState() << RESET_TEXT << std::endl;

		textureLayer = 0;

		imageData.width = 0;
        imageData.height = 0;
        imageData.pixelData = NULL;

		return;
	};

	/* ======================================
		Indexing through this texture vector 
		could become expensive at large sizes.

		A better implementation might make use
		of std::map (i.e. red-black BST).
	========================================= */
	
	this->textures.push_back(textureLayer);

	this->checkErrors(__PRETTY_FUNCTION__);

	return;
};

void TextureLoader::loadTexture(FileReader::Image imageData, GLuint textureLayer)
{
	if(imageData.pixelData != NULL)
	{
		this->image.width = imageData.width;
		this->image.height = imageData.height;
		this->image.pixelData = imageData.pixelData;

		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY, 
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

}

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

int TextureLoader::calculateMipLevels(int width, int height)
{
	this->loopCount = 0;

	this->x = width;
	this->y = height;

	this->loopCount += 1;

	while( 1 )
	{
		this->loopCount += 1;

		if(this->x != 1)
		{
			int xResult = floor(this->x / 2);
			this->x = xResult;
		}

		if (this->y != 1)
		{
			int yResult = floor(this->y / 2);
			this->y = yResult;
		}

		if ( (this->x == 1) && (this->y == 1) )
		{
			break;
		}
	}

	return this->loopCount;
}

TextureLoader::~TextureLoader()
{
	std::cout << GREEN_TEXT << "Destroying 'Texture' class." << RESET_TEXT << std::endl;

	for(unsigned int i = 0; i < this->textures.size(); i++) 
	{
		/* ========================================
			I dont *think* that index 0 of the
			textures vector should / would ever 
			actually be literal (int 0) but the 
			old code used to check for it so I've 
			left it here just in case.
		=========================================== */
		if(textures[0] != 0)
		{
			glDeleteTextures(1, &textures[i]);
		}
	}
};
