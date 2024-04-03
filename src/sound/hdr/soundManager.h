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
		void play();
		virtual ~SoundManager();
		
	private:
		void checkErrors(FMOD_RESULT res);

		unique_ptr<FileReader> reader;
		string path;

		FMOD_RESULT result;

		FMOD::System *system;
		FMOD::Sound *sound;
		FMOD::Channel *channel;
		FMOD::ChannelGroup *group;
};

#endif
