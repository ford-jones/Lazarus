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

    this->uvL = 0.0;
    this->uvR = 0.0;
    this->uvH = 0.0;
};

int TextManager::extendFontStack(std::string filepath, int ptSize)
{
    this->textureLoader = std::make_unique<TextureLoader>();
    this->fontLoader = std::make_unique<FontLoader>();
    
    fontLoader->initialise();

    this->fontIndex = fontLoader->loadFont(filepath, ptSize, 0);

    this->identifyAlphabetDimensions();

    glUniform1i(glGetUniformLocation(this->shaderProgram, "fontStack"), 1);
    textureLoader->storeBitmapTexture(atlasX, atlasY, this->textureId);

    for(int i = 33; i < 128; i++)
    {
        glyph = fontLoader->loadCharacter(char(i), fontIndex);
        textureLoader->loadBitmapToTexture(glyph);

        textures.emplace((i - 33), glyph);
    };

    return fontIndex;
};

void TextManager::loadText(std::string targetText)
{
    int winWidth = globals.getDisplayWidth();
    int winHeight = globals.getDisplayHeight();

    // glm::mat4 orthProjection = glm::ortho(0.0f, float(winHeight), 0.0f, float(winHeight));
    // glUniformMatrix4fv     (glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, &orthProjection[0][0]);                                          //  Pass projection-uniform data into the shader program

    for(unsigned int i = 0; i < targetText.size(); i++)
    {   
        // quad = meshLoader->createQuad((quad->textureData.width * (2.0f / winWidth)), (quad->textureData.height * (2.0f / winHeight)), LAZARUS_MESH_ISTEXT);
        this->lookUpUVs(static_cast<int>(targetText[i]));

        std::cout << "Uv X @: " << __PRETTY_FUNCTION__ << uvL << std::endl;
        std::cout << "Uv Y @: " << __PRETTY_FUNCTION__ << uvH << std::endl;

        quad = meshLoader->createQuad(1.0f, 1.0f, LAZARUS_MESH_ISTEXT, this->uvL, this->uvR, this->uvH);
        
        quad->isGlyph = 1;
        quad->textureId = this->textureId;
        quad->textureData = textures.at(static_cast<int>(targetText[i]));

        transformer.translateMeshAsset(quad, (1.0f * (i + 1)), 0.0f, 0.0f);

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

void TextManager::lookUpUVs(int keyCode)
{
    /* =======================================
        Skip control keys
    ========================================== */
    int span = keyCode - 33;
    int count = 0;

    int targetXL = 0;
    int targetXR = 0;
    int targetY = 0;

    while(count < span)
    {
        this->glyph = textures.at(count);
        count += 1;

        int cullY = (atlasY - glyph.height);

        targetXL += glyph.width;
        targetY = atlasY - cullY;
    };

    this->glyph = textures.at(keyCode);

    targetXR = targetXL + this->glyph.width;

    this->uvL = static_cast<float>(targetXL) / static_cast<float>(atlasX);
    this->uvR = static_cast<float>(targetXR) / static_cast<float>(atlasX);
    this->uvH = static_cast<float>(targetY) / static_cast<float>(atlasY);
};

TextManager::~TextManager()
{
        std::cout << GREEN_TEXT << "Calling destructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
};