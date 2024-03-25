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
#include "../hdr/soundManager.h"

SoundManager::SoundManager() 
{
    std::cout << GREEN_TEXT << "Constructing class 'SoundManager'." << RESET_TEXT << std::endl;
	this->system = NULL;
	this->sound = NULL;
};

void SoundManager::load(string filepath)
{
	//	TODO: 
	//	Add error checking
	
	this->reader = std::make_unique<FileReader>();
	this->path = reader->relativePathToAbsolute(filepath);
	
	//	TODO:
	//	Move these to an init function
	
	this->result = FMOD::System_Create(&this->system);
	this->result = system->init(512, FMOD_INIT_NORMAL, 0);
	
	//	TODO:
	//	Arg2 should be changed to FMOD_3D
	//	This allows the sound to be positioned in worldspace
	//	Somehow....
	
	this->result = system->createSound(this->path, FMOD_DEFAULT, NULL, &this->sound);
};

void SoundManager::play()
{
	//	TODO:
	//	Add in the optional args, the channel (Arg4) is important for controling the play-state
	//	See: https://www.fmod.com/docs/2.03/api/core-api-channel.html
	
	system->playSound(this->sound);
};

SoundManager::~SoundManager()
{
    std::cout << GREEN_TEXT << "Destroying 'SoundManager' class." << RESET_TEXT << std::endl;
	system->release();
};
