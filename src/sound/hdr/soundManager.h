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

//	TODO:
//	(1) Init:
//	-	Configure the 3D environment using `System`
//	-	Create a system callback and check for errors
//
//	(2) Ambient sound:
//	-	Rename `play()` to `playAmbientSound()`, this function will be used to just play stuff as if it were itunes or something		
//
//	(3) Locative sound:
//	-	Create a function called `playLocativeSound()`, this function will be used to play a sound from somewhere in worldspace and hear it through a listener
//	-	Retrieve the `Channel` from the `ChannelGroup` and use it to modify the position of the sounds source and the position of the listener
//	-	The function should accept the source pos (xyz), listener pos (xyz),  min & max distance as arguments

class SoundManager
{
	public:
		SoundManager();

		void init();
		void load(string filepath, bool is3D);

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

		FMOD_VECTOR testPos;
		FMOD_VECTOR testVel;

		FMOD::System *system;
		FMOD::Sound *sound;
		FMOD::Channel *channel;
		FMOD::ChannelGroup *group;
};

#endif