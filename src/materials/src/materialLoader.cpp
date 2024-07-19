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
	#include "../../utils/hdr/constants.h"
#endif

#ifndef LAZARUS_GL_INCLUDES_H
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/materialLoader.h"

MaterialLoader::MaterialLoader()
{
	std::cout << GREEN_TEXT << "Constructing class 'MaterialLoader'." << RESET_TEXT << std::endl;
	diffuseTexCount = 0;
};

bool MaterialLoader::loadMaterial(string path, vector<vec3> &out, vector<vector<int>> data) 
{
    diffuseTexCount = 0;

    file.open(path.c_str());
    char identifier[128];                                                                                           //  Store for the first string of each line from the loaded file
    
    if( !file.is_open() )
    {                                                                                                               //  If, the file has a null value                                 
        return false;                                                                                               //  Return from the function, exit the thread
    }   

    while( file.getline(currentLine, 256) ) 
    {        
        if( (currentLine[0] == 'K') && (currentLine[1] == 'd') )                                                                        // If the first string of the current line is "Kd" the line holds a set of diffuse colors
        {
            diffuseTexCount += 1;
            for(auto i: data)
            {
            	int index = i[0];
            	int faceCount = i[1];
            	
	            if(diffuseTexCount == index) {
                    string currentString = currentLine;
                    stringstream ss(currentString);
                    string token;

                    vector<string> tokenStore;                                     //  Continue reading the line, the next 3 strings are mapped to a diffuse object in order of r,g,b
                    while(getline(ss, token, ' ')) 
                    {
                        tokenStore.push_back(token);
                    }

                    diffuse.r = stof(tokenStore[1]);
                    diffuse.g = stof(tokenStore[2]);
                    diffuse.b = stof(tokenStore[3]);

    	            for(int j = 0; j < faceCount * 3; j++)                                                       //  Where n = the number of vertex's using the color (number of triangles * 3)
    	            {
    	                out.push_back(diffuse);                                                                          //  Push the current diffuse object into the out array n times
    	            };
    	        };        
            };
        }
    }
    if (file.eof())                                                                                             //  If, the scanner has reached the end of the file
    {
        file.close();
    }
    return true;
};

MaterialLoader::~MaterialLoader()
{
    if( file.is_open() )
    {
        file.close();
    }
    std::cout << GREEN_TEXT << "Destroying 'MaterialLoader' class." << RESET_TEXT << std::endl;
};
