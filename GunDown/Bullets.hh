
//universal bullet function
void FireBullet(
                vector<Bullet*>& Bullvect,
                char* sprite_pic,
                double pos_X,
                double Pos_Y,
                double DirX,
                double DirY,
                int bul_index,
                double bul_speed=3
                ){


Bullet* bullet = new Bullet;
bullet->sprite=SDL_LoadBMP(sprite_pic);
bullet->speed=bul_speed;
bullet->x= pos_X;
bullet->y = Pos_Y;
bullet->dirX =DirX;
bullet->dirY =DirY;
bullet->index=bul_index;
Bullvect.push_back(bullet);
}

// class bullet functions
 void Bullet::Render_all_Bullets(){
            SDL_Rect destination;
            //player bullets
			for(int i=0;i!=Bullet::Bplayer.size();i++){
				destination.x=Bullet::Bplayer[i]->x;
				destination.y=Bullet::Bplayer[i]->y;
				destination.w=14;
				destination.h=14;
				SDL_BlitSurface(Bullet::Bplayer[i]->sprite,0, screen, &destination);

			}
            //enemy bullets
			for(int i=0;i!=Bullet::Benemy.size();i++){
				destination.x=Bullet::Benemy[i]->x;
				destination.y=Bullet::Benemy[i]->y;
				destination.w=14;
				destination.h=14;
				SDL_BlitSurface(Bullet::Benemy[i]->sprite,0, screen, &destination);

			}
    }

void Bullet::Update_all_Bullets(){
    //rename the vectors for easyer use
    vector<Bullet*>& Bplayer = Bullet::Bplayer;
    vector<Bullet*>& Benemy = Bullet::Benemy;

    vector<Bullet*>::iterator it;

    //player bullets moving
    for(int i=0;i!=Bplayer.size();i++){
        Bplayer[i]->y+=Bplayer[i]->speed*Bplayer[i]->dirY*2;
        Bplayer[i]->x+=Bplayer[i]->dirX*Bplayer[i]->speed*2;
    }
    //Player bulets out of map
    while(Bplayer.size() > 0 && Bplayer[0]->y<=10) {
        it = Bplayer.begin();
        SDL_FreeSurface(Bplayer[0]->sprite);
        delete *it;
        Bplayer.erase(Bplayer.begin());
    }

    //Enemy bulets moves
    for(int i=0;i!=Benemy.size();i++){
        Benemy[i]->y+=Benemy[i]->speed*Benemy[i]->dirY;
        Benemy[i]->x+=Benemy[i]->speed*Benemy[i]->dirX;

    }
    // Enemy bulets out of map
    while(Benemy.size() > 0 && (
                                (Benemy[0]->y>=Screen_h || Benemy[0]->y<=0) ||
                                (Benemy[0]->x>=Screen_w || Benemy[0]->x<=0)
                               )) {
        it = Benemy.begin();
        SDL_FreeSurface(Benemy[0]->sprite);
        delete *it;
        Benemy.erase(Benemy.begin());
    }
}
