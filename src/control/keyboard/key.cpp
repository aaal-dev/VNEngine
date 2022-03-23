#include "key.hpp"

cob::Key::Key()
{
}

cob::Key::~Key()
{
}

void cob::Key::press() {
	pressed = true;
	action->exec();
}

void cob::Key::release() {
	pressed = false;
}

void cob::Key::setAction(actions::IAction *action) {
	this->action = action;
}