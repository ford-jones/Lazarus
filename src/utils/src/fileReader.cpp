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

#include "../hdr/fileReader.h"
#include <string>
#include <fstream>
#include <iostream>

#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[37m"
#define RED_TEXT  "\x1b[31m"

using std::ifstream;
using std::string;

const char *FileReader::readShader(string filename)
{
    path = "src/shaders/" + filename;

    if(fs::exists(path))
    {
        absolutePath = fs::absolute(path).string();  
        ifstream fileStream(absolutePath);

        if(fileStream.is_open())
        {
            stringstream << fileStream.rdbuf();

            contents = stringstream.str();
            return contents.c_str();
        } else {
            std::cout << RED_TEXT << "fileStream is not open" << RESET_TEXT << std::endl;
        }
    } else {
        std::cout << RED_TEXT << "File doesn't exist" << RESET_TEXT << std::endl;
    }
}