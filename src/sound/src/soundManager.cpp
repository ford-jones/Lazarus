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

	this->checkErrors(this->result);
};

void SoundManager::load(string filepath, bool is3D)
{	
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
	this->checkErrors(this->result);
	
	if(this->sound != NULL)
	{
		this->result = system->playSound(this->sound, group, false, &channel);
		this->result = channel->setPaused(true);
	}
	else
	{
		std::cout << RED_TEXT << "ERROR::SOUND_MANAGER" << RESET_TEXT << std::endl;	
		std::cout << LAZARUS_FILE_NOT_FOUND << std::endl;	
	}

	this->checkErrors(this->result);
};

void SoundManager::play()
{
	this->result = channel->setPaused(false);
	this->checkErrors(this->result);
};

void SoundManager::checkErrors(FMOD_RESULT res) 
{
	if(res != FMOD_OK)
	{
		std::cout << RED_TEXT "ERROR::SOUND_MANAGER" << RESET_TEXT << std::endl;
		std::cout << LAZARUS_AUDIO_ERROR << std::endl;
		std::cout << res << std::endl;
	};
};

SoundManager::~SoundManager()
{
    std::cout << GREEN_TEXT << "Destroying 'SoundManager' class." << RESET_TEXT << std::endl;
	system->release();
	sound->release();
};
