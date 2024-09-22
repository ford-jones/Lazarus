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

#include "../include/fileReader.h"

FileReader::FileReader()
{
	this->imageData = 0;
    this->outResize = 0;
    this->outImage = {};
	this->x = 0;
	this->y = 0;
	this->n = 0;	
};

string FileReader::relativePathToAbsolute(string filename) 
{
    this->filenameString      =   fs::absolute(filename).string();                                              //  Find the absolute path from root (/) to the mesh asset and convert to std::string

    return this->filenameString;                                         //  Return the absolute path to the asset, exit the thread
};

const char *FileReader::readFromText(string filepath) 
{
    if(fs::exists(filepath))
    {
        this->absolutePath = this->relativePathToAbsolute(filepath);
        ifstream fileStream(absolutePath);

        if(fileStream.is_open())
        {
            this->stringstream << fileStream.rdbuf();

            this->contents = stringstream.str();
            this->textData = this->contents.c_str();
            return textData;
        } 
        else 
        {
            std::cout << RED_TEXT << "fileStream is not open" << RESET_TEXT << std::endl;
            return LAZARUS_FILESTREAM_CLOSED;
        };
    }
    else 
    {
        std::cout << RED_TEXT << "File doesn't exist" << RESET_TEXT << std::endl;
        return LAZARUS_FILE_NOT_FOUND;
    };
};

FileReader::Image FileReader::readFromImage(string filename)
{
	const char *img = filename.c_str();
	
    /* ====================================================
        Images should be flipped on load due to the fact that 
        most file formats store the (x: 0.0, y: 0.0) coordinate
        at the top left (first pixel of first row), while 
        OpenGL's texture coordinate system stores it as the
        inverse - i.e. bottom left (first pixel, last row).
    ======================================================= */
    stbi_set_flip_vertically_on_load(true);

	this->imageData = stbi_load(img, &x, &y, &n, 0);

    if(imageData != NULL) 
    {
        /* ================================================= 
            Evil solution (the correct way):

            The return value of stbir_resize_uint8, unlike 
            stbi_load is reserved for error codes. This means 
            that to pass data into lazarus' tightly-packed byte 
            array (unsigned char *) it has to do so as a side-
            effect. To do so the memory has to be allocated 
            manually so that we can pass stbir a pointer to the 
            actual byte array pointer.

            See: https://stackoverflow.com/a/65873156/23636614
        ==================================================== */

        outResize = (unsigned char *) malloc(500 * 500 * n);

        stbir_resize_uint8(imageData, x, y, 0, outResize, 500, 500, 0, n);

        //  TODO:
        //  Allow user to determine rescale size for scenes, otherwise dont rescale
        //  correctly check for errors, stbir_resize_uint8 returns an int errorcode
        
        if(outResize)
        {
            outImage.pixelData = outResize;
            outImage.height = 500;
            outImage.width = 500;
        }
        else 
        {
            outImage.pixelData = imageData;
            outImage.height = y;
            outImage.width = x;
            std::cerr << RED_TEXT << "LAZARUS::ERROR::FILEREADER::IMAGE_LOADER " << "Failed to rescale image." << RESET_TEXT << std::endl;    
        }

    }
	else
	{
        outImage.pixelData = NULL;
        outImage.height = 0;
        outImage.width = 0;

		std::cerr << RED_TEXT << "LAZARUS::ERROR::FILEREADER::IMAGE_LOADER " << stbi_failure_reason() << RESET_TEXT << std::endl;
	};
	
	return outImage;
};

FileReader::~FileReader()
{
	stbi_image_free(this->imageData);
    free(outResize);
};