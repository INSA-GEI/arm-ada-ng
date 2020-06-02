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
	type=LauncherType::Undefined;
}

Launcher::Launcher(LauncherType type) {
	// TODO Auto-generated constructor stub
	this->type=type;
}

Launcher::~Launcher() {
	// TODO Auto-generated destructor stub
}

ExecStatus Launcher::exec(int id, int* returnCode)
{
	int i;
	ExecStatus status = ExecStatus::Successful;
	int code = 0;

	switch (type)
	{
	case LauncherType::IncludedTests:
		static_cast<FrontendApplication*>(Application::getInstance())->gotoTestsScreenCoverTransitionEast();
		break;
	case LauncherType::IncludedGames:
		int *p;
		//p= (int*)0xC0000000;
		p=(int*)0xC0340C00;
		for (i=0; i<(480*272)/4; i++)
		{
			*(p+i)=i;
		}

		break;
	case LauncherType::ExecfromSRAM:
		break;
	case LauncherType::ExecfromSDCard:
		break;
	default:
		break;
	}

	*returnCode=code;
	return status;
}

void Launcher::setLaunchType(LauncherType type)
{
	this->type = type;
}

