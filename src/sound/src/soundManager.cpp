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
	this->isPaused = false;
	
	this->system = NULL;
	this->channel = NULL;
	this->group = NULL;
	this->sound = NULL;

	this->prevSourcePosition = {0.0f, 0.0f, 0.0f};
	this->prevListenerPosition = {0.0f, 0.0f, 0.0f};
	this->sourceVelocity = {0.0f, 0.0f, 0.0f};

	this->currentSourcePosition = {0.0f, 0.0f, 0.0f};
	this->currentListenerPosition = {0.0f, 0.0f, 0.0f};
	this->listenerVelocity = {0.0f, 0.0f, 0.0f};

	this->forward = {0.0f, 0.0f, 0.0f};
	this->up = {0.0f, 0.0f, 0.0f};
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
		this->togglePaused();
	}
	else
	{
		std::cout << RED_TEXT << "ERROR::SOUND_MANAGER" << RESET_TEXT << std::endl;	
		std::cout << LAZARUS_FILE_NOT_FOUND << std::endl;	
	}

	this->checkErrors(this->result);
};

void SoundManager::togglePaused()
{
	if(this->isPaused == true)
	{
		this->result = channel->setPaused(false);
		this->isPaused = false;
	}
	else if(this->isPaused == false)
	{
		this->result = channel->setPaused(true);
		this->isPaused = true;
	}

	this->checkErrors(this->result);
};

void SoundManager::positionSource(float x, float y, float z)
{
	this->currentSourcePosition = {x, y, z};

	this->sourceVelocity = {
		((this->currentSourcePosition.x - this->prevSourcePosition.x) * (1000 / 60)),
		((this->currentSourcePosition.y - this->prevSourcePosition.y) * (1000 / 60)),
		((this->currentSourcePosition.z - this->prevSourcePosition.z) * (1000 / 60))
	};	

	this->result = channel->set3DAttributes(&currentSourcePosition, &sourceVelocity);
	this->checkErrors(this->result);

	this->result = system->update();
	this->prevSourcePosition = this->currentSourcePosition;

	this->checkErrors(this->result);
};

void SoundManager::positionListener(float x, float y, float z)
{
	//	TODO:
	//	Tidyup
	//	Make dynamic
	//	Write Docs
	//	Repeat for source
	this->currentListenerPosition = {x, y, z};

	//	TODO:
	//	Change (1000 / 60) to FpsCounter::durationTillRendered
	this->listenerVelocity = {
		((this->currentListenerPosition.x - this->prevListenerPosition.x) * (1000 / 60)),
		((this->currentListenerPosition.y - this->prevListenerPosition.y) * (1000 / 60)),
		((this->currentListenerPosition.z - this->prevListenerPosition.z) * (1000 / 60))
	};

	this->result = system->set3DListenerAttributes(
		0, 
		&currentListenerPosition, 
		&listenerVelocity,
		&forward,
		&up
	);
	
	this->checkErrors(this->result);

	this->result = system->update();
	this->prevListenerPosition = this->currentListenerPosition;

	this->checkErrors(this->result);
};

void SoundManager::checkErrors(FMOD_RESULT res) 
{
	if(res != FMOD_OK)
	{
		std::cout << RED_TEXT "ERROR::SOUND_MANAGER" << RESET_TEXT << std::endl;
		std::cout << LAZARUS_AUDIO_ERROR << std::endl;
		std::cout << "CODE: " << res << std::endl;
	};
};

SoundManager::~SoundManager()
{
    std::cout << GREEN_TEXT << "Destroying 'SoundManager' class." << RESET_TEXT << std::endl;
	system->release();
	sound->release();
};
