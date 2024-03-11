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

string FileReader::findFile(string filename) 
{
    this->filenameString      =   fs::absolute(filename).string();                                              //  Find the absolute path from root (/) to the mesh asset and convert to std::string

    this->fileVec.push_back(this->filenameString);                                                                     //  Push the absolute path into a temporary storage buffer
    return this->filenameString;                                         //  Return the absolute path to the asset, exit the thread
};

unsigned char *FileReader::loadImage(string filename)
{
	const char *img = filename.c_str();
	
	this->imageData = stbi_load(img, &x, &y, &n, 0);
	
	//	TODO:
	//	Add this to the error checker class
	if(imageData == NULL)
	{
		std::cout << RED_TEXT << "LAZARUS::ERROR::FILEREADER::IMAGE_LOADER " << stbi_failure_reason() << RESET_TEXT << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Width: " << x << std::endl;
		std::cout << "Height: " << y << std::endl;
	};
	
	return imageData;
};

const char *FileReader::readShader(string filename)
{
    path = "src/shaders/" + filename;

    if(fs::exists(path))
    {
        absolutePath = fs::absolute(path).string();  
        ifstream fileStream(absolutePath);

        if(fileStream.is_open())
        {
            stringstream << fileStream.rdbuf();

            contents = stringstream.str();
            return contents.c_str();
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

FileReader::~FileReader()
{
	stbi_image_free(this->imageData);
};
