#pragma once

#include "../config/configmanager.hpp"
#include "../log/log.hpp"
#include "openal.hpp"

class AudioManager {
public:
// -------------------------------------------------------- public.variables --
// -------------------------------------------------------- public.functions --
	/**
	 * @brief
	 * @return
	 */
	bool     init();

private:
// ------------------------------------------------------- private.variables --

	static Log  *log;

// ------------------------------------------------------- private.functions --

public:
	AudioManager();
	virtual ~AudioManager();

};
