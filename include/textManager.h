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
        int loadText(std::string targetText, int posX, int posY, int letterSpacing = 1, float red = 0.0f, float green = 0.0f, float blue = 0.0f);
        void drawText(int layoutIndex = 0);
        virtual ~TextManager();

    private: 
        void identifyAlphabetDimensions();
        void setActiveGlyph(char target, int spacing);
        void setTextColor(float r, float g, float b);
        void lookUpUVs(int keyCode);

        int translation;
        int targetKey;
        int targetXL;
        int targetXR;
        int span;

        int atlasX;
        int atlasY;

        float monitorWidth;

        float uvL;
        float uvR;
        float uvH;

        unsigned int fontIndex;
        unsigned int wordCount;

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
        std::map<int, FileReader::Image> textures;
        std::map<int, std::vector<std::shared_ptr<Mesh::TriangulatedMesh>>> layout;
        std::pair<int, std::vector<std::shared_ptr<Mesh::TriangulatedMesh>>> layoutEntry;
};

#endif
