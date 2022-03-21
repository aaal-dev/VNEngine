#include "app.hpp"

// TODO: Parser for app arguments for debuging purpose
int main(int argc, char **argv) {
	App app;

	if(app.init()) {
		app.run();
		app.stop();
	}

	return 0;
}
