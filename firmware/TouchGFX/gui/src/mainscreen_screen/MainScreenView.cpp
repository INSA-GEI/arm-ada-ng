#include <gui/mainscreen_screen/MainScreenView.hpp>

MainScreenView::MainScreenView()
{

}

void MainScreenView::setupScreen()
{
	MainScreenViewBase::setupScreen();

	addLaunchers("Tests", LauncherType::IncludedTests);
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

void  MainScreenView::buttonSDCardPressed() {
	addLaunchers("essai", LauncherType::ExecfromSRAM);
}

void  MainScreenView::addLaunchers(const char* name, LauncherType type)
{
	iconLauncherArray[iconLauncherNbr]->SetText(name);
	iconLauncherArray[iconLauncherNbr]->SetLaunchType(type);

	iconLauncherArray[iconLauncherNbr]->setVisible(true);
	iconLauncherArray[iconLauncherNbr]->invalidate();

	iconLauncherNbr++;

	if (iconLauncherNbr>=MAX_LAUNCHERS) iconLauncherNbr=MAX_LAUNCHERS-1;
}

void MainScreenView::addLaunchers(const char* name, LauncherType type, Bitmap &bitmap)
{
	iconLauncherArray[iconLauncherNbr]->SetText(name);
	iconLauncherArray[iconLauncherNbr]->SetLaunchType(type);
	iconLauncherArray[iconLauncherNbr]->SetIcon(bitmap, bitmap);

	iconLauncherArray[iconLauncherNbr]->setVisible(true);
	iconLauncherArray[iconLauncherNbr]->invalidate();

	iconLauncherNbr++;

	if (iconLauncherNbr>=MAX_LAUNCHERS) iconLauncherNbr=MAX_LAUNCHERS-1;
}

void  MainScreenView::flushLaunchers()
{
	for (int i=0; i<iconLauncherNbr; i++)
	{
		iconLauncherArray[i]->setVisible(false);
		//iconLauncherArray[i].setVisible(false);
		//iconLauncherArray[i].invalidate();
	}

	iconLauncherNbr =0;
}
//
//void MainScreenView::displayLaunchers()
//{
//	int i=0;
//	int intervalHaut=0, intervalBas=0;
//
//	if (iconLauncherNbr<4)
//	{
//		// Une ligne
//		intervalHaut=(360 - (120*iconLauncherNbr))/(iconLauncherNbr+1);
//
//		for (i=0;i<iconLauncherNbr;i++) {
//			iconLauncherArray[i].setXY(360-(i*intervalHaut), 66);
//			iconLauncherArray[i].invalidate();
//		}
//	}
//	else
//	{
//		// 2 lignes
//	}
//}
