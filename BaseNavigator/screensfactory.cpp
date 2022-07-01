#include "screensfactory.h"

ScreensFactory::ScreensFactory()
{

}
ScreensFactory::~ScreensFactory()
{

}
BaseFragment* ScreensFactory::create(QString tag) {
    if (tag == Screens::START_TEG)
        return new StartFragment;
    if (tag == Screens::GAME_TEG)
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

