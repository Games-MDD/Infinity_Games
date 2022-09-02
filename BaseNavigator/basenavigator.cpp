#include "basenavigator.h"

BaseNavigator::BaseNavigator(QStackedWidget *container,
                             BaseScreensFactory *_screensFactory) {
  this->currentContainer = container;
  this->screensFactory = _screensFactory;
  BaseFragment *startFragment = getStartScreen();
  this->fragmentStack.append(startFragment);
  currentContainer->addWidget(fragmentStack.last());
  currentContainer->setCurrentIndex(0);
}

BaseNavigator::~BaseNavigator() {
  delete currentContainer;
  delete screensFactory;
  while (!fragmentStack.empty()) {
    delete fragmentStack.last();
    fragmentStack.removeLast();
  }
}

BaseFragment *BaseNavigator::getStartScreen() {
  return createAndConnect(this->screensFactory->createStart());
}

BaseFragment *BaseNavigator::createAndConnect(QString tag) {
  BaseFragment *fragment = this->screensFactory->create(tag);
  connectFragment(fragment);
  return fragment;
}

void BaseNavigator::connectFragment(BaseFragment *fragment) {
  connect(fragment, SIGNAL(back()), this, SLOT(back()));
  // connect(fragment, &BaseFragment::replace, this, &BaseNavigator::replace);
  connect(fragment, SIGNAL(navigateTo(QString)), this,
          SLOT(navigateTo(QString)));
  // connect(fragment, &BaseFragment::newRootScreen, this,
  // &BaseNavigator::newRootScreen); connect(fragment,
  // &BaseFragment::navigateWhithData, this, &BaseNavigator::navigateWhithData);
}

void BaseNavigator::disconnectFragment(BaseFragment *fragment) {
  disconnect(fragment, SIGNAL(back()), this, SLOT(back()));
  // disconnect(fragment, &BaseFragment::replace, this,
  // &BaseNavigator::replace);
  disconnect(fragment, SIGNAL(navigateTo(QString)), this,
             SLOT(navigateTo(QString)));
  // disconnect(fragment, &BaseFragment::newRootScreen, this,
  // &BaseNavigator::newRootScreen); disconnect(fragment,
  // &BaseFragment::navigateWhithData, this, &BaseNavigator::navigateWhithData);
}

void BaseNavigator::navigateTo(QString tag) {
  qDebug() << tag;
  BaseFragment *newFragment = this->screensFactory->create(tag);
  if (newFragment == nullptr) {
    qDebug() << "Unknown tag!";
    return;
  }
  fragmentStack.last()->onPause();
  disconnectFragment(fragmentStack.last());
  connectFragment(newFragment);
  fragmentStack.append(newFragment);
  currentContainer->addWidget(newFragment);
  currentContainer->setCurrentWidget(newFragment);
}

void BaseNavigator::back() {
  if (fragmentStack.size() == 0)
    return;
  currentContainer->removeWidget(fragmentStack.last());
  delete fragmentStack.last();
  disconnectFragment(fragmentStack.last());
  fragmentStack.removeLast();
  connectFragment(fragmentStack.last());
  fragmentStack.last()->onResume();
  currentContainer->setCurrentWidget(fragmentStack.last());
}
