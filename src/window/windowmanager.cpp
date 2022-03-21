#include "windowmanager.hpp"

Log* WindowManager::log = nullptr;

// ----------------------------------------------------------- WindowManager --

WindowManager::WindowManager() {
	log = Log::get();
	
	ConfigManager manager;
	config = manager.createSection("Video");
	config->addProperty<int>("width", 800);
	config->addProperty<int>("height", 600);
	config->addProperty<std::string>("title", "Visual novel");
}

WindowManager::~WindowManager() {}

// ---------------------------------------------------- public.WindowManager --

bool WindowManager::init() {
	log->info("WINDOW MANAGER initializing...");
	
	if(!glfwInit()) {
		log->error("Failed to initialize GLFW");
		return false;
	}
	
	glfwSetErrorCallback(glfwErrorCallback);
	log->info("initialize GLFW: %s", glfwGetVersionString());
	
	GLFWvidmode const *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	
	// Set the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	
	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	
	if(!getMonitors()) {
		return false;
	}
	
	log->info("WINDOW MANAGER initialized");
	return true;
}

bool WindowManager::update() {
	glfwPollEvents();
	return window.update();
}

void WindowManager::terminate() {
	glfwTerminate();
}

bool WindowManager::createWindow() {
	window.width = config->getValue<int>("width");
	window.height = config->getValue<int>("height");
	window.title = config->getValue<std::string>("title");
	window.create();
	
	if(!window.exist()) {
		log->error("Failed to create GLFW window");
		terminate();
		return false;
	}
	
	// Configuration for window
	window.makeActive();
	window.swapInterval(0);
//	window.keyboardCallback(controlManager->keyboardCallback);
//	window.keyboardCharacterCallback(controlManager->keyboardCharacterCallback);
//	window.keyboardCharacterModifiersCallback
//	(controlManager->keyboardCharacterModifiersCallback);
//	window.mouseButtonCallback(controlManager->mouseButtonCallback);
//	window.mousePositionCallback(controlManager->mousePositionCallback);
//	window.mouseEnterCallback(controlManager->mouseEnterCallback);
//	window.mouseScrollCallback(controlManager->mouseScrollCallback);
//	window.dropCallback(controlManager->dropCallback);
//	window.windowPositionCallback(windowManager.windowPositionCallback);
//	window.windowSizeCallback(windowManager.windowSizeCallback);
//	window.windowCloseCallback(windowManager.windowCloseCallback);
//	window.windowRefreshCallback(windowManager.windowRefreshCallback);
//	window.windowFocusCallback(windowManager.windowFocusCallback);
//	window.windowIconifyCallback(windowManager.windowIconifyCallback);
//	window.windowMaximizeCallback(windowManager.windowMaximizeCallback);
	window.framebufferSizeCallback(framebufferSizeCallback);
//	window.windowContentScaleCallback(windowManager.windowContentScaleCallback);

	log->info("Create GLFW window \"%s\"", window.title.data());
	return true;
}

void WindowManager::makeActive(GLFWwindow *window) {
	int width {0};
	int height {0};
	glfwGetFramebufferSize(window, &width, &height);
//	controlManager->screenSize(width, height);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void WindowManager::cleanup() {}

// --------------------------------------------------- private.WindowManager --

float WindowManager::getFPS() {
	static double previous_seconds = glfwGetTime();
	static int frame_count;
	double current_seconds = glfwGetTime();
	double elapsed_seconds = current_seconds - previous_seconds;
	static double fps;
	
	if(elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		fps = (double)frame_count / elapsed_seconds;
		frame_count = 0;
	}
	
	frame_count++;
	return fps;
}

bool WindowManager::getMonitors() {
	GLFWmonitor **monitors = glfwGetMonitors(&monitorsCount);
	GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
	
	if(monitors == NULL) {
		log->error("No monitors was found by GLFW");
		return false;
	}
	
	Monitor **newMonitors = new Monitor*[monitorsCount];
	
	for(int i = 0; i < monitorsCount; i++) {
		Monitor newMonitor;
		newMonitor.monitor = monitors[i];
		newMonitor.name = glfwGetMonitorName(monitors[i]);
		newMonitor.videoModes = glfwGetVideoModes(monitors[i],
		                        &newMonitor.videoModesCount);
		newMonitor.curentVideoMode = glfwGetVideoMode(monitors[i]);
		newMonitor.isPrimary = false;
		
		if(monitors[i] == primaryMonitor) {
			newMonitor.isPrimary = true;
			this->primaryMonitor = &newMonitor;
		}
		
		newMonitors[i] = &newMonitor;
	}
	
	this->avalableMonitors = newMonitors;
	return true;
}



//////////////////////////////////////////////////////////////////////////////
//                            Callback functions                            //
//////////////////////////////////////////////////////////////////////////////

void WindowManager::glfwErrorCallback(int error, const char* description) {
	log->error("GLFW ERROR: code %i msg: %s", error, description);
}

void WindowManager::framebufferSizeCallback
(GLFWwindow* window, int width, int height) {
	(void)window;
//	Configuration::Section* config = configManager->find("Video");
//	config->setValueInProperty("width", width);
//	config->setValueInProperty("height", height);
//	controlManager->screenSize(width, height);
}
