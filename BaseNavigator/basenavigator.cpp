#include "basenavigator.h"

BaseNavigator::BaseNavigator(QStackedWidget *container, BaseScreensFactory *_screensFactory)
{
    this->currentContainer=container;
    this->screensFactory=_screensFactory;
    BaseFragment *startFragment=getStartScreen();
    this->fragmentStack.append(startFragment);
    currentContainer->addWidget(fragmentStack.last());
    currentContainer->setCurrentIndex(0);
}

BaseNavigator::~BaseNavigator()
{
    delete currentContainer;
    delete screensFactory;
    while(!fragmentStack.empty())
    {
        delete fragmentStack.last();
        fragmentStack.removeLast();
    }
}

BaseFragment *BaseNavigator::getStartScreen()
{
    return createAndConnect(this->screensFactory->createStart());
}

BaseFragment *BaseNavigator::createAndConnect(QString tag)
{
    BaseFragment *fragment=this->screensFactory->create(tag);
    connectFragment(fragment);
    return fragment;
}

void BaseNavigator::connectFragment(BaseFragment *fragment)
{
    connect(fragment, &BaseFragment::back,this, &BaseNavigator::back);
    //connect(fragment, &BaseFragment::replace, this, &BaseNavigator::replace);
    connect(fragment, &BaseFragment::navigateTo, this, &BaseNavigator::navigateTo);
    //connect(fragment, &BaseFragment::newRootScreen, this, &BaseNavigator::newRootScreen);
    //connect(fragment, &BaseFragment::navigateWhithData, this, &BaseNavigator::navigateWhithData);
}

void BaseNavigator::disconnectFragment(BaseFragment *fragment)
{
    disconnect(fragment, &BaseFragment::back,this, &BaseNavigator::back);
    //disconnect(fragment, &BaseFragment::replace, this, &BaseNavigator::replace);
    disconnect(fragment, &BaseFragment::navigateTo, this, &BaseNavigator::navigateTo);
    //disconnect(fragment, &BaseFragment::newRootScreen, this, &BaseNavigator::newRootScreen);
    //disconnect(fragment, &BaseFragment::navigateWhithData, this, &BaseNavigator::navigateWhithData);
}

void BaseNavigator::navigateTo(QString tag)
{
    BaseFragment *newFragment = this->screensFactory->create(tag);
    fragmentStack.last()->onPause();
    disconnectFragment(fragmentStack.last());
    connectFragment(newFragment);
    fragmentStack.append(newFragment);
    currentContainer->addWidget(newFragment);
    currentContainer->setCurrentWidget(newFragment);
}

void BaseNavigator::back()
{
    if(fragmentStack.size()==0)
        return;
    currentContainer->removeWidget(fragmentStack.last());
    delete fragmentStack.last();
    disconnectFragment(fragmentStack.last());
    fragmentStack.removeLast();
    connectFragment(fragmentStack.last());
    fragmentStack.last()->onResume();
    currentContainer->setCurrentWidget(fragmentStack.last());
}
