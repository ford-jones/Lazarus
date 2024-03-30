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

#include <FMOD/fmod.h>
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_common.h>
#include <FMOD/fmod_codec.h>

#include <string>
#include <memory>

#include "../../utils/hdr/fileReader.h"

using std::unique_ptr;
using std::string;

#ifndef LAZARUS_SOUND_MANAGER_H
#define LAZARUS_SOUND_MANAGER_H

//	TODO:
//	1. Find and link the static library, this is close but no cigar
//	2. Update docs
//	3. Create a script for makefile which locates FMOD libs and passes the correct path to the linker

//	So far:
//	-	Create an account on FMOD
//	-	Download the binaries
//	-	Move lib stuff to your program files (look this up, os specific. Right now it's stored in /usr/local/lib/FMOD/. I think on windows it's \ Program Files \)
//	-	Move header stuff to include files (currently /usr/local/include/FMOD/)
//	-	Point the compiler's linker to the relevant static-object libraries (see makefile: CXX flags && -lfmod) (See: TODO(3))

class SoundManager
{
	public:
		SoundManager();
		void load(string filepath);
		void play();
		virtual ~SoundManager();
		
	private:
		unique_ptr<FileReader> reader;
		FMOD::System *system;
		FMOD::Sound *sound;
		FMOD_RESULT result;
		string path;
};

#endif
