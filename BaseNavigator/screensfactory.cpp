#include "screensfactory.h"

ScreensFactory::ScreensFactory() {}
ScreensFactory::~ScreensFactory() {}
BaseFragment *ScreensFactory::create(QString tag) {
    //TODO добавить экраны игр
  tag = tag.toUpper();
  qDebug() << tag;
  if (tag == Screens::START_TEG)
    return new StartFragment;
  else
  //if (tag == Screens::GAME_TEG)
    return new GameFragment;
  return nullptr;
  //    } else if (tag == LOGIN_TAG) {
  //        return new LoginFragment;
  //    } else if (tag == REGISTRATION_TAG) {
  //       // и так далее.....
  //    }
}

QString ScreensFactory::createStart() {
  return Screens::START_TEG; // идентификатор стартового экрана.
}
