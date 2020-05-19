/*
 * Launcher.cpp
 *
 *  Created on: 18 mai 2020
 *      Author: dimercur
 */

#include <gui/Launcher/Launcher.hpp>
#include <gui/common/FrontendApplication.hpp>

Launcher::Launcher() {
	// TODO Auto-generated destructor stub
	type=-1;
}

Launcher::Launcher(int type) {
	// TODO Auto-generated constructor stub
	this->type=type;
}

Launcher::~Launcher() {
	// TODO Auto-generated destructor stub
}

void Launcher::exec(int id)
{
	switch (type)
	{
	case 0:
		static_cast<FrontendApplication*>(Application::getInstance())->gotoTestsScreenCoverTransitionEast();
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}

void Launcher::setLaunchType(int type)
{
	this->type = type;
}

