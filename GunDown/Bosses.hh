



//Boss1 Formation  Functions start
//--------------------------------------------------------------------------------------------------------------------
void Boss_1::Create_Boss_1(){
    Boss_1* boss = new Boss_1();
    boss->sprite= SDL_LoadBMP("Images/Boss.bmp");
    Uint32 colorkey = SDL_MapRGB( boss->sprite->format, 0, 0, 0);
    SDL_SetColorKey( boss->sprite, SDL_SRCCOLORKEY, colorkey );
    boss->width=137;
    boss->height=144;
    boss->y = 0;
    if(LevelManager::Level%2==1){
        boss->x = Screen_w+130;
        boss->dirX=-0.1;
    }
    else{
        boss->x = -130;
        boss->dirX=0.1;
    }
    boss->dirY=0;
    boss->speed = 5;
    boss->prime_weap_interval=0;
    boss->health=200;
    boss->score_value=2000;
    boss->lazer_interval=rand()%1100+701;
    boss->Lazer=SDL_LoadBMP("Images/Lazer.bmp");
    boss->charge_laser=SDL_LoadBMP("Images/BoomBig.bmp");
    boss->LeftShield=0;
    boss->RightShield=0;
    boss->Shields=SDL_LoadBMP("Images/BossShields.bmp");
    Enemy::Emanager.push_back(boss);
}



 void Boss_1::Update(){
 this->Update_FirePrimeWeapon();
 this->Update_FireLazer();
 this->Update_ImpactPlayerBullets();
 this->Update_ImpactPlayerHBalls();
 this->Update_LeftShield();
 this->Update_RightShield();
 if(player->y<=111)
    if(player->x<=this->x+143 && player->x+64>=this->x-5)
        player->health--;
 }

 void Boss_1::Update_FirePrimeWeapon(){

     if(lazer_interval>=700){
			this->prime_weap_interval++;
			if(this->prime_weap_interval>=300 && this->prime_weap_interval<=600)
				//if(this->prime_weap_interval%3==0)
					this->bossfirebullet(); // see function definition below
			if(this->prime_weap_interval>600) this->prime_weap_interval=0;
				}
 }

 void Boss_1::bossfirebullet(){
    int left=rand()%2+1;
	double DirX=rand()%708;
	DirX/=1000;
	double DirY=rand()%708;
	DirY/=1000;
	if(left==1) DirX=-DirX;
	FireBullet(Bullet::Benemy,"Images/BossBulet.bmp",this->x+66,this->y+144,DirX,DirY,6);
}

void Boss_1::Update_FireLazer(){ // also modify movement while fireing and check if player is hited by the lazer(kill player and remove 1 weapon level)
    bool dirE;
    if(this->dirX > 0) dirE=true;
    else dirE=false;
    lazer_interval++;
      if(lazer_interval>=2500) lazer_interval=0;

      if(lazer_interval<=700&&lazer_interval>=200){
            if(this->x+137>=Screen_w-40) dirE=false;
            else if(this->x<=40) dirE=true;
           if(dirE)this->dirX=0.7;
            else this->dirX=-0.7;
            if( this->x+55>=player->x && this->x+55<=player->x+67){
                if(player->health>0)player->health--;
            }
            if( this->x+80>=player->x && this->x+80<=player->x+67){
                if(player->health>0) player->health--;
            }
            if(player->health==0 && player->alive){ player->alive=false; if(player->weapon_level>1)player->weapon_level--;}
      }
}

void Boss_1::Update_ImpactPlayerBullets(){
    vector<Bullet*>&  Bplayer = Bullet::Bplayer;
    vector<Bullet*>::iterator it;
     for(int i=0;Bplayer.size() > 0 && i<Bplayer.size();i++){
        if(Bplayer[i]->y<=this->y+144 && Bplayer[i]->y>=this->y+102){
            if(Bplayer[i]->x<=this->x+126 && Bplayer[i]->x>=this->x+10){
                BoomP::create_boom(Bplayer[i]->x, Bplayer[i]->y,Bplayer[i]->index);
                it = Bplayer.begin()+i;
                SDL_FreeSurface(Bplayer[i]->sprite);
                delete *it;
                Bplayer.erase(Bplayer.begin()+i);
                this->health-=1;
                if(this->health==0){
                SDL_FreeSurface(this->Lazer);
                SDL_FreeSurface(this->charge_laser);
                }
            }
        }
    }
}


void Boss_1::Update_ImpactPlayerHBalls(){
    vector<HBall*>&  HBplayer = HBall::HBplayer;
    vector<HBall*>::iterator ithb;
     for(int i=0;HBplayer.size() > 0 && i<HBplayer.size();i++){
            if(HBplayer[i]->y<=this->y+144 && HBplayer[i]->y>=this->y+102){
                if(HBplayer[i]->x<=this->x+126 && HBplayer[i]->x>=this->x+10){
                    BoomP::create_boom(HBplayer[i]->x, HBplayer[i]->y,8);
                    ithb = HBplayer.begin()+i;
                    SDL_FreeSurface(HBplayer[i]->sprite);
                    delete *ithb;
                    HBplayer.erase(HBplayer.begin()+i);
                    this->health-=1;
                if(this->health==0){
                    SDL_FreeSurface(this->Lazer);
                    SDL_FreeSurface(this->charge_laser);
                    SDL_FreeSurface(this->Shields);
                }
            }
        }
     }
}

void Boss_1::Update_LeftShield(){

        vector<HBall*>&  HBplayer = HBall::HBplayer;
        vector<HBall*>::iterator ithb;
        vector<Bullet*>&  Bplayer = Bullet::Bplayer;
        vector<Bullet*>::iterator it;
        if(LeftShield>0){
            LeftShield++;
            if(LeftShield==300) LeftShield=0;
        }



        for(int i=0;Bplayer.size() > 0 && i<Bplayer.size();i++){
            if(Bplayer[i]->y<=this->y+111 && Bplayer[i]->y>=this->y){
                if(Bplayer[i]->x<=this->x+143 && Bplayer[i]->x>=this->x+69){
                    it = Bplayer.begin()+i;
                    SDL_FreeSurface(Bplayer[i]->sprite);
                    delete *it;
                    Bplayer.erase(Bplayer.begin()+i);
                    LeftShield=1;
                }
            }
        }

        for(int i=0;HBplayer.size() > 0 && i<HBplayer.size();i++){
            if(HBplayer[i]->y<=this->y+111 && HBplayer[i]->y>=this->y){
                if(HBplayer[i]->x<=this->x+143 && HBplayer[i]->x>=this->x+69){
                    ithb = HBplayer.begin()+i;
                    SDL_FreeSurface(HBplayer[i]->sprite);
                    delete *ithb;
                    HBplayer.erase(HBplayer.begin()+i);
                    LeftShield=1;
                }
            }
        }



}

void Boss_1::Update_RightShield(){
        vector<HBall*>&  HBplayer = HBall::HBplayer;
        vector<HBall*>::iterator ithb;
        vector<Bullet*>&  Bplayer = Bullet::Bplayer;
        vector<Bullet*>::iterator it;
        if(RightShield>0){
            RightShield++;
            if(RightShield==300) RightShield=0;
        }



        for(int i=0;Bplayer.size() > 0 && i<Bplayer.size();i++){
            if(Bplayer[i]->y<=this->y+111 && Bplayer[i]->y>=this->y){
                if(Bplayer[i]->x<=this->x+69 && Bplayer[i]->x>=this->x-5){
                    it = Bplayer.begin()+i;
                    SDL_FreeSurface(Bplayer[i]->sprite);
                    delete *it;
                    Bplayer.erase(Bplayer.begin()+i);
                    RightShield=1;
                }
            }
        }

        for(int i=0;HBplayer.size() > 0 && i<HBplayer.size();i++){
            if(HBplayer[i]->y<=this->y+111 && HBplayer[i]->y>=this->y){
                if(HBplayer[i]->x<=this->x+69 && HBplayer[i]->x>=this->x-5){
                    ithb = HBplayer.begin()+i;
                    SDL_FreeSurface(HBplayer[i]->sprite);
                    delete *ithb;
                    HBplayer.erase(HBplayer.begin()+i);
                    RightShield=1;
                }
            }
        }

}

void Boss_1::Render(){
    SDL_Rect destination;
    destination.x=this->x;
    destination.y=this->y;
    SDL_BlitSurface(this->sprite,0, screen, &destination);

   if(lazer_interval<=700 && lazer_interval>=200){
        destination.x=this->x+55;
        destination.y=this->y+144;
        SDL_BlitSurface(this->Lazer,0, screen, &destination);

    }
    if(lazer_interval<=200){
        destination.x=this->x+55;
        destination.y=this->y+144;
        SDL_BlitSurface(this->charge_laser,0, screen, &destination);
    }

    if(RightShield>0 && RightShield<300){
        destination.x=this->x-5;
        destination.y=this->y;
        SDL_BlitSurface(this->Shields,0, screen, &destination);
    }
    if(LeftShield>0 && LeftShield<300){
        destination.x=this->x+138;
        destination.y=this->y;
        SDL_BlitSurface(this->Shields,0, screen, &destination);
    }
}

//Boss1 Formation  Functions end
//--------------------------------------------------------------------------------------------------------------------
