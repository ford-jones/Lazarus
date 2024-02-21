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

#include <iostream>
#include <stdlib.h>

using glm::vec3;

#ifndef LAZARUS_LIGHT_H
#define LAZARUS_LIGHT_H

class Light
{
    public:
        struct AmbientLight
        {
            int id;

            vec3 lightPosition;                     //  The (x,y,z) location of the light source
            vec3 lightColor;                        //  The (r,g,b) color of the light

            GLuint lightPositionUniformLocation;    //  The location / index of the light position uniform inside the frag shader
            GLuint lightColorUniformLocation;       //  The location / index of the light color uniform inside the frag shader
        };

        AmbientLight createAmbientLight(GLuint shader, double x, double y, double z, double r, double g, double b);
        void initialiseLight(AmbientLight lightData);

    private:
        AmbientLight ambientLight;
        
};

#endif