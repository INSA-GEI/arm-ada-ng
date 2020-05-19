/*
 * Launcher.hpp
 *
 *  Created on: 18 mai 2020
 *      Author: dimercur
 */

#ifndef GUI_INCLUDE_GUI_LAUNCHER_HPP_
#define GUI_INCLUDE_GUI_LAUNCHER_HPP_

class Launcher {
public:
	Launcher();
	Launcher(int type);
	virtual ~Launcher();
	virtual void setLaunchType(int type);
	virtual void exec(int id);
protected:
	int type;
};

#endif /* GUI_INCLUDE_GUI_LAUNCHER_HPP_ */
