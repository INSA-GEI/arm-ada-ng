#ifndef TESTSPRESENTER_HPP
#define TESTSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class TestsView;

class TestsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    TestsPresenter(TestsView& v);

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

    virtual ~TestsPresenter() {};

private:
    TestsPresenter();

    TestsView& view;
};

#endif // TESTSPRESENTER_HPP
