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

#ifndef LAZARUS_GLOBALS_MANAGER_H
	#include "globalsManager.h"
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
		void extendTextureStack(int maxWidth, int maxHeight, GLuint &textureLayer);
		void loadImageToTextureStack(FileReader::Image imageData, GLuint textureLayer);

		void storeBitmapTexture(int maxWidth, int maxHeight, GLuint &textureLayer);
		void loadBitmapToTexture(FileReader::Image imageData);

		virtual ~TextureLoader();
		
	private:
		int calculateMipLevels(int width, int height);
		void checkErrors(const char *invoker);

		shared_ptr<FileReader> loader;

		FileReader::Image image;
		
		vector<GLuint> textures;
		GLuint bitmapTexture;

		GLenum errorCode;
		
		int mipCount;
		int loopCount;
		int x, y;

		int offset;

		GlobalsManager globals;
};

#endif
