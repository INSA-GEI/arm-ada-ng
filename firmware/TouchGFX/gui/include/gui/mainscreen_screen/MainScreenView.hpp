#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

#include <gui/containers/IconLauncher.hpp>
//#include <vector>

#define MAX_LAUNCHERS 8

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
	virtual void buttonSDCardPressed();

	virtual void addLaunchers(const char* name, LauncherType type);
	virtual void addLaunchers(const char* name, LauncherType type, Bitmap &bitmap);
	virtual void flushLaunchers();
protected:
	int iconLauncherNbr=0;

	IconLauncher* iconLauncherArray[MAX_LAUNCHERS]={
			&iconLauncher1, &iconLauncher2, &iconLauncher3, &iconLauncher4,
			&iconLauncher5, &iconLauncher6, &iconLauncher7, &iconLauncher8
	};



	//virtual void displayLaunchers();
};

#endif // MAINSCREENVIEW_HPP
