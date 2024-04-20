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

#include <iostream>
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_common.h>
#include <fmod_codec.h>

#include <string>
#include <memory>

#include "../../utils/hdr/fileReader.h"

using std::unique_ptr;
using std::string;

#ifndef LAZARUS_SOUND_MANAGER_H
#define LAZARUS_SOUND_MANAGER_H

class SoundManager
{
	public:
		SoundManager();

		void init();
		void load(string filepath, bool is3D = false, int loopCount = 0);

		void togglePaused();
		void positionSource(float x, float y, float z);
		void positionListener(float x, float y, float z);

		virtual ~SoundManager();

		bool isPaused;
		

	private:
		void checkErrors(FMOD_RESULT res);

		unique_ptr<FileReader> reader;
		string path;

		FMOD_RESULT result;

		FMOD_VECTOR prevSourcePosition;
		FMOD_VECTOR currentSourcePosition;
		FMOD_VECTOR sourceVelocity;

		FMOD_VECTOR prevListenerPosition;
		FMOD_VECTOR currentListenerPosition;
		FMOD_VECTOR listenerVelocity;

		FMOD_VECTOR forward;
		FMOD_VECTOR up;

		FMOD::System *system;
		FMOD::Sound *sound;
		FMOD::Channel *channel;
		FMOD::ChannelGroup *group;
};

#endif