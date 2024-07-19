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
	this->image = NULL;
	this->texture = 0;
};

void TextureLoader::loadTexture(string texturePath)
{
	std::cout << "Filepath: " << texturePath << std::endl;
	
	this->loader = std::make_shared<FileReader>();
	this->image = loader->readFromImage(texturePath);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &this->texture);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	
	if(image != NULL)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 320, 239, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		// glGenerateTextureMipmap(this->texture);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	
		// glBindTextureUnit(1, this->texture);
		glBindTexture(GL_TEXTURE_2D, this->texture);
	}
	else
	{
		std::cout << LAZARUS_FILE_NOT_FOUND << std::endl;
	};
};

TextureLoader::~TextureLoader()
{
	std::cout << GREEN_TEXT << "Destroying 'Texture' class." << RESET_TEXT << std::endl;
	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &this->texture);
};
