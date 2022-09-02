#ifndef WEAPONFACTORY_H
#define WEAPONFACTORY_H
#include<weapon.h>
#include<QtDebug>
enum WeaponType{
    knife,
    pistol,
    rifle,
    startScreen,
    dieGame,
    endGame
};
class WeaponFactory{
public:
    Weapon operator()(WeaponType type)
    {
        std::vector<QImage> frameTexture;
        if(type==WeaponType::startScreen)
        {
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/1aa.bmp"));
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/2aa.bmp"));
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/3aa.bmp"));
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/4aa.bmp"));
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/5aa.bmp"));
            return Weapon(frameTexture,0,QUrl("qrc:/StartScreen/Resources/StartScreen/kevin-macleod-8bit-dungeon-level.mp3"),0);
        }
        if(type==WeaponType::dieGame)
        {
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/txt_cyberscreen.png"));
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/txt_cyberscreen1.png"));
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/txt_cyberscreen2.png"));
            return Weapon(frameTexture,0,QUrl("qrc:/StartScreen/Resources/StartScreen/kevin-macleod-8bit-dungeon-level.mp3"),0);
        }
        if(type==WeaponType::endGame)
        {
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/1aa.bmp"));
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/2aa.bmp"));
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/3aa.bmp"));
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/4aa.bmp"));
            frameTexture.push_back(QImage(":/StartScreen/Resources/StartScreen/5aa.bmp"));
            return Weapon(frameTexture,0,QUrl("qrc:/StartScreen/Resources/StartScreen/kevin-macleod-8bit-dungeon-level.mp3"),0);
        }
        if(type==WeaponType::knife)
        {
            frameTexture.push_back(QImage(":/knife/Resources/weapon/weapon1/knife/SPR_KNIFEATK1.BMP.png"));
            frameTexture.push_back(QImage(":/knife/Resources/weapon/weapon1/knife/SPR_KNIFEATK2.BMP.png"));
            frameTexture.push_back(QImage(":/knife/Resources/weapon/weapon1/knife/SPR_KNIFEATK3.BMP.png"));
            frameTexture.push_back(QImage(":/knife/Resources/weapon/weapon1/knife/SPR_KNIFEATK4.BMP.png"));
            frameTexture.push_back(QImage(":/knife/Resources/weapon/weapon1/knife/SPR_KNIFEATK1.BMP.png"));
            frameTexture.push_back(QImage(":/knife/Resources/weapon/weapon1/knife/SPR_KNIFEREADY.BMP.png"));
            return Weapon(frameTexture,50,QUrl("qrc:/knife/Resources/weapon/weapon1/knife/knife.mp3"),50);
        }
        if(type==WeaponType::pistol)
        {
            frameTexture.push_back(QImage(":/pistol/Resources/weapon/weapon2/pistole0/SPR_PISTOLATK1.BMP.png"));
            frameTexture.push_back(QImage(":/pistol/Resources/weapon/weapon2/pistole0/SPR_PISTOLATK2.BMP.png"));
            frameTexture.push_back(QImage(":/pistol/Resources/weapon/weapon2/pistole0/SPR_PISTOLATK3.BMP.png"));
            frameTexture.push_back(QImage(":/pistol/Resources/weapon/weapon2/pistole0/SPR_PISTOLATK4.BMP.png"));
            frameTexture.push_back(QImage(":/pistol/Resources/weapon/weapon2/pistole0/SPR_PISTOLREADY.BMP.png"));
            return Weapon(frameTexture,500,QUrl("qrc:/pistol/Resources/weapon/weapon2/pistole0/pistol.mp3"),25);
        }
        if(type==WeaponType::rifle)
        {
        frameTexture.push_back(QImage(":/rifle/Resources/weapon/weapon3/rifle0/SPR_MACHINEGUNATK1.BMP.png"));
        frameTexture.push_back(QImage(":/rifle/Resources/weapon/weapon3/rifle0/SPR_MACHINEGUNATK2.BMP.png"));
        frameTexture.push_back(QImage(":/rifle/Resources/weapon/weapon3/rifle0/SPR_MACHINEGUNATK3.BMP.png"));
        frameTexture.push_back(QImage(":/rifle/Resources/weapon/weapon3/rifle0/SPR_MACHINEGUNATK4.BMP.png"));
        frameTexture.push_back(QImage(":/rifle/Resources/weapon/weapon3/rifle0/SPR_MACHINEGUNREADY.BMP.png"));
        return Weapon(frameTexture,300,QUrl("qrc:/rifle/Resources/weapon/weapon3/rifle0/machine-gun.mp3"),100);
        }
    }
};

#endif // WEAPONFACTORY_H
