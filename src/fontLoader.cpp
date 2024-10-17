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

#include "../include/fontLoader.h"

FontLoader::FontLoader()
{
    this->fileReader = nullptr;

    this->lib = NULL;
    this->fontFace = NULL;
    this->status = 0;

    this->fontStack = {};

    this->keyCode = 0;
    
    this->image.width = 0;
    this->image.height = 0;
    this->image.pixelData = NULL;
};

void FontLoader::initialise()
{
    status = FT_Init_FreeType(&lib);

    if(status != FT_Err_Ok)
    {
        std::cerr << RED_TEXT << "ERROR::FONTLOADER::INIT" << RESET_TEXT << std::endl;
        std::cerr << RED_TEXT << "Status: " << status << RESET_TEXT << std::endl;

        std::cerr << status << std::endl;
        globals.setExecutionState(LAZARUS_FT_NO_INIT);
    }
};

int FontLoader::loadFont(std::string filepath, int charHeight, int charWidth)
{
    fileReader = std::make_unique<FileReader>();
    absolutePath = fileReader->relativePathToAbsolute(filepath);

    status = FT_New_Face(lib, absolutePath.c_str(), 0, &fontFace);

    if(status != FT_Err_Ok)
    {
        std::cerr << RED_TEXT << "ERROR::FONTLOADER::LOADFONT" << RESET_TEXT << std::endl;
        std::cerr << RED_TEXT << "Status: " << status << RESET_TEXT << std::endl;

        globals.setExecutionState(LAZARUS_FILE_UNREADABLE);

        return -1;
    } 
    else 
    {
        FT_Set_Pixel_Sizes(fontFace, charWidth, charHeight);
        fontStack.push_back(fontFace);

        return (fontStack.size() - 1);
    }
};

FileReader::Image FontLoader::loadCharacter(char character, int fontIndex)
{
    this->fontFace = fontStack[fontIndex];
    this->keyCode = int(character);

    // this->glyphIndex = FT_Get_Char_Index(fontFace, keyCode);

    // status = FT_Load_Glyph(fontFace, glyphIndex, FT_LOAD_RENDER);
    status = FT_Load_Char(fontFace, keyCode, FT_LOAD_RENDER);

    if(status != FT_Err_Ok)
    {
        std::cerr << RED_TEXT << "ERROR::FONTLOADER::LOADCHAR" << RESET_TEXT << std::endl;
        std::cerr << RED_TEXT << "Status: " << status << RESET_TEXT << std::endl;

        globals.setExecutionState(LAZARUS_IMAGE_LOAD_FAILURE);

        this->image.width = 0;
        this->image.height = 0;
        this->image.pixelData = NULL;
    }
    else
    {
        this->image.width = fontFace->glyph->bitmap.width;
        this->image.height = fontFace->glyph->bitmap.rows;
        this->image.pixelData = fontFace->glyph->bitmap.buffer;
    }
    
    return this->image;
};

FontLoader::~FontLoader()
{
    FT_Done_Face(this->fontFace);
    FT_Done_FreeType(this->lib);
};
