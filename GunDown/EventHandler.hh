#include <vector>
using namespace std;

//functions used by the handler - see theyr definition below the event handler
void Player_keyboard_handler(SDL_Event event);
void Player_mouse_handler(SDL_Event event);
void Cheat_handler(SDL_Event event);
bool Menu_handler(SDL_Event event);


//The event handler
bool EventHandler(SDL_Event event){
    if(event.type == SDL_QUIT)
			return false;

    if(!Mmenu->main_menu){
            if(player->alive)
                if(!player->use_mouse){
                    Player_keyboard_handler(event);
                }
                else Player_mouse_handler(event);

                Cheat_handler(event);

            if(event.type==SDL_KEYDOWN) {
                if(event.key.keysym.sym==SDLK_n){ //player resurect - universal
                    player->alive=true;
                    player->x=(Screen_w/2)-33;
                    player->y=Screen_h+20;
                    player->health=10;
                    player->lives--;
                    player->incomming=true;
                }
            }

            if(event.key.keysym.sym==SDLK_ESCAPE){
                Mmenu->main_menu=true;
            }

    }
    else if(!Menu_handler(event)) return false;
    return true;
}









void Player_keyboard_handler(SDL_Event event){
    if(event.type==SDL_KEYDOWN) {
        if(event.key.keysym.sym==SDLK_RIGHT){
            player->moving = 1;
            player->dirX= 1;
        }
        if(event.key.keysym.sym==SDLK_LEFT){
            player->moving = 1;
            player->dirX= -1;
        }
        if(event.key.keysym.sym==SDLK_UP){
            player->moving_up = 1;
            player->dirY= 1;
        }
        if(event.key.keysym.sym==SDLK_DOWN){
            player->moving_up = 1;
            player->dirY= -1;
        }
        if(event.key.keysym.sym==SDLK_SPACE){
            if(player->weapon_level>9) player->weapon_level=9;
            player->firePlayerBullet(player->weapon_level);
        }
        if(event.key.keysym.sym==SDLK_RETURN){
            if(Bomb::bomb==NULL && (player->Player_bombs>0)){
                Bomb::Create();
                player->Player_bombs--;
            }
        }
    }
    if(event.type==SDL_KEYUP){
        if(event.key.keysym.sym==SDLK_RIGHT){
                player->moving = 0;
        }
        if(event.key.keysym.sym==SDLK_LEFT){
                player->moving = 0;
        }
        if(event.key.keysym.sym==SDLK_UP){
            player->moving_up = 0;
        }
        if(event.key.keysym.sym==SDLK_DOWN){
            player->moving_up = 0;
        }
    }
}










void Player_mouse_handler(SDL_Event event){
    if(player->alive && !player->incomming && player->use_mouse){
        if(event.type = SDL_MOUSEMOTION){

            player->x=event.motion.x-32;
            player->y=event.motion.y-28;
        }
        if(event.type = SDL_MOUSEBUTTONDOWN){
            if(event.button.button==SDL_BUTTON_LEFT){
                 if(player->weapon_level>9) player->weapon_level=9;
                    player->firePlayerBullet(player->weapon_level);
            }
            if(event.button.button==SDL_BUTTON_RIGHT){
                 if(Bomb::bomb==NULL && (player->Player_bombs>0)){
                        Bomb::Create();
                        player->Player_bombs--;
                 }
            }
        }
    }
}









void Cheat_handler(SDL_Event event){
    if(event.type==SDL_KEYDOWN) {
        if(event.key.keysym.sym==SDLK_q){
            player->use_mouse=!player->use_mouse;

        }
        if(event.key.keysym.sym==SDLK_r){

                player->Player_bombs++;
        }

        if(event.key.keysym.sym==SDLK_w){
                player->weapon_level++;

        }

        if(event.key.keysym.sym==SDLK_e){
                player->HBall_level++;
        }
    }
}








void GameReset(); //a function used by the menu for "new game"

bool Menu_handler(SDL_Event event){
if(event.type==SDL_KEYDOWN) {
    if(event.key.keysym.sym==SDLK_UP){
        Mmenu->menu_index--;
        if(Mmenu->menu_index<1)Mmenu->menu_index=3;
    }
    if(event.key.keysym.sym==SDLK_DOWN){
        Mmenu->menu_index++;
        if(Mmenu->menu_index>3)Mmenu->menu_index=1;
    }
    if(event.key.keysym.sym==SDLK_RETURN){
        bool break_main_cicle=false;
        switch(Mmenu->menu_index){
            case 1:{
            Mmenu->main_menu=false;
            break;
            }
            case 2:{
                GameReset();
            break;
            }
            case 3:{
            break_main_cicle=true;
            break;
            }
        }
        if(break_main_cicle) return false;
    }
    if(event.key.keysym.sym==SDLK_ESCAPE){
    Mmenu->main_menu=false;
    }
}
return true;
}

void GameReset(){
 for(int i=0;i<Enemy::Emanager.size();i++){
    Enemy::Emanager[i]->health=0;
 }
while(!Enemy::Emanager.empty()){
    Enemy::Emanager[0]->destroing_Enemy();
 }

 while(!Bonus::Bonusl.empty()){
    vector<Bonus*>::iterator itb;
    itb=Bonus::Bonusl.begin();
    SDL_FreeSurface(Bonus::Bonusl[0]->sprite);
    delete *itb;
    Bonus::Bonusl.erase(Bonus::Bonusl.begin());
 }
  while(!HBall::HBplayer.empty()){
    vector<HBall*>::iterator itb;
    itb=HBall::HBplayer.begin();
    SDL_FreeSurface(HBall::HBplayer[0]->sprite);
    delete *itb;
    HBall::HBplayer.erase(HBall::HBplayer.begin());
 }
 while(!Bullet::Benemy.empty()){
    vector<Bullet*>::iterator itb;
    itb= Bullet::Benemy.begin();
    SDL_FreeSurface( Bullet::Benemy[0]->sprite);
    delete *itb;
     Bullet::Benemy.erase( Bullet::Benemy.begin());
 }
  while(!Bullet::Bplayer.empty()){
    vector<Bullet*>::iterator itb;
    itb= Bullet::Bplayer.begin();
    SDL_FreeSurface( Bullet::Bplayer[0]->sprite);
    delete *itb;
     Bullet::Bplayer.erase( Bullet::Bplayer.begin());
 }
    LevelManager::Level=1;
    LManager.ChangePhase(new Suicide_phase_1());
    SDL_FreeSurface( player->sprite);
    SDL_FreeSurface( player->flames_moving);
    player = player->Init();
    Mmenu->main_menu=false;
}
