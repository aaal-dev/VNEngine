#include "openal.hpp"

Log* OpenAl::log = nullptr;

// ------------------------------------------------------------------ OpenAl --

OpenAl::OpenAl() {
	log = Log::get();
}

OpenAl::~OpenAl() {}

// ----------------------------------------------------------- public.OpenAl --

bool OpenAl::init() {
	log->begin("OpenAL initializing...");
	
	/* Open and initialize a device */
	ALCdevice *device = alcOpenDevice(NULL);
	
	if(!device) {
		log->error("Could not open a device!");
		return false;
	}
	
	ALCcontext *ctx = alcCreateContext(device, NULL);
	
	if(ctx == NULL || alcMakeContextCurrent(ctx) == ALC_FALSE) {
		if(ctx != NULL) alcDestroyContext(ctx);
		
		alcCloseDevice(device);
		log->error("Could not set a context!");
		return false;
	}
	
	ALCchar const *name {nullptr};
	
	if(alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
		name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
		
	if(!name || alcGetError(device) != AL_NO_ERROR)
		name = alcGetString(device, ALC_DEVICE_SPECIFIER);
		
	log->info("Opened \"%s\"", name);
	log->done("OpenAl initialized");
	return true;
}

void OpenAl::stop() {
	log->begin("OpenAL stoping...");
	ALCcontext *ctx = alcGetCurrentContext();
	
	if(ctx == nullptr) return;
	
	ALCdevice *device = alcGetContextsDevice(ctx);
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(ctx);
	alcCloseDevice(device);
	log->done("OpenAL stoped");
}
