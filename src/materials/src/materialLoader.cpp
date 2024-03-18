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

#ifndef __GLEW_H__
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/materialLoader.h"

MaterialLoader::MaterialLoader()
{
	std::cout << GREEN_TEXT << "Constructing class 'MaterialLoader'." << RESET_TEXT << std::endl;
	
	textureLoader = nullptr;
	diffuseTexCount = 0;
	file = NULL;
};

bool MaterialLoader::loadMaterial(vector<vec3> &out, vector<vector<int>> data ,string materialPath, string texturePath)
{
    diffuseTexCount = 0;
	this->textureLoader = std::make_unique<TextureLoader>();

    file = fopen(materialPath.c_str(), "r");                                                                                //  Open the file located at `path` with read permissions
    char identifier[128];                                                                                           //  Store for the first string of each line from the loaded file
    
    if( file == NULL )
    {                                                                                                               //  If, the file has a null value                                 
        return false;                                                                                               //  Return from the function, exit the thread
    }   

    while( 1 ) 
    {
        int res = fscanf(file, "%s", identifier);                                                                   //  initialise the file scanner

        if (res == EOF)                                                                                             //  If, the scanner has reached the end of the file
        {
            break;                                                                                                  //  Break out of the loop.
        }
        
        if( strcmp( identifier, "Kd") == 0 )                                                                        // If the first string of the current line is "Kd" the line holds a set of diffuse colors
        {
            diffuseTexCount += 1;
            for(auto i: data)
            {
            	int index = i[0];
            	int faceCount = i[1];
            	
	            if(diffuseTexCount == index) {
    	            fscanf(file, "%f %f %f\n", &diffuse.r, &diffuse.g, &diffuse.b);                                      //  Continue reading the line, the next 3 strings are mapped to a diffuse object in order of r,g,b

    	            for(int j = 0; j < faceCount * 3; j++)                                                       //  Where n = the number of vertex's using the color (number of triangles * 3)
    	            {
    	                out.push_back(diffuse);                                                                          //  Push the current diffuse object into the out array n times
    	            };
    	        };        
            };
        }
	    else if( strcmp( identifier, "map_Kd" ) == 0 )
    	{
			textureLoader->loadTexture(texturePath);
	    };
        
   };
   
   return true;
};

MaterialLoader::~MaterialLoader()
{
    fclose(file);                                                                                                   //  Close the file
    std::cout << GREEN_TEXT << "Destroying 'MaterialLoader' class." << RESET_TEXT << std::endl;
};
