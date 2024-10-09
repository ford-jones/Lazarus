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
    this->meshLoader = nullptr;
    this->textureLoader = nullptr;
    this->fontLoader = nullptr;
    this->quad = nullptr;
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
        std::cout << "Keycode: " << char(i) << std::endl;
        this->glyph = fontLoader->loadCharacter(char(i), fontIndex);
        std::cout << "Glyph width: " << glyph.width << std::endl;
        textureLoader->storeTexture(glyph, this->textureId);
    };

    return fontIndex;
};

//  Needs font index?
void TextManager::loadText(std::string targetText)
{
    // std::cout << GREEN_TEXT << "targetText @:"<< __PRETTY_FUNCTION__ << RESET_TEXT << targetText << std::endl;
    for(char i: targetText)
    {   
        this->meshLoader = std::make_unique<Mesh>(this->shaderProgram);
        this->quad = std::make_shared<Mesh::TriangulatedMesh>();

        quad = meshLoader->createQuad(1.0, 1.0, LAZARUS_MESH_ISTEXT);

        // std::cout << GREEN_TEXT << "Filepath @:"<< __PRETTY_FUNCTION__ << RESET_TEXT << quad->textureFilepath << std::endl;

        quad->textureId = int(i);

        word.push_back(quad);
    };

    return;
};

void TextManager::drawText()
{
    for(auto i: word)
    {
        if(i->modelviewUniformLocation >= 0)
        {
            meshLoader.reset();
            std::cout << "Trying to draw texture: " << i->textureId << std::endl;
            quad = i;
            meshLoader->initialiseMesh(quad);
            meshLoader->loadMesh(quad);
            //  Translate mesh on x++ axis by a factor of (image.width * (index + 1))
            meshLoader->drawMesh(quad);
        }
        else
        {
            globals.setExecutionState(LAZARUS_UNIFORM_NOT_FOUND);
        }
        
    };

    return;
};

TextManager::~TextManager()
{
    std::cout << "Destroying TextManager" << std::endl;
};