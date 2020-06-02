#include <gui/containers/IconLauncher.hpp>
#include "BitmapDatabase.hpp"

IconLauncher::IconLauncher()
{
	launcher.setLaunchType(LauncherType::Undefined);
}

IconLauncher::IconLauncher(LauncherType launchType)
{
	launcher.setLaunchType(launchType);
}

void IconLauncher::initialize()
{
	IconLauncherBase::initialize();
}

void IconLauncher::buttonClicked()
{
	int code;

	launcher.exec(this->id, &code);
}

void IconLauncher::SetText(const char* str)
{
	Unicode::UnicodeChar unicodeBuffer[TEXT_SIZE];
	Unicode::fromUTF8((const uint8_t*)str, unicodeBuffer, TEXT_SIZE);
	Unicode::snprintf(textBuffer, TEXT_SIZE, "%s", unicodeBuffer);
	text.invalidate();
}

void IconLauncher::SetIcon (const Bitmap &iconPressed, const Bitmap &iconReleased)
{
	button.setBitmaps(touchgfx::Bitmap(BITMAP_LAUNCHER_BUTTON_RELEASED_ID), touchgfx::Bitmap(BITMAP_LAUNCHER_BUTTON_CLICKED_ID), iconReleased, iconPressed);
	button.invalidate();
}

void IconLauncher::SetId(int id)
{
	this->id=id;
}

void IconLauncher::SetLaunchType(LauncherType launchType)
{
	launcher.setLaunchType(launchType);
}
