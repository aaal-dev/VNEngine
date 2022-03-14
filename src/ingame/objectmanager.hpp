#pragma once

#include <string>
#include <vector>

#include "../log/log.hpp"
#include "../parser/node.hpp"

#include "audio.hpp"
#include "character.hpp"
#include "music.hpp"
#include "picture.hpp"
#include "scene.hpp"
#include "sound.hpp"
#include "video.hpp"



class ObjectManager {
	static Log* log;
	struct ObjectType {
		enum Types {
			CHARACTER,
			MUSIC,
			PICTURE,
			SCENE,
			SOUND,
			VIDEO,
			_OBJECT_TYPE_NUMBER
		};
		std::string types[_OBJECT_TYPE_NUMBER] = {
			"character",
			"music",
			"picture",
			"scene",
			"sound",
			"video"
		};
		int find(std::string &type);
	} objectType;
	
public:
	    std::vector<AudioObject>   audioObjects; 
	std::vector<CharacterObject>   characterObjects; 
	    std::vector<MusicObject>   musicObjects;
	  std::vector<PictureObject>   pictureObjects; 
	    std::vector<SceneObject>   sceneObjects; 
	    std::vector<SoundObject>   soundObjects;
	    std::vector<VideoObject>   videoObjects; 
	
	
	bool init();
	void collectObjects(std::string gamepath, std::string gamefile);
	void obtainObject(NodeTree* &tree, std::string &dir);
	void seekObjects(NodeTree* &tree, std::string &dir);
	GameObject find(std::string const &id, ObjectType type);
	                             ObjectManager();
	virtual                     ~ObjectManager();
};

