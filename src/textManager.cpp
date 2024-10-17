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

#include "../include/textManager.h"

TextManager::TextManager(GLuint shader)
{
    this->shaderProgram = shader;
    this->quad = std::make_shared<Mesh::TriangulatedMesh>();
    this->meshLoader = std::make_unique<Mesh>(this->shaderProgram);
    
    this->textureLoader = nullptr;
    this->fontLoader = nullptr;
    this->word = {};

    this->fontIndex = 0;
};

int TextManager::extendFontStack(std::string filepath, int width, int height)
{
    this->textureLoader = std::make_unique<TextureLoader>();
    this->fontLoader = std::make_unique<FontLoader>();
    
    fontLoader->initialise();

    this->fontIndex = fontLoader->loadFont(filepath, width, height);

    for(int i = 33; i < 128; i++)
    {
        glyph = fontLoader->loadCharacter(char(i), fontIndex);
        textureLoader->storeTexture(glyph, this->textureId, width, height);

        textures.insert(std::pair<GLuint, FileReader::Image>(textureId, glyph));
    };

    return fontIndex;
};

void TextManager::loadText(std::string targetText)
{
    for(char i: targetText)
    {   
        quad = meshLoader->createQuad(1.0, 1.0, LAZARUS_MESH_ISTEXT);

        quad->textureId = int(i);
        quad->textureData = textures[quad->textureId];

        word.push_back(quad);
    };

    return;
};

void TextManager::drawText()
{
    for(auto i: word)
    {
        quad.reset();
        quad = i;

        if(quad->modelviewUniformLocation >= 0)
        {            
            //  Translate mesh on x++ axis by a factor of (image.width * (index + 1))
            meshLoader->initialiseMesh(quad);
            meshLoader->loadMesh(quad);
            meshLoader->drawMesh(quad);
            continue;
        }
        else
        {
            globals.setExecutionState(LAZARUS_UNIFORM_NOT_FOUND);
            break;
        };
    };

    return;
};

TextManager::~TextManager()
{
    std::cout << "Destroying TextManager" << std::endl;
};