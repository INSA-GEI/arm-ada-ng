#ifndef ICONLAUNCHER_HPP
#define ICONLAUNCHER_HPP

#include <gui_generated/containers/IconLauncherBase.hpp>
#include <gui/Launcher/Launcher.hpp>

class IconLauncher : public IconLauncherBase
{
public:
    IconLauncher();
    IconLauncher(LauncherType launchType);
    virtual ~IconLauncher() {}

    virtual void initialize();
    virtual void buttonClicked();
    virtual void SetText(const char* str);
    virtual void SetIcon (const Bitmap &iconPressed, const Bitmap &iconReleased);
    virtual void SetId(int id);
    virtual void SetLaunchType(LauncherType launchType);

protected:
    int id;
    Launcher launcher;
};

#endif // ICONLAUNCHER_HPP
