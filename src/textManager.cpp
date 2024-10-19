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
    std::cout << GREEN_TEXT << "Calling constructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
    this->shaderProgram = shader;
    this->quad = std::make_shared<Mesh::TriangulatedMesh>();
    this->meshLoader = std::make_unique<Mesh>(this->shaderProgram);
    
    this->textureLoader = nullptr;
    this->fontLoader = nullptr;
    this->word = {};

    this->fontIndex = 0;

    this->atlasX = 0;
    this->atlasY = 0;
};

int TextManager::extendFontStack(std::string filepath, int ptSize)
{
    this->textureLoader = std::make_unique<TextureLoader>();
    this->fontLoader = std::make_unique<FontLoader>();
    
    fontLoader->initialise();

    this->fontIndex = fontLoader->loadFont(filepath, ptSize, 0);

    this->identifyAlphabetDimensions();

    textureLoader->storeBitmapTexture(atlasX, atlasY);

    for(int i = 33; i < 128; i++)
    {
        glyph = fontLoader->loadCharacter(char(i), fontIndex);
        textureLoader->loadBitmapToTexture(glyph);

        textures.emplace(textureId, glyph);
    };

    return fontIndex;
};

void TextManager::loadText(std::string targetText)
{
    int winWidth = globals.getDisplayWidth();
    int winHeight = globals.getDisplayHeight();

    // glm::mat4 orthProjection = glm::ortho(0.0f, float(winHeight), 0.0f, float(winHeight));
    // glUniformMatrix4fv     (glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, &orthProjection[0][0]);                                          //  Pass projection-uniform data into the shader program

    for(char i: targetText)
    {   
        // quad = meshLoader->createQuad((quad->textureData.width * (2.0f / winWidth)), (quad->textureData.height * (2.0f / winHeight)), LAZARUS_MESH_ISTEXT);
        quad = meshLoader->createQuad(1.0f, 1.0f, LAZARUS_MESH_ISTEXT);

        quad->textureId = int(i);
        quad->textureData = textures[quad->textureId];

        word.push_back(quad);
    };

    return;
};

void TextManager::identifyAlphabetDimensions()
{
    for(int i = 33; i < 128; i++)
    {
        glyph = fontLoader->loadCharacter(char(i), fontIndex);
        
        atlasX += glyph.width;
        atlasY = std::max(atlasY, glyph.height);
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
        std::cout << GREEN_TEXT << "Calling destructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
};