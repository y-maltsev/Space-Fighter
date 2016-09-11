const int Screen_w=1600;
const int Screen_h=900;
SDL_Surface* screen;

Main_menu* Mmenu;

int LevelManager::Level=1; //The level of the game(set to 1)
LevelManager LManager; // and creating the manager

Player* player;
GUI* gui2; //player's user interface

//backgrounds
SDL_Surface* bg1;
SDL_Surface* bg2;
double bgY1=0,bgY2=-600;

vector<Enemy*> Enemy::Emanager; //container for ALL enemyes
 vector<Bullet*> Bullet::Bplayer;
 vector<Bullet*> Bullet::Benemy;
 vector<HBall*> HBall::HBplayer; //homing ball container
 vector<Bonus*> Bonus::Bonusl;
 vector<BoomP*> BoomP::booms;

 Bomb* Bomb::bomb=NULL; //player's special atack

//intro global vars
int intro=0;
SDL_Surface* intro_pic;
