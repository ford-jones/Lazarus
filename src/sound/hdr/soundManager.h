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
//	(1) Update docs:
//	-	Create an account on FMOD
//	-	Download the binaries
//	-	Move lib stuff to your program files (look this up, os specific. Right now it's stored in /usr/local/lib/. I think on windows it's \ Program Files \)
//	-	Move header stuff to include files (currently /usr/local/include/)
//	-	Run ldconfig
//
//	(2) Init:
//	-	Configure the 3D environment using `System`
//	-	Create a `ChannelGroup`
//	-	Retrieve the `Channel` from `System::play_sound()`
//	-	Create a system callback and check for errors
//
//	(3) Ambient sound:
//	-	Rename `play()` to `playAmbientSound()`, this function will be used to just play stuff as if it were itunes or something		
//
//	(4) Locative sound:
//	-	Create a function called `playLocativeSound()`, this function will be used to play a sound from somewhere in worldspace and hear it through a listener
//	-	Retrieve the `Channel` from the `ChannelGroup` and use it to modify the position of the sounds source and the position of the listener
//	-	The function should accept the source pos (xyz), listener pos (xyz),  min & max distance as arguments

class SoundManager
{
	public:
		SoundManager();
		void init();
		void load(string filepath);
		void play();
		virtual ~SoundManager();
		
	private:
		unique_ptr<FileReader> reader;
		FMOD::System *system;
		FMOD::Sound *sound;
		FMOD::Channel *channel;
		FMOD::ChannelGroup *group;
		FMOD_RESULT result;
		string path;
};

#endif
