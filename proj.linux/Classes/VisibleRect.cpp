#include "cocos2d.h"


class VisibleRect
{
public:

    static CCRect getVisibleRect()
    {
        lazyInit();
        return CCRectMake(s_visibleRect.origin.x, s_visibleRect.origin.y, s_visibleRect.size.width, s_visibleRect.size.height);
    }

    static CCPoint left()
    {
        lazyInit();
        return ccp(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height/2);
    }

    static CCPoint right()
    {
        lazyInit();
        return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height/2);
    }

    static CCPoint top()
    {
        lazyInit();
        return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height);
    }

    static CCPoint bottom()
    {
        lazyInit();
        return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y);
    }

    static CCPoint center()
    {
        lazyInit();
        return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
    }

    static CCPoint leftTop()
    {
        lazyInit();
        return ccp(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height);
    }

    static CCPoint rightTop()
    {
        lazyInit();
        return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height);
    }

    static CCPoint leftBottom()
    {
        lazyInit();
        return s_visibleRect.origin;
    }

    static CCPoint rightBottom()
    {
        lazyInit();
        return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y);
    }

private:
    static CCRect s_visibleRect;
    
    static void lazyInit()
    {
        if (s_visibleRect.size.width == 0.0f && s_visibleRect.size.height == 0.0f)
        {
            CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
            s_visibleRect.origin = pEGLView->getVisibleOrigin();
            s_visibleRect.size = pEGLView->getVisibleSize();
        }
    }
};
CCRect VisibleRect::s_visibleRect;