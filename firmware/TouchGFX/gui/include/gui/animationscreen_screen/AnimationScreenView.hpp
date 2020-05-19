#ifndef ANIMATIONSCREENVIEW_HPP
#define ANIMATIONSCREENVIEW_HPP

#include <gui_generated/animationscreen_screen/AnimationScreenViewBase.hpp>
#include <gui/animationscreen_screen/AnimationScreenPresenter.hpp>

class AnimationScreenView : public AnimationScreenViewBase
{
public:
    AnimationScreenView();
    virtual ~AnimationScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void functionStartAnimation();
    virtual void handleTickEvent();
protected:
    int16_t tickCount;
    bool tickEnable;
    uint8_t alpha;
	uint8_t alphaBg;
    uint8_t state;
    uint8_t counter;
};


#endif // ANIMATIONSCREENVIEW_HPP
