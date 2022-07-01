#ifndef SCREENSFACTORY_H
#define SCREENSFACTORY_H

#include "basescreensfactory.h"
#include "gamefragment.h"
#include "startfragment.h"
namespace Screens {
static const QString START_TEG="START";
static const QString GAME_TEG="GAME";
static const QString CHARACTER_TAG="CHARACTER";
static const QString STATISTIC_TEG="STATISTIC";
}
class ScreensFactory : public BaseScreensFactory
{
public:
    ScreensFactory();
    ~ScreensFactory();

    BaseFragment * create(QString tag) override;
    QString createStart() override;
};

#endif // SCREENSFACTORY_H
