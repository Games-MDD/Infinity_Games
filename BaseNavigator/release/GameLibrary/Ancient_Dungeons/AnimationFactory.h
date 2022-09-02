#ifndef ANIMATIONFACTORY_H
#define ANIMATIONFACTORY_H
#include <QImage>
enum SpriteType {
  barrel,
  greenlight,
  pillar,
  Knight,
  patron,
  DoomHead,
  zombe

};
// 0 standart
//    0
//    ^
//    |
// 2<- ->6
//    |
//    \/
//    4
// 1-atack
// 2-die
class AnimationFactory {
public:
  std::vector<std::vector<std::vector<QImage>>> operator()(SpriteType Type) {
    std::vector<std::vector<QImage>> answer;
    if (Type == SpriteType::Knight) {
      return std::vector<std::vector<std::vector<QImage>>>(
          1,
          std::vector<std::vector<QImage>>(
              1,
              std::vector<QImage>(
                  1, QImage(":/Sprites/Resources/StaticSprite/Knight.png"))));
    }
    if (Type == SpriteType::barrel) {
      return std::vector<std::vector<std::vector<QImage>>>(
          1,
          std::vector<std::vector<QImage>>(
              1,
              std::vector<QImage>(
                  1, QImage(":/Sprites/Resources/StaticSprite/barrel.png"))));
    }
    if (Type == SpriteType::greenlight) {
      return std::vector<std::vector<std::vector<QImage>>>(
          1,
          std::vector<std::vector<QImage>>(
              1,
              std::vector<QImage>(
                  1,
                  QImage(":/Sprites/Resources/StaticSprite/greenlight.png"))));
    }
    if (Type == SpriteType::pillar) {
      return std::vector<std::vector<std::vector<QImage>>>(
          1,
          std::vector<std::vector<QImage>>(
              1,
              std::vector<QImage>(
                  1, QImage(":/Sprites/Resources/StaticSprite/pillar.png"))));
    }
    if (Type == SpriteType::patron) {
      return std::vector<std::vector<std::vector<QImage>>>(
          1,
          std::vector<std::vector<QImage>>(
              1,
              std::vector<QImage>(
                  1, QImage(":/patrons/Resources/patrons/pixil-frame-0.png"))));
    }
    if (Type == SpriteType::DoomHead) {
      std::vector<std::vector<std::vector<QImage>>> answer(3);
      answer[0].resize(8);
      for (size_t i = 0; i < 8; ++i)
        answer[0][i].resize(6);
      answer[1].resize(1);
      answer[2].resize(1);
      answer[1][0].resize(6);
      answer[2][0].resize(6);
      // standart
      // 0
      answer[0][0][0] = QImage(":/DoomHead/Resources/enemy/DoomHead/Beholder1.bmp.png");
      answer[0][0][1] = QImage(":/DoomHead/Resources/enemy/DoomHead/Beholder2.bmp.png");
      answer[0][0][2] = QImage(":/DoomHead/Resources/enemy/DoomHead/Beholder2.bmp.png");
      answer[0][0][3] = QImage(":/DoomHead/Resources/enemy/DoomHead/Beholder3.bmp.png");
      answer[0][0][4] = QImage(":/DoomHead/Resources/enemy/DoomHead/Beholder3.bmp.png");
      answer[0][0][5] = QImage(":/DoomHead/Resources/enemy/DoomHead/Beholder4.bmp.png");
      // 1
      answer[0][1][0] = QImage(":/zombe/Resources/enemy/Zombe/ZB1.bmp.png");
      answer[0][1][1] = QImage(":/zombe/Resources/enemy/Zombe/ZB1.bmp.png");
      answer[0][1][2] = QImage(":/zombe/Resources/enemy/Zombe/ZB1.bmp.png");
      answer[0][1][3] = QImage(":/zombe/Resources/enemy/Zombe/ZB2.bmp.png");
      answer[0][1][4] = QImage(":/zombe/Resources/enemy/Zombe/ZB2.bmp.png");
      answer[0][1][5] = QImage(":/zombe/Resources/enemy/Zombe/ZB2.bmp.png");
      // 2
      answer[0][2][0] = QImage(":/zombe/Resources/enemy/Zombe/ZC1.bmp.png");
      answer[0][2][1] = QImage(":/zombe/Resources/enemy/Zombe/ZC1.bmp.png");
      answer[0][2][2] = QImage(":/zombe/Resources/enemy/Zombe/ZC1.bmp.png");
      answer[0][2][3] = QImage(":/zombe/Resources/enemy/Zombe/ZC2.bmp.png");
      answer[0][2][4] = QImage(":/zombe/Resources/enemy/Zombe/ZC2.bmp.png");
      answer[0][2][5] = QImage(":/zombe/Resources/enemy/Zombe/ZC2.bmp.png");
      // 3
      answer[0][3][0] = QImage(":/zombe/Resources/enemy/Zombe/ZD1.bmp.png");
      answer[0][3][1] = QImage(":/zombe/Resources/enemy/Zombe/ZD1.bmp.png");
      answer[0][3][2] = QImage(":/zombe/Resources/enemy/Zombe/ZD1.bmp.png");
      answer[0][3][3] = QImage(":/zombe/Resources/enemy/Zombe/ZD2.bmp.png");
      answer[0][3][4] = QImage(":/zombe/Resources/enemy/Zombe/ZD2.bmp.png");
      answer[0][3][5] = QImage(":/zombe/Resources/enemy/Zombe/ZD2.bmp.png");
      // 4
      answer[0][4][0] = QImage(":/zombe/Resources/enemy/Zombe/ZE1.bmp.png");
      answer[0][4][1] = QImage(":/zombe/Resources/enemy/Zombe/ZE1.bmp.png");
      answer[0][4][2] = QImage(":/zombe/Resources/enemy/Zombe/ZE1.bmp.png");
      answer[0][4][3] = QImage(":/zombe/Resources/enemy/Zombe/ZE2.bmp.png");
      answer[0][4][4] = QImage(":/zombe/Resources/enemy/Zombe/ZE2.bmp.png");
      answer[0][4][5] = QImage(":/zombe/Resources/enemy/Zombe/ZE2.bmp.png");
      // 5
      answer[0][5][0] = QImage(":/zombe/Resources/enemy/Zombe/ZF1.bmp.png");
      answer[0][5][1] = QImage(":/zombe/Resources/enemy/Zombe/ZF1.bmp.png");
      answer[0][5][2] = QImage(":/zombe/Resources/enemy/Zombe/ZF1.bmp.png");
      answer[0][5][3] = QImage(":/zombe/Resources/enemy/Zombe/ZF2.bmp.png");
      answer[0][5][4] = QImage(":/zombe/Resources/enemy/Zombe/ZF2.bmp.png");
      answer[0][5][5] = QImage(":/zombe/Resources/enemy/Zombe/ZF2.bmp.png");
      // 6
      answer[0][6][0] = QImage(":/zombe/Resources/enemy/Zombe/ZG1.bmp.png");
      answer[0][6][1] = QImage(":/zombe/Resources/enemy/Zombe/ZG1.bmp.png");
      answer[0][6][2] = QImage(":/zombe/Resources/enemy/Zombe/ZG1.bmp.png");
      answer[0][6][3] = QImage(":/zombe/Resources/enemy/Zombe/ZG2.bmp.png");
      answer[0][6][4] = QImage(":/zombe/Resources/enemy/Zombe/ZG2.bmp.png");
      answer[0][6][5] = QImage(":/zombe/Resources/enemy/Zombe/ZG2.bmp.png");
      // 7
      answer[0][7][0] = QImage(":/zombe/Resources/enemy/Zombe/ZH1.bmp.png");
      answer[0][7][0] = QImage(":/zombe/Resources/enemy/Zombe/ZH1.bmp.png");
      answer[0][7][0] = QImage(":/zombe/Resources/enemy/Zombe/ZH1.bmp.png");
      answer[0][7][1] = QImage(":/zombe/Resources/enemy/Zombe/ZH2.bmp.png");
      answer[0][7][2] = QImage(":/zombe/Resources/enemy/Zombe/ZH2.bmp.png");
      answer[0][7][3] = QImage(":/zombe/Resources/enemy/Zombe/ZH2.bmp.png");
      for(int k=1;k<8;++k)
        for(int l=0;l<6;++l)
            answer[0][k][l]=answer[0][0][l];
      // atack
      answer[1][0][0] =
          QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderAtk1.bmp.png");
      answer[1][0][1] =
          QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderAtk1.bmp.png");
      answer[1][0][2] =
          QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderAtk2.bmp.png");
      answer[1][0][3] =
          QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderAtk2.bmp.png");
      answer[1][0][4] =
          QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderAtk3.bmp.png");
      answer[1][0][5] =
          QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderAtk3.bmp.png");
      // die
      answer[2][0][0] = QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderDying1.bmp.png");
      answer[2][0][1] = QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderDying1.bmp.png");
      answer[2][0][2] = QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderDying2.bmp.png");
      answer[2][0][3] = QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderDying2.bmp.png");
      answer[2][0][4] = QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderDying3.bmp.png");
      answer[2][0][5] = QImage(":/DoomHead/Resources/enemy/DoomHead/BeholderDead.bmp.png");
      return answer;
    }
    if (Type == SpriteType::zombe) {
      std::vector<std::vector<std::vector<QImage>>> answer(3);
      answer[0].resize(8);
      for (size_t i = 0; i < 8; ++i)
        answer[0][i].resize(6);
      answer[1].resize(1);
      answer[2].resize(1);
      answer[1][0].resize(6);
      answer[2][0].resize(6);
      // standart
      // 0
      answer[0][0][0] = QImage(":/zombe/Resources/enemy/Zombe/ZA1.bmp.png");
      answer[0][0][1] = QImage(":/zombe/Resources/enemy/Zombe/ZA1.bmp.png");
      answer[0][0][2] = QImage(":/zombe/Resources/enemy/Zombe/ZA1.bmp.png");
      answer[0][0][3] = QImage(":/zombe/Resources/enemy/Zombe/ZA2.bmp.png");
      answer[0][0][4] = QImage(":/zombe/Resources/enemy/Zombe/ZA2.bmp.png");
      answer[0][0][5] = QImage(":/zombe/Resources/enemy/Zombe/ZA2.bmp.png");
      // 1
      answer[0][1][0] = QImage(":/zombe/Resources/enemy/Zombe/ZB1.bmp.png");
      answer[0][1][1] = QImage(":/zombe/Resources/enemy/Zombe/ZB1.bmp.png");
      answer[0][1][2] = QImage(":/zombe/Resources/enemy/Zombe/ZB1.bmp.png");
      answer[0][1][3] = QImage(":/zombe/Resources/enemy/Zombe/ZB2.bmp.png");
      answer[0][1][4] = QImage(":/zombe/Resources/enemy/Zombe/ZB2.bmp.png");
      answer[0][1][5] = QImage(":/zombe/Resources/enemy/Zombe/ZB2.bmp.png");
      // 2
      answer[0][2][0] = QImage(":/zombe/Resources/enemy/Zombe/ZC1.bmp.png");
      answer[0][2][1] = QImage(":/zombe/Resources/enemy/Zombe/ZC1.bmp.png");
      answer[0][2][2] = QImage(":/zombe/Resources/enemy/Zombe/ZC1.bmp.png");
      answer[0][2][3] = QImage(":/zombe/Resources/enemy/Zombe/ZC2.bmp.png");
      answer[0][2][4] = QImage(":/zombe/Resources/enemy/Zombe/ZC2.bmp.png");
      answer[0][2][5] = QImage(":/zombe/Resources/enemy/Zombe/ZC2.bmp.png");
      // 3
      answer[0][3][0] = QImage(":/zombe/Resources/enemy/Zombe/ZD1.bmp.png");
      answer[0][3][1] = QImage(":/zombe/Resources/enemy/Zombe/ZD1.bmp.png");
      answer[0][3][2] = QImage(":/zombe/Resources/enemy/Zombe/ZD1.bmp.png");
      answer[0][3][3] = QImage(":/zombe/Resources/enemy/Zombe/ZD2.bmp.png");
      answer[0][3][4] = QImage(":/zombe/Resources/enemy/Zombe/ZD2.bmp.png");
      answer[0][3][5] = QImage(":/zombe/Resources/enemy/Zombe/ZD2.bmp.png");
      // 4
      answer[0][4][0] = QImage(":/zombe/Resources/enemy/Zombe/ZE1.bmp.png");
      answer[0][4][1] = QImage(":/zombe/Resources/enemy/Zombe/ZE1.bmp.png");
      answer[0][4][2] = QImage(":/zombe/Resources/enemy/Zombe/ZE1.bmp.png");
      answer[0][4][3] = QImage(":/zombe/Resources/enemy/Zombe/ZE2.bmp.png");
      answer[0][4][4] = QImage(":/zombe/Resources/enemy/Zombe/ZE2.bmp.png");
      answer[0][4][5] = QImage(":/zombe/Resources/enemy/Zombe/ZE2.bmp.png");
      // 5
      answer[0][5][0] = QImage(":/zombe/Resources/enemy/Zombe/ZF1.bmp.png");
      answer[0][5][1] = QImage(":/zombe/Resources/enemy/Zombe/ZF1.bmp.png");
      answer[0][5][2] = QImage(":/zombe/Resources/enemy/Zombe/ZF1.bmp.png");
      answer[0][5][3] = QImage(":/zombe/Resources/enemy/Zombe/ZF2.bmp.png");
      answer[0][5][4] = QImage(":/zombe/Resources/enemy/Zombe/ZF2.bmp.png");
      answer[0][5][5] = QImage(":/zombe/Resources/enemy/Zombe/ZF2.bmp.png");
      // 6
      answer[0][6][0] = QImage(":/zombe/Resources/enemy/Zombe/ZG1.bmp.png");
      answer[0][6][1] = QImage(":/zombe/Resources/enemy/Zombe/ZG1.bmp.png");
      answer[0][6][2] = QImage(":/zombe/Resources/enemy/Zombe/ZG1.bmp.png");
      answer[0][6][3] = QImage(":/zombe/Resources/enemy/Zombe/ZG2.bmp.png");
      answer[0][6][4] = QImage(":/zombe/Resources/enemy/Zombe/ZG2.bmp.png");
      answer[0][6][5] = QImage(":/zombe/Resources/enemy/Zombe/ZG2.bmp.png");
      // 7
      answer[0][7][0] = QImage(":/zombe/Resources/enemy/Zombe/ZH1.bmp.png");
      answer[0][7][1] = QImage(":/zombe/Resources/enemy/Zombe/ZH1.bmp.png");
      answer[0][7][2] = QImage(":/zombe/Resources/enemy/Zombe/ZH1.bmp.png");
      answer[0][7][3] = QImage(":/zombe/Resources/enemy/Zombe/ZH2.bmp.png");
      answer[0][7][4] = QImage(":/zombe/Resources/enemy/Zombe/ZH2.bmp.png");
      answer[0][7][5] = QImage(":/zombe/Resources/enemy/Zombe/ZH2.bmp.png");
      // atack
      answer[1][0][0] =
          QImage(":/zombe/Resources/enemy/Zombe/ZAttack1.bmp.png");
      answer[1][0][1] =
          QImage(":/zombe/Resources/enemy/Zombe/ZAttack1.bmp.png");
      answer[1][0][2] =
          QImage(":/zombe/Resources/enemy/Zombe/ZAttack2.bmp.png");
      answer[1][0][3] =
          QImage(":/zombe/Resources/enemy/Zombe/ZAttack2.bmp.png");
      answer[1][0][4] =
          QImage(":/zombe/Resources/enemy/Zombe/ZAttack3.bmp.png");
      answer[1][0][5] =
          QImage(":/zombe/Resources/enemy/Zombe/ZAttack3.bmp.png");
      // die
      answer[2][0][0] = QImage(":/zombe/Resources/enemy/Zombe/Zdie1.bmp.png");
      answer[2][0][1] = QImage(":/zombe/Resources/enemy/Zombe/Zdie2.bmp.png");
      answer[2][0][2] = QImage(":/zombe/Resources/enemy/Zombe/Zdie2.bmp.png");
      answer[2][0][3] = QImage(":/zombe/Resources/enemy/Zombe/Zdie3.bmp.png");
      answer[2][0][4] = QImage(":/zombe/Resources/enemy/Zombe/Zdie3.bmp.png");
      answer[2][0][5] = QImage(":/zombe/Resources/enemy/Zombe/Zdie4.bmp.png");
      return answer;
    }
  }
};

#endif // ANIMATIONFACTORY_H
