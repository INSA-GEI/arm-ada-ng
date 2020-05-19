/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef ANIMATIONSCREENVIEWBASE_HPP
#define ANIMATIONSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/animationscreen_screen/AnimationScreenPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>

class AnimationScreenViewBase : public touchgfx::View<AnimationScreenPresenter>
{
public:
    AnimationScreenViewBase();
    virtual ~AnimationScreenViewBase() {}
    virtual void setupScreen();
    virtual void handleTickEvent();
    virtual void afterTransition();

    /*
     * Virtual Action Handlers
     */
    virtual void functionStartAnimation()
    {
        // Override and implement this function in AnimationScreen
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Image imageBackground;
    touchgfx::Image imageBackgroundAnimation;
    touchgfx::Image ImageLogo;

private:

    /*
     * Delay Variable Declarations
     */
    static const uint16_t INTERACTIONWAIT_DURATION = 300;
    uint16_t interactionWaitCounter;

};

#endif // ANIMATIONSCREENVIEWBASE_HPP
