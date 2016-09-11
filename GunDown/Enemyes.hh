#include <vector>
using namespace std;




//Base class functions start
//--------------------------------------------------------------------------
void Enemy::Update_all_Enemyes(){
    for(int i=0;i<Emanager.size();i++)
        Emanager[i]->Update();
}
void Enemy::Render_all_Enemyes(){
    for(int i=0;i<Emanager.size();i++)
        Emanager[i]->Render();

}

bool Enemy::destroing_Enemy(){
        if(this->health<=0){
            //which element of the Emanager this object is
            int obj_Emanag_index;
            for(int i=0;i<Enemy::Emanager.size();i++)
                if(Enemy::Emanager[i]==this) {obj_Emanag_index=i; break;}

            // relocate the HBalls
            for(int k=0;k<HBall::HBplayer.size();k++){
                if(HBall::HBplayer[k]->target_index>obj_Emanag_index)  HBall::HBplayer[k]->target_index--;
                if(HBall::HBplayer[k]->target_index==obj_Emanag_index) HBall::HBplayer[k]->has_target=false;
            }
            //create bonus if the enemy holds it and destroy the enemy
            player->inc_score(this->score_value);
            if(this->bonus_hold)
                Bonus::create_bonus(x+(width/2 - 15) ,y+(height/2 - 15),rand()%4+1);
            SDL_FreeSurface(this->sprite);
            vector<Enemy*>::iterator ite = Enemy::Emanager.begin()+obj_Emanag_index;
            delete *ite;
            Enemy::Emanager.erase(Enemy::Emanager.begin()+obj_Emanag_index);
            return true;
        }
        return false;
}

//Base class functions end
//--------------------------------------------------------------------------






//Royal guard functions start
//--------------------------------------------------------------------------


void Royal_Guard::create_RGenemy(int pos_x,int pos_y, int Ymax_, bool bonus)
{
    Royal_Guard* RG = new Royal_Guard();
	RG->sprite= SDL_LoadBMP("Images/RoyalGuard.bmp");
	Uint32 colorkey = SDL_MapRGB( RG->sprite->format, 0, 0, 0);
	SDL_SetColorKey( RG->sprite, SDL_SRCCOLORKEY, colorkey );
    RG->width=83;
    RG->height=56;
	RG->x=pos_x;
	RG->y=pos_y;
	RG->dirY=1;
	RG->dirX=0.5;
	RG->speed = 5;
	RG->health = 10;
	RG->Ymax=Ymax_;
	RG->fire_interval=rand()%300+1;
	RG->bonus_hold=bonus;
	RG->score_value=250;
	Enemy::Emanager.push_back(RG);
}



void Royal_Guard::Update(){
this->Update_fire();
this->Update_impact_player_bullets();
this->Update_impact_player_HBalls();
}

void Royal_Guard::Update_fire(){
        fire_interval++;
        if(fire_interval==90000){fire_interval=0;}
        if(fire_interval%enemy_fire_rate==0) {
             FireBullet(Bullet::Benemy,"Images/EnemyBulet.bmp",x+40,y+56,0,1,6,(rand()%34+15)/10);
             enemy_fire_rate-=1;
             if(enemy_fire_rate==100)
             enemy_fire_rate=300;}

}

void Royal_Guard::Update_impact_player_bullets(){
    vector<Bullet*>& Bplayer = Bullet::Bplayer;
    vector<Bullet*>::iterator it;

        for(int k=0;k<Bplayer.size();k++){
                if(Bplayer[k]->y<=this->y+56 && Bplayer[k]->y>=this->y){
                    if(Bplayer[k]->x<=this->x+54 && Bplayer[k]->x>=this->x+29){
                        BoomP::create_boom(Bplayer[k]->x, Bplayer[k]->y,Bplayer[k]->index);
                        it = Bplayer.begin()+k;
                        SDL_FreeSurface(Bplayer[k]->sprite);
                        delete *it;
                        Bplayer.erase(Bplayer.begin()+k);
                        this->health--;

                    }
                }
                if(Bplayer[k]->y<=this->y+37 && Bplayer[k]->y>=this->y+11){
                    if(Bplayer[k]->x<=this->x+83 && Bplayer[k]->x>=this->x){
                        BoomP::create_boom(Bplayer[k]->x, Bplayer[k]->y,Bplayer[k]->index);
                        it = Bplayer.begin()+k;
                        SDL_FreeSurface(Bplayer[k]->sprite);
                        delete *it;
                        Bplayer.erase(Bplayer.begin()+k);
                        this->health--;
                    }
                }
        }
}
void Royal_Guard::Update_impact_player_HBalls(){
        vector<HBall*>& HBplayer = HBall::HBplayer;
        vector<HBall*>::iterator ithb;
 int k=0;
        while(HBplayer.size() > 0 && k<HBplayer.size()){
            if(HBplayer[k]->y<=this->y+56 && HBplayer[k]->y>=this->y){
                if(HBplayer[k]->x<=this->x+54 && HBplayer[k]->x>=this->x+29){
                    BoomP::create_boom(HBplayer[k]->x, HBplayer[k]->y,8);
                    ithb = HBplayer.begin()+k;
                    SDL_FreeSurface(HBplayer[k]->sprite);
                    delete *ithb;
                    HBplayer.erase(HBplayer.begin()+k);


                    this->health--;

                }
            }
            if(HBplayer[k]->y<=this->y+37 && HBplayer[k]->y>=this->y+11){
                if(HBplayer[k]->x<=this->x+83 && HBplayer[k]->x>=this->x){
                    BoomP::create_boom(HBplayer[k]->x, HBplayer[k]->y,8);
                    ithb = HBplayer.begin()+k;
                    SDL_FreeSurface(HBplayer[k]->sprite);
                    delete *ithb;
                    HBplayer.erase(HBplayer.begin()+k);

                    this->health--;

                }
            }
        k++;

        }
}



void Royal_Guard::Render(){
    SDL_Rect destination;
    destination.x=this->x;
    destination.y=this->y;
    SDL_BlitSurface(this->sprite,0, screen, &destination);
}

//Royal guard functions end
//--------------------------------------------------------------------------

//Suiceders functuions start
//--------------------------------------------------------------------------

void Suicide::create_Suicide(char* sprite_name, bool bonus)
{
    Suicide* sui = new Suicide();
	sui->sprite= SDL_LoadBMP(sprite_name);
	Uint32 colorkey = SDL_MapRGB( sui->sprite->format, 0, 0, 0);
	SDL_SetColorKey( sui->sprite, SDL_SRCCOLORKEY, colorkey );
	if(sprite_name=="Images/PSuicide.bmp")
	{
        sui->width=41;
        sui->height=44;
        sui->exploding=true;
	}
	else {
        sui->width=35;
        sui->height=44;
        sui->exploding=false;
    }
	sui->x=rand()%1560+1;
	sui->y=0;
	sui->dirY=1;
	sui->dirX=0;
	sui->speed = 5;
	sui->health = 4;
	sui->fire_interval=rand()%300+1;
	sui->bonus_hold=bonus;
	sui->score_value=100;

	Enemy::Emanager.push_back(sui);
}



void Suicide::Update(){
this->Update_movement();
if(!exploding) this->Update_fire();
this->Update_impact_player_bullets();
this->Update_impact_player_HBalls();
}

void Suicide::Update_movement(){
    y+=dirY*speed;
    if(exploding && y>=Screen_h-height){
            this->explode();
            this->score_value=0;
            this->health=0;
    }
    else if(y>=Screen_h){
            this->score_value=0;
            this->health=0;
         }
}
void Suicide::Update_fire(){
        fire_interval++;
        if(fire_interval==90000){fire_interval=0;}
        if(fire_interval%50==0) {
             FireBullet(Bullet::Benemy,"Images/EnemyBuletB.bmp",x+width-2,y+height,0,1,6);
        }
}

void Suicide::Update_impact_player_bullets(){
    vector<Bullet*>& Bplayer = Bullet::Bplayer;
    vector<Bullet*>::iterator it;

        for(int k=0;k<Bplayer.size();k++){
                if(Bplayer[k]->y<=this->y+this->height && Bplayer[k]->y>=this->y){
                    if(Bplayer[k]->x<=this->x+this->width && Bplayer[k]->x>=this->x){
                        BoomP::create_boom(Bplayer[k]->x, Bplayer[k]->y,Bplayer[k]->index);
                        it = Bplayer.begin()+k;
                        SDL_FreeSurface(Bplayer[k]->sprite);
                        delete *it;
                        Bplayer.erase(Bplayer.begin()+k);
                        this->health--;
                        if(this->health==0 && this->exploding) this->explode();
                    }
                }
        }
}
void Suicide::Update_impact_player_HBalls(){
        vector<HBall*>& HBplayer = HBall::HBplayer;
        vector<HBall*>::iterator ithb;
 int k=0;
        while(HBplayer.size() > 0 && k<HBplayer.size()){
            if(HBplayer[k]->y<=this->y+this->height && HBplayer[k]->y>=this->y){
                if(HBplayer[k]->x<=this->x+this->width && HBplayer[k]->x>=this->x){
                    BoomP::create_boom(HBplayer[k]->x, HBplayer[k]->y,8);
                    ithb = HBplayer.begin()+k;
                    SDL_FreeSurface(HBplayer[k]->sprite);
                    delete *ithb;
                    HBplayer.erase(HBplayer.begin()+k);
                    this->health--;
                    if(this->health==0 && this->exploding) this->explode();
                }
            }
        k++;

        }
}



void Suicide::Render(){
    SDL_Rect destination;
    destination.x=this->x;
    destination.y=this->y;
    SDL_BlitSurface(this->sprite,0, screen, &destination);
}

void Suicide::explode(){
    FireBullet(Bullet::Benemy,"Images/ExplodeBulet.bmp",x+(width/2)-2,y+(height/2)-2,0,1,6);
    FireBullet(Bullet::Benemy,"Images/ExplodeBulet.bmp",x+(width/2)-2,y+(height/2)-2,1,0,6);
    FireBullet(Bullet::Benemy,"Images/ExplodeBulet.bmp",x+(width/2)-2,y+(height/2)-2,0,-1,6);
    FireBullet(Bullet::Benemy,"Images/ExplodeBulet.bmp",x+(width/2)-2,y+(height/2)-2,-1,0,6);
    FireBullet(Bullet::Benemy,"Images/ExplodeBulet.bmp",x+(width/2)-2,y+(height/2)-2,0.707,0.707,6);
    FireBullet(Bullet::Benemy,"Images/ExplodeBulet.bmp",x+(width/2)-2,y+(height/2)-2,0.707,-0.707,6);
    FireBullet(Bullet::Benemy,"Images/ExplodeBulet.bmp",x+(width/2)-2,y+(height/2)-2,-0.707,0.707,6);
    FireBullet(Bullet::Benemy,"Images/ExplodeBulet.bmp",x+(width/2)-2,y+(height/2)-2,-0.707,-0.707,6);
}
