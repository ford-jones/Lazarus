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
	this->audioOut = nullptr;
	this->reader = nullptr;
	
	this->system = NULL;
	this->audioData.channel = NULL;
	this->audioData.group = NULL;
	this->audioData.sound = NULL;

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

	this->result = system->createChannelGroup("lazarusGroup", &audioData.group);

	this->checkErrors(this->result);
};

shared_ptr<SoundManager::Audio> SoundManager::createAudio(string filepath, bool is3D, int loopCount)
{
	this->audioOut = std::make_shared<SoundManager::Audio>();
	this->reader = std::make_unique<FileReader>();

	srand(time((0)));
	audioOut->id = 1 + (rand() % 2147483647);

	audioOut->listenerLocationX = 0.0f;
	audioOut->listenerLocationY = 0.0f;
	audioOut->listenerLocationZ = 0.0f;

	audioOut->sourceLocationX = 0.0f;
	audioOut->sourceLocationY = 0.0f;
	audioOut->sourceLocationZ = 0.0f;

	audioOut->path = reader->relativePathToAbsolute(filepath);
	audioOut->is3D = is3D;
	audioOut->loopCount = loopCount;
	audioOut->isPaused = true;
	audioOut->audioIndex = 0;

	return audioOut;
};

shared_ptr<SoundManager::Audio> SoundManager::loadAudio(shared_ptr<SoundManager::Audio> audioIn)
{	
	if(this->audioOut != nullptr)
	{
		audioOut.reset();
	};

	this->audioOut = std::move(audioIn);

	(audioOut->is3D == true) 
	? this->result = system->createSound(audioOut->path.c_str(), FMOD_3D, NULL, &this->audioData.sound) 
	: this->result = system->createSound(audioOut->path.c_str(), FMOD_DEFAULT, NULL, &this->audioData.sound);
	
	this->checkErrors(this->result);
	
	if(this->audioData.sound != NULL)
	{
		this->result = system->playSound(this->audioData.sound, audioData.group, false, &audioData.channel);
		
		if (audioOut->loopCount != 0)
		{
			audioData.channel->setMode(FMOD_LOOP_NORMAL);
			audioData.channel->setLoopCount(audioOut->loopCount);
		};
		
		audioData.channel->setPaused(true);
	}
	else
	{
		std::cout << RED_TEXT << "ERROR::SOUND_MANAGER" << RESET_TEXT << std::endl;	
		std::cout << LAZARUS_FILE_NOT_FOUND << std::endl;	
	}

	this->checkErrors(this->result);
	
	this->audioStore.push_back(audioData);
	audioOut->audioIndex = audioStore.size();

	audioData.channel = NULL;
	audioData.group = NULL;
	audioData.sound = NULL;

	return audioOut;
};

shared_ptr<SoundManager::Audio> SoundManager::togglePaused(shared_ptr<SoundManager::Audio> audioIn)
{
	if(this->audioOut != nullptr)
	{
		audioOut.reset();
	};

	this->audioOut = std::move(audioIn);

	if(audioOut->isPaused == true)
	{
		this->result = audioStore[audioOut->audioIndex - 1].channel->setPaused(false);
		audioOut->isPaused = false;
	}
	else if(audioOut->isPaused == false)
	{
		this->result = audioStore[audioOut->audioIndex - 1].channel->setPaused(true);
		audioOut->isPaused = true;
	}

	this->checkErrors(this->result);

	return audioOut;
};

shared_ptr<SoundManager::Audio> SoundManager::positionSource(shared_ptr<SoundManager::Audio> audioIn, float x, float y, float z)
{
	if(this->audioOut != nullptr)
	{
		audioOut.reset();
	};

	this->audioOut = std::move(audioIn);

	this->currentSourcePosition = {x, y, z};

	this->sourceVelocity = {
		((this->currentSourcePosition.x - this->prevSourcePosition.x) * (1000 / 60)),
		((this->currentSourcePosition.y - this->prevSourcePosition.y) * (1000 / 60)),
		((this->currentSourcePosition.z - this->prevSourcePosition.z) * (1000 / 60))
	};

	this->result = audioStore[audioOut->audioIndex - 1].channel->set3DAttributes(&currentSourcePosition, &sourceVelocity);
	this->checkErrors(this->result);

	this->result = system->update();
	this->prevSourcePosition = this->currentSourcePosition;

	this->checkErrors(this->result);

	audioOut->sourceLocationX = this->prevSourcePosition.x;
	audioOut->sourceLocationY = this->prevSourcePosition.y;
	audioOut->sourceLocationZ = this->prevSourcePosition.z;

	return audioOut;
};

shared_ptr<SoundManager::Audio> SoundManager::positionListener(shared_ptr<SoundManager::Audio> audioIn, float x, float y, float z)
{
	//	TODO:
	//	Tidyup
	//	Write Docs

	if(this->audioOut != nullptr)
	{
		audioOut.reset();
	};

	this->audioOut = std::move(audioIn);

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

	audioOut->listenerLocationX = this->prevListenerPosition.x;
	audioOut->listenerLocationY = this->prevListenerPosition.y;
	audioOut->listenerLocationZ = this->prevListenerPosition.z;

	return audioOut;
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
	
	for(unsigned int i; i < audioStore.size(); i++)
	{
		SoundManager::AudioData data = audioStore[i];

		data.sound->release();
		data.group->release();
	}

	system->release();
};