#include "WindowManagement.h"

int main(void) {
	WindowManagement myWindow;

	myWindow.init(800, 600);
	myWindow.setCallbackFunction();
	myWindow.mainLoop();

	return 0;
}