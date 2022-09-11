#include "startfragment.h"

StartFragment::StartFragment() {
  this->setCursor(Qt::OpenHandCursor);
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  setLayout(mainLayout);
  // Logo Label
  QLabel *LogoLabel = new QLabel("Infinity Games Studio", this);
  LogoLabel->setPalette(QPalette(Qt::GlobalColor::red));
  mainLayout->addWidget(LogoLabel);
  // Splitrer

  QSplitter *firstSplitter = new QSplitter(Qt::Horizontal, this);
  QPalette SplitterPallete;
  SplitterPallete.setColor(QPalette::Background, Qt::red);
  firstSplitter->setPalette(SplitterPallete);
  mainLayout->addWidget(firstSplitter);
  // Choose Frame
  QHBoxLayout *FrameLayout = new QHBoxLayout;
  FrameLayout->setSpacing(0);
  //FrameLayout->addWidget(new QPushButton("Games"));
  //FrameLayout->addWidget(new QPushButton("Account"));
  //FrameLayout->addWidget(new QPushButton("Statistics"));
  mainLayout->addLayout(FrameLayout);
  // StartButton
  QPushButton *StartGameButton = new QPushButton("Play Game", this);
  mainLayout->addWidget(StartGameButton);
  // GamesTags
  GameTagsModel = new QStandardItemModel;
  GameTagsModel->setItem(0, new QStandardItem(QIcon(":/icon/Resource/MinerIcon.png"),"Miner"));
  GameTagsModel->setItem(1, new QStandardItem(QIcon(":/icon/Resource/BreakoutIcon.png"),"Breakout"));
  GameTagsModel->setItem(2, new QStandardItem(QIcon(":/icon/Resource/SnakeIcon.png"),"Snake"));
  GameTagsModel->setItem(3, new QStandardItem(QIcon(":/icon/Resource/HangManIcon.jpg"),"Hangman"));
  GameTagsModel->setItem(4, new QStandardItem(QIcon(":/icon/Resource/Ancient_Dungeons.gif"),"Ancient_Dungeons"));
  GameTagsListView = new QListView;
  GameTagsListView->setModel(GameTagsModel);
  GameTagsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  //GameTagsListView->setBackgroundRole(QPalette::Dark);
  GameTagsListView->setPalette(QPalette(Qt::blue,Qt::blue));
  mainLayout->addWidget(GameTagsListView);
  // connect
  connect(StartGameButton, SIGNAL(clicked()), this, SLOT(StartNewGame()));
  //
  //set font
  int id = QFontDatabase::addApplicationFont(
      ":/font/Resource/8-bit Limit BRK.ttf");
  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  setFont(QFont(family));
}
StartFragment::~StartFragment() {}

void StartFragment::StartNewGame() {
  int currentRow = GameTagsListView->currentIndex().row();
  if (currentRow == -1) {
    qDebug() << "Nothing current!";
    return;
  }
  qDebug() << "Current Game :" << GameTagsModel->item(currentRow)->text();
  // TODO
  QProcess * newGame=new QProcess(this);
  if(GameTagsModel->item(currentRow)->text()=="Breakout")
  {

      newGame->startDetached(QDir::currentPath()+"/GameLibrary/Breakout/release/Breakout.exe");
  }
  if(GameTagsModel->item(currentRow)->text()=="Miner")
  {

      newGame->startDetached(QDir::currentPath()+"/GameLibrary/Miner/release/Miner.exe");
  }
  if(GameTagsModel->item(currentRow)->text()=="Snake")
  {
       newGame->startDetached(QDir::currentPath()+"/GameLibrary/Snake/release/Snake.exe");
  }
  if(GameTagsModel->item(currentRow)->text()=="Hangman")
  {
       newGame->startDetached(QDir::currentPath()+"/GameLibrary/Hangman/release/Hangman.exe");
  }
  if(GameTagsModel->item(currentRow)->text()=="Ancient_Dungeons")
  {
       newGame->startDetached(QDir::currentPath()+"/GameLibrary/Ancient_Dungeons/release/RayCastingRaner.exe");
  }
  //emit navigateTo(GameTagsModel->item(currentRow)->text());
}
