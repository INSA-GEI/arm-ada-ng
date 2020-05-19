#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

class MainScreenView : public MainScreenViewBase
{
public:
	MainScreenView();
	virtual ~MainScreenView() {}
	virtual void setupScreen();
	virtual void tearDownScreen();
	virtual void updateScreen();
	virtual void buttonModalClicked();
	virtual void buttonMenuClicked();
	virtual void buttonSDCardClicked();

protected:
	IconLauncher iconLauncherA;
	IconLauncher iconLauncherB;
};

#endif // MAINSCREENVIEW_HPP
