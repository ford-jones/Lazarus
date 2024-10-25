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
    std::cout << GREEN_TEXT << "Calling constructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;
    this->fileReader = nullptr;

    this->lib = NULL;
    this->fontFace = NULL;
    this->status = 0;

    this->fontStack = {};

    this->keyCode = 0;
    
    this->setImageData(0, 0, NULL);
};

void FontLoader::initialise()
{
    status = FT_Init_FreeType(&lib);

    if(status != FT_Err_Ok)
    {
        std::cerr << RED_TEXT << "ERROR::FONTLOADER::INIT" << RESET_TEXT << std::endl;
        std::cerr << RED_TEXT << "Status: " << status << RESET_TEXT << std::endl;

        std::cerr << status << std::endl;
        globals.setExecutionState(LAZARUS_FT_INIT_FAILURE);
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
        FT_Set_Pixel_Sizes(fontFace, 0, charHeight);

        fontStack.push_back(fontFace);

        return (fontStack.size() - 1);
    }
};

FileReader::Image FontLoader::loadCharacter(char character, int fontIndex)
{
    this->fontFace = fontStack[fontIndex];
    this->keyCode = int(character);

    this->flipGlyph();

    this->glyphIndex = FT_Get_Char_Index(fontFace, keyCode);
    status = FT_Load_Glyph(fontFace, glyphIndex, FT_LOAD_DEFAULT);

    if(status != FT_Err_Ok)
    {
        std::cerr << RED_TEXT << "ERROR::FONTLOADER::LOADCHAR" << RESET_TEXT << std::endl;
        std::cerr << RED_TEXT << "Status: " << status << RESET_TEXT << std::endl;

        globals.setExecutionState(LAZARUS_FT_LOAD_FAILURE);

        this->setImageData(0, 0, NULL);
    }
    else
    {
        this->createBitmap();
    }

    return this->image;
};

void FontLoader::createBitmap()
{
    status = FT_Render_Glyph(fontFace->glyph, FT_RENDER_MODE_NORMAL);

    if(status != FT_Err_Ok)
    {
        globals.setExecutionState(LAZARUS_FT_RENDER_FAILURE);

        this->setImageData(0, 0, NULL);
    }
    else
    {
        this->setImageData(
            fontFace->glyph->bitmap.width, 
            fontFace->glyph->bitmap.rows, 
            fontFace->glyph->bitmap.buffer
        );
    };
};

void FontLoader::setImageData(int width, int height, unsigned char *data)
{
    this->image.width = width;
    this->image.height = height;
    this->image.pixelData = data;
};

void FontLoader::flipGlyph()
{
    FT_Vector pixelStore;

    pixelStore.x = 1 * 64;
    pixelStore.y = 1 * 64;

    /* =========================================
        Construct a transformation matrix used to
        flip the glyph vertically. This is to 
        accomidate OpenGL's cartesian coordinate
        system (0.0 being bottom left instead of top 
        left).
    ============================================ */
    transformationMatrix.xx = (FT_Fixed)( cos( 0.0f ) * 0x10000L );
    transformationMatrix.xy = (FT_Fixed)(-sin( 0.0f ) * 0x10000L );
    transformationMatrix.yx = (FT_Fixed)( sin( 0.0f ) * 0x10000L );
    transformationMatrix.yy = (FT_Fixed)( cos( 180.0f ) * 0x10000L );

    FT_Set_Transform( fontFace, &transformationMatrix, &pixelStore);

    /* ==========================================
        Advance the pen / cursor / locator to the 
        end of the active glyph's coordinates to 
        be properly placed for next glyph load.
    ============================================= */
    pixelStore.x += fontFace->glyph->advance.x;
    pixelStore.y += fontFace->glyph->advance.y;
};

FontLoader::~FontLoader()
{
    std::cout << GREEN_TEXT << "Calling destructor @: " << __PRETTY_FUNCTION__ << RESET_TEXT << std::endl;

    FT_Done_Face(this->fontFace);
    FT_Done_FreeType(this->lib);
};
