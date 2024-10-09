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
//                                        
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
#include <vector>

#include "shader.h"
#include "fontLoader.h"
#include "textureLoader.h"
#include "mesh.h"

#ifndef LAZARUS_TEXT_MANAGER_H
#define LAZARUS_TEXT_MANAGER_H

class TextManager
{
    public:
        TextManager(GLuint shader);
        int extendFontStack(std::string filepath, int width = 12, int height = 12);
        void loadText(std::string targetText);
        void drawText();
        virtual ~TextManager();

    private: 
        GlobalsManager globals;
        std::unique_ptr<Mesh> meshLoader;
        std::unique_ptr<TextureLoader> textureLoader;
        std::unique_ptr<FontLoader> fontLoader;

        unsigned int fontIndex;

        std::shared_ptr<Mesh::TriangulatedMesh> quad;

        FileReader::Image glyph;
        GLuint textureId;

        GLuint shaderProgram;

        std::vector<std::shared_ptr<Mesh::TriangulatedMesh>> word;

};

#endif
