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
	this->channel = NULL;
	this->group = NULL;
	this->sound = NULL;
};

void SoundManager::init()
{
	this->result = FMOD::System_Create(&this->system);
	this->result = system->init(512, FMOD_INIT_NORMAL, 0);

	this->result = system->createChannelGroup("lazarusGroup", &group);
};

void SoundManager::load(string filepath, bool is3D)
{
	//	TODO: 
	//	Add error checking
	
	this->reader = std::make_unique<FileReader>();
	this->path = reader->relativePathToAbsolute(filepath);
	
	if(is3D == true) 
	{
		this->result = system->createSound(this->path.c_str(), FMOD_3D, NULL, &this->sound);
	}
	else if (is3D == false)
	{
		this->result = system->createSound(this->path.c_str(), FMOD_DEFAULT, NULL, &this->sound);
	};
	
	if(this->sound != NULL)
	{
		system->playSound(this->sound, group, false, &channel);
		channel->setPaused(true);
	}
	else
	{
		std::cout << RED_TEXT << "ERROR::SOUND_MANAGER" << RESET_TEXT << std::endl;	
		std::cout << LAZARUS_FILE_NOT_FOUND << std::endl;	
	}
};

void SoundManager::play()
{
	channel->setPaused(false);
};

SoundManager::~SoundManager()
{
    std::cout << GREEN_TEXT << "Destroying 'SoundManager' class." << RESET_TEXT << std::endl;
	system->release();
	sound->release();
};
