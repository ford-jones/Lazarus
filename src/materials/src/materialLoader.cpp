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

#ifndef __GLEW_H__
    #include "../../utils/hdr/gl_includes.h"
#endif

#include "../hdr/materialLoader.h"

string MaterialLoader::findMaterial(char *filename)
{
    fs::path fn     =   "assets/material/" + string(filename);                                                      //  Create a target path, comprised of the target file's name prefixed by it's directory
    string fns      =   fs::absolute(fn).string();                                                                  //  Find the absolute path from root (/) to the mesh asset and convert to std::string

    return fns;                                                                                                     //  Return the absolute path, exit the thread
};

bool MaterialLoader::loadMaterial(string path, vector<vec3> &out, int numOfTri, int materialIdentificationIndex) 
{
    diffuseTexCount = 0;

    file = fopen(path.c_str(), "r");                                                                                //  Open the file located at `path` with read permissions
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
            
            if(diffuseTexCount == materialIdentificationIndex) {
                fscanf(file, "%f %f %f\n", &diffuse.r, &diffuse.g, &diffuse.b);                                      //  Continue reading the line, the next 3 strings are mapped to a diffuse object in order of r,g,b

                for(unsigned int i = 0; i < numOfTri * 3; i++)                                                       //  Where n = the number of vertex's using the color (number of triangles * 3)
                {
                    out.push_back(diffuse);                                                                          //  Push the current diffuse object into the out array n times
                }
            }
        }
    }
    fclose(file);                                                                                                   //  Close the file
    return true;
};
