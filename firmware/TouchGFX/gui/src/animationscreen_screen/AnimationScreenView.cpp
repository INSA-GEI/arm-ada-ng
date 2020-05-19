#include <gui/animationscreen_screen/AnimationScreenView.hpp>

AnimationScreenView::AnimationScreenView()
{
	tickCount=0;
	tickEnable=false;
	alpha =0;
	alphaBg=255;
	state=0;
	counter=0;
}

void AnimationScreenView::setupScreen()
{
	AnimationScreenViewBase::setupScreen();
}

void AnimationScreenView::tearDownScreen()
{
	AnimationScreenViewBase::tearDownScreen();
}

void AnimationScreenView::functionStartAnimation()
{
	//touchgfx_printf("Animation start\n");
	tickEnable=true;
}

void AnimationScreenView::handleTickEvent()
{
	if (tickEnable==true)
	{
		tickCount++;

		if(tickCount==2)
		{
			//touchgfx_printf("State = %d\n", state);
			tickCount=0;

			switch (state)
			{
			case 0:
				alpha = alpha+(255/60);
				ImageLogo.setAlpha(alpha);

				if (alpha> 250)
				{
					alpha=255;
					ImageLogo.setAlpha(alpha);

					state=1;
				}

				break;
			case 1:
				counter++;

				if (counter==25) state=2;
				break;

			case 2:
				alpha = alpha-(255/30);
				ImageLogo.setAlpha(alpha);

				if (alpha< 10)
				{
					alpha=0;
					ImageLogo.setAlpha(alpha);

					state=3;
				}
				break;

			case 3:
				alphaBg = alphaBg-(255/20);
				imageBackgroundAnimation.setAlpha(alphaBg);

				if (alphaBg<10) {
					alphaBg =0;
					imageBackgroundAnimation.setAlpha(alphaBg);

					state=4;
				}
				break;
			default:
				break;
			}

			ImageLogo.invalidate();
			imageBackgroundAnimation.invalidate();
		}
	}

	AnimationScreenViewBase::handleTickEvent();
}
