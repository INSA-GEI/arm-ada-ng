#ifndef ANIMATIONSCREENPRESENTER_HPP
#define ANIMATIONSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class AnimationScreenView;

class AnimationScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    AnimationScreenPresenter(AnimationScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~AnimationScreenPresenter() {};

private:
    AnimationScreenPresenter();

    AnimationScreenView& view;
};

#endif // ANIMATIONSCREENPRESENTER_HPP
