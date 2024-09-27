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

void GlobalsManager::setCursorHidden(bool shouldHide)
{
    LAZARUS_DISABLE_CURSOR_VISIBILITY = shouldHide;

    return;
}

bool GlobalsManager::getCursorHidden()
{
    return LAZARUS_DISABLE_CURSOR_VISIBILITY;
}

void GlobalsManager::setBackFaceCulling(bool shouldCull)
{
    LAZARUS_CULL_BACK_FACES = shouldCull;

    return;
}

bool GlobalsManager::getBackFaceCulling()
{
    return LAZARUS_CULL_BACK_FACES;
}

void GlobalsManager::setDepthTest(bool shouldTest)
{
    LAZARUS_DEPTH_TEST_FRAGS = shouldTest;

    return;
}

bool GlobalsManager::getDepthTest()
{
    return LAZARUS_DEPTH_TEST_FRAGS;
}

void GlobalsManager::setContextWindowOpen(bool isOpen)
{
    LAZARUS_MAIN_WIN_OPEN = isOpen;

    return;
}

bool GlobalsManager::getContextWindowOpen()
{
    return LAZARUS_MAIN_WIN_OPEN;
}