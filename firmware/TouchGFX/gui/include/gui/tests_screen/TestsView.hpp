#ifndef TESTSVIEW_HPP
#define TESTSVIEW_HPP

#include <gui_generated/tests_screen/TestsViewBase.hpp>
#include <gui/tests_screen/TestsPresenter.hpp>

class TestsView : public TestsViewBase
{
public:
    TestsView();
    virtual ~TestsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // TESTSVIEW_HPP
