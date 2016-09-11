void Bomb::Create(){
    Bomb::bomb = new Bomb();
    Bomb::bomb->sprite=SDL_LoadBMP("Images/Bomb.bmp");
	Bomb::bomb->speed=10;
	Bomb::bomb->x = 0;
	Bomb::bomb->y = Screen_h;
	Bomb::bomb->dirY =-1;
	Bomb::bomb->dirX=0;
}

void Bomb::Update(){
    bomb->y+=bomb->speed*bomb->dirY;

    for(int i=0;i!=HBall::HBplayer.size();i++){
      if(HBall::HBplayer[i]->y>bomb->y){
             vector<HBall*>::iterator ithb = HBall::HBplayer.begin()+i;
            SDL_FreeSurface(HBall::HBplayer[i]->sprite);
            delete *ithb;
            HBall::HBplayer.erase(HBall::HBplayer.begin()+i);
            i--;
      }
    }
    for(int i=0;i!=Bullet::Bplayer.size();i++){
      if(Bullet::Bplayer[i]->y>bomb->y){
             vector<Bullet*>::iterator it = Bullet::Bplayer.begin()+i;
            SDL_FreeSurface(Bullet::Bplayer[i]->sprite);
            delete *it;
            Bullet::Bplayer.erase(Bullet::Bplayer.begin()+i);
            i--;
      }
    }
    for(int i=0;i!=Bullet::Benemy.size();i++){
      if(Bullet::Benemy[i]->y>bomb->y){
             vector<Bullet*>::iterator it = Bullet::Benemy.begin()+i;
            SDL_FreeSurface(Bullet::Benemy[i]->sprite);
            delete *it;
            Bullet::Benemy.erase(Bullet::Benemy.begin()+i);
            i--;
      }
    }
     for(int i=0;i!=Enemy::Emanager.size();i++){
      if(Enemy::Emanager[i]->y+Enemy::Emanager[i]->height>bomb->y){
          Enemy::Emanager[i]->health--;
      }
    }



    if(bomb->y+47<=0){
    SDL_FreeSurface(bomb->sprite);
    delete bomb;
    bomb=NULL;
    }
}

void Bomb::Render(){
    SDL_Rect destination;
    destination.x=Bomb::bomb->x;
    destination.y=Bomb::bomb->y;
    SDL_BlitSurface(Bomb::bomb->sprite,0, screen, &destination);
}
