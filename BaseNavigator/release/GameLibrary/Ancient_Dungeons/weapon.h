#ifndef WEAPON_H
#define WEAPON_H

#include<QImage>
#include<vector>
#include<QTimer>
#include<QtWidgets>
#include<QMediaPlayer>
class Weapon
{

private:
    std::vector<QImage> FrameTexture;
    int textureIndex=0;
    double FigthDistanse=0;
    double Damage;
    QMediaPlayer *Player;
public:
    ~Weapon()
    {
    Player->stop();
    }
    Weapon(){

    }
    Weapon(std::vector<QImage>,double,QMediaContent,double);
    QImage getTexture();
    void startAnimation();
    void setFrameTexture( std::vector<QImage> );

    double getFigthDistanse() const;

    double getDamage() const;

    int getTextureIndex() const;

public slots:
    void nextAnimation();
};

#endif // WEAPON_H
