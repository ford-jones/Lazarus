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
    this->status = NULL;

    this->fontStack = {};

    this->keyCode = 0;
};

void FontLoader::initialise()
{
    status = FT_Init_FreeType(&lib);

    if(status != FT_Err_Ok)
    {
        std::cerr << status << std::endl;
        globals.setExecutionState(LAZARUS_FT_NO_INIT);
    }
};

int FontLoader::loadFont(std::string filepath, int charHeight, int charWidth)
{
    fileReader = std::make_unique<FileReader>();
    absolutePath = (fileReader->relativePathToAbsolute(filepath)).c_str();

    status = FT_New_Face(lib, absolutePath, 0, &fontFace);

    if(status != FT_Err_Ok)
    {
        std::cerr << status << std::endl;
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

    this->glyphIndex = FT_Get_Char_Index(fontFace, keyCode);

    status = FT_Load_Glyph(fontFace, glyphIndex, FT_LOAD_RENDER);

    if(status != FT_Err_Ok)
    {
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