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

#include "../include/textManager.h"

TextManager::TextManager()
{
    this->symbolHeight = 0;
    this->symbolWidth = 0;

    this->fontLoader = nullptr;
};

TextManager::Text TextManager::loadText(string text, string fontPath, int symbolWidth, int symbolHeight)
{
    this->fontLoader = std::make_unique<FileReader>();
    this->symbolSet = fontLoader->readFromImage(fontPath);

    this->createQuad(symbolWidth, symbolHeight);

    FT_Init_FreeType(&this->freeType);
    FT_New_Face(this->freeType, fontPath.c_str(), 0, &this->fontFamily);

    for(unsigned int i = 0; i < text.size(); i++)
    {
        char current = text[i];
        FT_Load_Char(this->fontFamily, current, FT_LOAD_RENDER);
    }

    return this->text;
}

void TextManager::drawText(TextManager::Text text)
{

};

void TextManager::createQuad(int width, int height)
{
    
}

TextManager::~TextManager()
{

};