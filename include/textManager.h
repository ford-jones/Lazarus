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
#include <algorithm>
#include <vector>
#include <map>

#include "shader.h"
#include "camera.h"
#include "fontLoader.h"
#include "textureLoader.h"
#include "transforms.h"
#include "mesh.h"

#ifndef LAZARUS_TEXT_MANAGER_H
#define LAZARUS_TEXT_MANAGER_H

class TextManager
{
    public:
        TextManager(GLuint shader);
        int extendFontStack(std::string filepath, int ptSize = 12);
        void loadText(std::string targetText, float red, float green, float blue, int posX, int posY, int letterSpacing = 1);
        void drawText();
        virtual ~TextManager();

    private: 
        void identifyAlphabetDimensions();
        void lookUpUVs(int keyCode);

        int atlasX;
        int atlasY;

        float uvL;
        float uvR;
        float uvH;

        unsigned int fontIndex;

        GLuint textureId;
        GLuint shaderProgram;

        glm::vec3 textColor;

        Transform transformer;
        GlobalsManager globals;
        FileReader::Image glyph;

        std::unique_ptr<Mesh> meshLoader;
        std::unique_ptr<TextureLoader> textureLoader;
        std::unique_ptr<FontLoader> fontLoader;
        std::unique_ptr<Camera> cameraBuilder;

        std::shared_ptr<Mesh::TriangulatedMesh> quad;
        std::shared_ptr<Camera::FixedCamera> camera;

        std::vector<std::shared_ptr<Mesh::TriangulatedMesh>> word;
        std::map<GLuint, FileReader::Image> textures;
};

#endif
