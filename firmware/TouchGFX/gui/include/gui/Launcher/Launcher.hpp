/*
 * Launcher.hpp
 *
 *  Created on: 18 mai 2020
 *      Author: dimercur
 */

#ifndef GUI_INCLUDE_GUI_LAUNCHER_HPP_
#define GUI_INCLUDE_GUI_LAUNCHER_HPP_

enum class LauncherType {
	IncludedTests,
	IncludedGames,
	ExecfromSRAM,
	ExecfromSDCard,
	Undefined
};

enum class ExecStatus {
	Successful,
	InvalidProgram,
	CorruptedProgram,
	CardIOError,
	OtherError
};

class Launcher {
public:

	Launcher();
	Launcher(LauncherType type);
	virtual ~Launcher();
	virtual void setLaunchType(LauncherType type);
	virtual ExecStatus exec(int id, int* returnCode);
protected:
	LauncherType type;
};

#endif /* GUI_INCLUDE_GUI_LAUNCHER_HPP_ */
