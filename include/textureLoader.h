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
#ifndef LAZARUS_GL_INCLUDES_H
    #include "gl_includes.h"
#endif

#ifndef LAZARUS_CONSTANTS_H
	#include "constants.h"
#endif

#include <iostream>
#include <string>
#include <memory>
#include <cmath>
#include <vector>

#include "fileReader.h"

using std::string;
using std::shared_ptr;
using std::vector;

#ifndef LAZARUS_TEXTURE_LOADER_H
#define LAZARUS_TEXTURE_LOADER_H

class TextureLoader
{
	public:
		TextureLoader();
		void storeTexture(string texturePath, GLuint &textureLayer, FileReader::Image &imageData);
		void loadTexture(FileReader::Image imageData, GLuint textureLayer);
		virtual ~TextureLoader();
		
	private:
		int calculateMipLevels(int width, int height);
		void checkErrors(const char *invoker);

		shared_ptr<FileReader> loader;

		FileReader::Image image;
		
		vector<GLuint> textures;
		GLenum errorCode;
		
		int mipCount;
		int loopCount;
		int x, y;
};

#endif
