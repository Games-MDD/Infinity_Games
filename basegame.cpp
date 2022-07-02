#include "basegame.h"


BaseGame::BaseGame()
{

}

void BaseGame::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);
    emit showedUp();
}
