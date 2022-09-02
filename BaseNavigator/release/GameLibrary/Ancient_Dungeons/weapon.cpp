#include "weapon.h"




void Weapon::setFrameTexture( std::vector<QImage> frameTexture)
{
    FrameTexture=frameTexture;
    textureIndex=0;
   // connect(&animationTimer, SIGNAL(timeout()), this, SLOT(nextAnimation()));
}

double Weapon::getFigthDistanse() const
{
    return FigthDistanse;
}

double Weapon::getDamage() const
{
    return Damage;
}

int Weapon::getTextureIndex() const
{
    return textureIndex;
}

Weapon::Weapon(std::vector<QImage> frameTexture,double fightDistance,QMediaContent shotSound,double damage):
    FrameTexture(frameTexture),
    textureIndex(0),
    FigthDistanse(fightDistance),
    Damage(damage)
{
    Player=new QMediaPlayer;
    Player->setMedia(shotSound);
    Player->setVolume(100);
    Player->setPlaybackRate(1.);
}

QImage Weapon::getTexture()
{
    if((Player->mediaStatus()==QMediaPlayer::EndOfMedia || Player->mediaStatus()==QMediaPlayer::LoadedMedia) && Damage==0)
            Player->play();
    return FrameTexture[textureIndex];
}
void Weapon::startAnimation()
{
    if(textureIndex!=0 || (Player->mediaStatus()!=QMediaPlayer::EndOfMedia && Player->mediaStatus()!=QMediaPlayer::LoadedMedia))
        return;
    Player->play();
    textureIndex++;
}

void Weapon::nextAnimation()
{
    if(textureIndex!=0 || Damage==0)
    textureIndex=(textureIndex+1)%FrameTexture.size();

}
