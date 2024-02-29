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
	#include "../hdr/gl_includes.h"
#endif

#include "../hdr/fpsCounter.h"

void FpsCounter::calculateFramesPerSec()
{	
	// 	TODO:
	//	loading of assets(?) currently increments the ms value of durationTillRendered from 16 to 18 (decreases fps from 60-50) (%12.5). 
	//	This observable "hump" on init should be documented under known caveats. 
	
	this->numberOfFrames++;	
	this->currentMs = glfwGetTime();
	
	this->timePassed = (this->currentMs - this->prevMs);
	
	if(this->timePassed >= 1.0)
	{
		this->framesPerSecond = this->numberOfFrames;
		this->durationTillRendered=(1000 / this->numberOfFrames);
		
		this->numberOfFrames = 0;
		this->prevMs += 1.0;
	};
};
