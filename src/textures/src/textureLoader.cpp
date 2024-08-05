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

#ifndef __GLEW_H__
    #include "../../utils/hdr/gl_includes.h"
#endif

#ifndef LAZARUS_CONSTANTS_H
	#include "../../utils/hdr/constants.h"
#endif

#include "../hdr/textureLoader.h"

TextureLoader::TextureLoader()
{
	std::cout << GREEN_TEXT << "Constructing class 'Texture'" << RESET_TEXT << std::endl;

	this->loader = nullptr;	

	this->image = {pixelData: NULL, height: 0, width: 0};
	this->texture = 0;

	this->x = 0;
	this->y = 0;
	this->loopCount = 0;
};

void TextureLoader::loadTexture(string texturePath, GLuint &textureId)
{	
	this->loader = std::make_shared<FileReader>();
	this->image = loader->readFromImage(texturePath);
	
	glEnable(GL_TEXTURE_2D_ARRAY);
	glGenTextures(1, &textureId);

	glActiveTexture(GL_TEXTURE0 + (textureId - 1));
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureId);
	if(image.pixelData != NULL)
	{	
		int mipCount = this->calculateMipLevels(image.width, image.height);

		//	TODO:
		//	Image sanitisation 
		//  establish constant values to be passed for the following alloc
		//	i.e. mipcount, w, h, numOfTex

		glTexStorage3D(
			GL_TEXTURE_2D_ARRAY, 
			mipCount, 
			GL_RGB8, 
			image.width, image.height, 
			textureId // the number of layers to store
		);
		// glTexImage3D(
		// 	GL_TEXTURE_2D_ARRAY, 
		// 	mipCount, 
		// 	GL_RGB8, 
		// 	image.width, image.height, 
		// 	textureId, 
		// 	0, 
		// 	GL_RGBA, 
		// 	GL_UNSIGNED_BYTE, 
		// 	((const void *)(image.pixelData))
		// );

		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY, 
			0, // mipmap level (leave as 0 if openGL is generating the mipmaps)
			0, 0, // xy offset into the layer
			(textureId - 1), // layer depth, in a loop this is i (texId is a unique serial)
			image.width, image.height,
			1, // number of layers being passed each time this is called
			GL_RGBA, 
			GL_UNSIGNED_BYTE, 
			((const void *)(image.pixelData)) // texels
		);

		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}
	else
	{
		std::cerr << LAZARUS_FILE_NOT_FOUND << std::endl;
	};
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
	
	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &this->texture);
};
