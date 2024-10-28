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
    this->cameraBuilder = std::make_unique<Camera>(this->shaderProgram);
    
    this->camera = nullptr;
    this->textureLoader = nullptr;
    this->fontLoader = nullptr;
    this->word = {};

    this->textColor = glm::vec3(0.0f, 0.0f, 0.0f);

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

void TextManager::loadText(std::string targetText, float red, float green, float blue)
{
    int winWidth = globals.getDisplayWidth();
    int winHeight = globals.getDisplayHeight();

    textColor = glm::vec3(red, green, blue);
    glUniform3fv(glGetUniformLocation(this->shaderProgram, "textColor"), 1, &textColor[0]);

    int translation = 0;

    for(unsigned int i = 0; i < targetText.size(); i++)
    {   
        // quad = meshLoader->createQuad((quad->textureData.width * (2.0f / winWidth)), (quad->textureData.height * (2.0f / winHeight)), LAZARUS_MESH_ISTEXT);
        this->lookUpUVs(static_cast<int>(targetText[i]));
        this->glyph = textures.at(static_cast<int>(targetText[i]));

        quad = meshLoader->createQuad(static_cast<float>(this->glyph.width), static_cast<float>(this->glyph.height), LAZARUS_MESH_ISTEXT, this->uvL, this->uvR, this->uvH);
        
        quad->isGlyph = 1;
        quad->textureId = this->textureId;
        quad->textureData = this->glyph;

        transformer.translateMeshAsset(quad, static_cast<float>(translation), 0.0f, 0.0f);
        translation += this->glyph.width;

        word.push_back(quad);
    };

    return;
};

void TextManager::drawText()
{
    this->camera = cameraBuilder->createOrthoCam(globals.getDisplayWidth(), globals.getDisplayHeight());
    
    for(auto i: word)
    {
        quad.reset();
        quad = i;

        if(quad->modelviewUniformLocation >= 0)
        {            
            cameraBuilder->loadCamera(camera);

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