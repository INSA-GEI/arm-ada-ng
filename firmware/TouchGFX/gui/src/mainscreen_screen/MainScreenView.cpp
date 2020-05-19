#include <gui/mainscreen_screen/MainScreenView.hpp>

MainScreenView::MainScreenView()
{

}

void MainScreenView::setupScreen()
{
	MainScreenViewBase::setupScreen();

	iconLauncherA.setXY(289, 30);
	iconLauncherB.setXY(78, 30);
	iconLauncherA.SetText("icon A");
	iconLauncherB.SetText("Icon B");
	iconLauncherA.SetLaunchType(0);
	iconLauncherB.SetLaunchType(1);

	add(iconLauncherA);
	add(iconLauncherB);

	iconLauncherA.initialize();
	iconLauncherB.initialize();
}

void MainScreenView::tearDownScreen()
{
	MainScreenViewBase::tearDownScreen();
}

void MainScreenView::updateScreen()
{
	Unicode::snprintf(textDateTimeBuffer, TEXTDATETIME_SIZE, "%d:%d", 13,26);
	// Invalidate text area, which will result in it being redrawn in next tick.
	textDateTime.invalidate();

}

void  MainScreenView::buttonModalClicked() {
	modalWindow.setVisible(false);
}

void  MainScreenView::buttonMenuClicked()  {
	modalWindow.setVisible(true);
}

void  MainScreenView::buttonSDCardClicked() {
	modalWindow.setVisible(true);
}


