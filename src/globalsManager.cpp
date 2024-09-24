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

#include "../include/globalsManager.h"

void GlobalsManager::setEnforceImageSanity(bool shouldEnforce)
{
    LAZARUS_ENFORCE_IMAGE_SANITY = shouldEnforce;

    return;
};

bool GlobalsManager::getEnforceImageSanity()
{
    return LAZARUS_ENFORCE_IMAGE_SANITY;
}

void GlobalsManager::setMaxImageSize(int width, int height)
{
    LAZARUS_MAX_IMAGE_WIDTH = width;
    LAZARUS_MAX_IMAGE_HEIGHT = height;

    return;
};

int GlobalsManager::getMaxImageWidth() 
{
    return LAZARUS_MAX_IMAGE_WIDTH;
}

int GlobalsManager::getMaxImageHeight() 
{
    return LAZARUS_MAX_IMAGE_HEIGHT;
}

void GlobalsManager::setExecutionState(int state)
{
    LAZARUS_EXECUTION_STATUS = state;
    
    return;   
};

int GlobalsManager::getExecutionState()
{
    return LAZARUS_EXECUTION_STATUS;
}
