#include "objectmanager.hpp"

Log* ObjectManager::log = nullptr;

// ----------------------------------------------------------- ObjectManager -- 

ObjectManager::ObjectManager () {
	log = Log::get();
}

ObjectManager::~ObjectManager () {}

// ---------------------------------------------------- public:ObjectManager -- 

bool ObjectManager::init () {
	log->info("initialize object manager start...");
	
	
	log->info("initialize object manager done!");
	return true;
}

void ObjectManager::collectObjects (std::string gamepath, std::string gamefile) {
	
	
}

void ObjectManager::obtainObject (NodeTree* &tree, std::string &dir) {
	Node* node = tree->search("object");
	switch (objectType.find(node->value)) {
		case (ObjectType::CHARACTER): {
			CharacterObject newCharacter;
			newCharacter.id = tree->search("id")->value;
			newCharacter.name = tree->search("name")->value;
			newCharacter.shortname = tree->search("shortname")->value;
			newCharacter.type = node->value;
			newCharacter.path = dir + tree->search("filename")->value;
			characterObjects.push_back(newCharacter);
			break;
		}
		case (ObjectType::MUSIC): {
			MusicObject newMusic;
			newMusic.id = tree->search("id")->value;
			newMusic.name = tree->search("name")->value;
			newMusic.shortname = tree->search("shortname")->value;
			newMusic.type = node->value;
			newMusic.path = dir + tree->search("filename")->value;
			musicObjects.push_back(newMusic);
			break;
		}
		case (ObjectType::PICTURE): {
			PictureObject newPicture;
			newPicture.id = tree->search("id")->value;
			newPicture.name = tree->search("name")->value;
			newPicture.shortname = tree->search("shortname")->value;
			newPicture.type = node->value;
			newPicture.path = dir + tree->search("filename")->value;
			pictureObjects.push_back(newPicture);
			break;
		}
		case (ObjectType::SCENE): {
			SceneObject newScene;
			newScene.id = tree->search("id")->value;
			newScene.name = tree->search("name")->value;
			newScene.shortname = tree->search("shortname")->value;
			newScene.type = node->value;
			newScene.path = dir + tree->search("filename")->value;
			sceneObjects.push_back(newScene);
			break;
		}
		case (ObjectType::SOUND): {
			SoundObject newSound;
			newSound.id = tree->search("id")->value;
			newSound.name = tree->search("name")->value;
			newSound.shortname = tree->search("shortname")->value;
			newSound.type = node->value;
			newSound.path = dir + tree->search("filename")->value;
			soundObjects.push_back(newSound);
			break;
		}
		case (ObjectType::VIDEO): {
			VideoObject newVideo;
			newVideo.id = tree->search("id")->value;
			newVideo.name = tree->search("name")->value;
			newVideo.shortname = tree->search("shortname")->value;
			newVideo.type = node->value;
			newVideo.path = dir + tree->search("filename")->value;
			videoObjects.push_back(newVideo);
			break;
		}
		default: break;
	}
}

void ObjectManager::seekObjects (NodeTree* &tree, std::string &dir) {
	if (tree->count > 0) {
		if (tree->key == "file") {
			dir = tree->search("path")->value;
		}
		if (tree->search("object") != nullptr) {
			obtainObject(tree, dir);
		} else {
			for (auto node : tree->nodes) {
				seekObjects(node, dir);
			}
		}
	}
}

//// ==== ObjectManager::ObjectType ======================================= ////

int ObjectManager::ObjectType::find (std::string &type) {
	int i = -1;
	while (i < _OBJECT_TYPE_NUMBER) {
		i++;
		if (types[i] == type) break;
	}
	return i;
}
