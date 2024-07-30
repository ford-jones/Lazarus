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


#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#include <stb_image.h>

namespace fs = std::filesystem;

using std::ifstream;
using std::string;
using std::vector;

#ifndef PATHFINDER_H
#define PATHFINDER_H

class FileReader 
{
    public:
		FileReader();
        
        struct Image 
        {
            unsigned char *pixelData;

            int height;
            int width;
        };

		string relativePathToAbsolute(string filepath);
        Image readFromImage(string filepath);
        const char *readFromText(string filepath);
        
		int x, y, n;
        virtual ~FileReader();

        
	private:
		unsigned char *imageData;
		const char *textData;
		
        std::stringstream stringstream;
        fs::path path;
        
        string contents;
        string absolutePath;
        
        string filenameString;

        Image outImage;
};

#endif
