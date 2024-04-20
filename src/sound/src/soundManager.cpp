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
	this->audio = nullptr;
	this->reader = nullptr;

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

	this->forward = {0.0f, 0.0f, 1.0f};
	this->up = {0.0f, 1.0f, 0.0f};
};

void SoundManager::initialise()
{
	this->result = FMOD::System_Create(&this->system);
	this->result = system->init(512, FMOD_INIT_3D_RIGHTHANDED, 0);

	this->result = system->createChannelGroup("lazarusGroup", &group);

	this->checkErrors(this->result);
};

shared_ptr<SoundManager::Audio> SoundManager::createAudio(string filepath, bool is3D, int loopCount)
{
	this->audio = std::make_shared<SoundManager::Audio>();
	this->reader = std::make_unique<FileReader>();

	srand(time((0)));
	audio->id = 1 + (rand() % 2147483647);

	audio->locationX = 0.0f;
	audio->locationY = 0.0f;
	audio->locationZ = 0.0f;

	audio->path = reader->relativePathToAbsolute(filepath);
	audio->is3D = is3D;
	audio->loopCount = loopCount;

	return audio;
};

shared_ptr<SoundManager::Audio> SoundManager::loadAudio(shared_ptr<SoundManager::Audio> audioData)
{	
	if(this->audio != nullptr)
	{
		audio.reset();
	};

	this->audio = std::move(audioData);

	(audio->is3D == true) 
	? this->result = system->createSound(audio->path.c_str(), FMOD_3D, NULL, &this->sound) 
	: this->result = system->createSound(audio->path.c_str(), FMOD_DEFAULT, NULL, &this->sound);
	
	this->checkErrors(this->result);
	
	if(this->sound != NULL)
	{
		this->result = system->playSound(this->sound, group, false, &channel);
		
		if (audio->loopCount != 0)
		{
			channel->setMode(FMOD_LOOP_NORMAL);
			channel->setLoopCount(audio->loopCount);
		};
		
		this->togglePaused(this->audio);
	}
	else
	{
		std::cout << RED_TEXT << "ERROR::SOUND_MANAGER" << RESET_TEXT << std::endl;	
		std::cout << LAZARUS_FILE_NOT_FOUND << std::endl;	
	}

	this->checkErrors(this->result);
	
	return audio;
};

shared_ptr<SoundManager::Audio> SoundManager::togglePaused(shared_ptr<SoundManager::Audio> audioData)
{
	if(this->audio != nullptr)
	{
		audio.reset();
	};

	this->audio = std::move(audioData);

	if(audio->isPaused == true)
	{
		this->result = channel->setPaused(false);
		audio->isPaused = false;
	}
	else if(audio->isPaused == false)
	{
		this->result = channel->setPaused(true);
		audio->isPaused = true;
	}

	this->checkErrors(this->result);

	return audio;
};

shared_ptr<SoundManager::Audio> SoundManager::positionSource(shared_ptr<SoundManager::Audio> audioData, float x, float y, float z)
{
	if(this->audio != nullptr)
	{
		audio.reset();
	};

	this->audio = std::move(audioData);

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

	audio->locationX = this->prevSourcePosition.x;
	audio->locationY = this->prevSourcePosition.y;
	audio->locationZ = this->prevSourcePosition.z;

	return audio;
};

void SoundManager::positionListener(float x, float y, float z)
{
	//	TODO:
	//	Make dynamic
	//	Tidyup
	//	Write Docs

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
	
	sound->release();
	group->release();
	system->release();
};
