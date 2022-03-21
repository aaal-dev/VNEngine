#pragma once

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"

#include "../config/configmanager.hpp"
#include "../log/log.hpp"

class OpenAl {
public:
// -------------------------------------------------------- public.variables --
// -------------------------------------------------------- public.functions --
	/**
	 * @brief
	 * @return
	 */
	bool init();
	
	/**
	 * @brief
	 */
	void stop();
	
private:
// ------------------------------------------------------- private.variables --

	static Log  *log;
	
// ------------------------------------------------------------- private.App --

public:
	OpenAl();
	virtual ~OpenAl();
};
