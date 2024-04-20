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
#include <time.h>
#include <vector>

#include "../../utils/hdr/fileReader.h"

using std::unique_ptr;
using std::shared_ptr;
using std::string;
using std::vector;

#ifndef LAZARUS_SOUND_MANAGER_H
#define LAZARUS_SOUND_MANAGER_H

class SoundManager
{
	public:
		struct Audio 
		{
			int id;
			string path;

			float listenerLocationX;
			float listenerLocationY;
			float listenerLocationZ;

			float sourceLocationX;
			float sourceLocationY;
			float sourceLocationZ;

			bool is3D;
			bool isPaused;

			int loopCount;

			unsigned int audioIndex;
		};

		SoundManager();

		void initialise();
		shared_ptr<Audio> createAudio(string filepath, bool is3D = false, int loopCount = 0);
		shared_ptr<Audio> loadAudio(shared_ptr<Audio> audioIn);

		shared_ptr<Audio> togglePaused(shared_ptr<Audio> audioIn);
		shared_ptr<Audio> positionSource(shared_ptr<Audio> audioIn, float x, float y, float z);
		shared_ptr<Audio> positionListener(shared_ptr<Audio> audioIn, float x, float y, float z);

		virtual ~SoundManager();

	private:
		struct AudioData 
		{
			FMOD::Sound *sound;
			FMOD::Channel *channel;
			FMOD::ChannelGroup *group;
		};

		vector<AudioData> audioStore;
		AudioData audioData;

		void checkErrors(FMOD_RESULT res);

		unique_ptr<FileReader> reader;

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

		shared_ptr<Audio> audioOut;
};

#endif