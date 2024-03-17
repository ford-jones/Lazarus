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

#ifndef LAZARUS_CONSTANTS_H
	#include "../hdr/constants.h"
#endif

#include "../hdr/fileReader.h"

FileReader::FileReader()
{
	this->imageData = 0;
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

//	TODO:
//	This function should also make accessible the returned cursor size values
//	Currently the user has to know the cursor images actual size
//	Preferably they could access it from here and pass it as an argument to WindowManager::createCursor()

unsigned char *FileReader::readFromImage(string filename)
{
	const char *img = filename.c_str();
	
	this->imageData = stbi_load(img, &x, &y, &n, 0);
	
	//	TODO:
	//	Add this to the error checker class
	
	if(imageData == NULL)
	{
		std::cout << RED_TEXT << "LAZARUS::ERROR::FILEREADER::IMAGE_LOADER " << stbi_failure_reason() << RESET_TEXT << std::endl;
		return 0;
	};
	
	return imageData;
};

FileReader::~FileReader()
{
	stbi_image_free(this->imageData);
};
