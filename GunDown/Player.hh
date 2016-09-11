#include <vector>
using namespace std;

Player* Player::Init(){


Player* player2= new Player();
       player2->alive=true;

       player2->sprite= SDL_LoadBMP("Images/shipfinal.bmp");

       Uint32 colorkey = SDL_MapRGB( player2->sprite->format, 0, 0, 0);
       SDL_SetColorKey( player2->sprite, SDL_SRCCOLORKEY, colorkey );

       player2->animation_index=0;
       player2->animation_index_interval=0;
       player2->x=Screen_w/2-33;
       player2->y=Screen_h+20;
       player2->moving=0;
       player2->moving_up=0;
       player2->dirX=0;
       player2->dirY=0;
       player2->speed = 2;
       player2->incomming=true;
       player2->health=10;
       player2->lives=5;
       player2->weapon_level=1;
       player2->HBall_level=0;
       player2->HBall_interval=0;
       player2->Player_bombs=5;
       player2->Player_score=0;
       player2->use_mouse=false;
       player2->flames_moving= SDL_LoadBMP("Images/Flame.bmp");
       Uint32 colorkey2 = SDL_MapRGB( player2->flames_moving->format, 0, 0, 0);
       SDL_SetColorKey( player2->flames_moving, SDL_SRCCOLORKEY, colorkey2 );
       player2->flames_moving_interval=1;

       player2->ShipClip[0].x=0;
       player2->ShipClip[0].y=0;
       player2->ShipClip[0].w=62;
       player2->ShipClip[0].h=78;

       player2->ShipClip[1].x=63;
       player2->ShipClip[1].y=0;
       player2->ShipClip[1].w=71;
       player2->ShipClip[1].h=78;

       player2->ShipClip[2].x=135;
       player2->ShipClip[2].y=0;
       player2->ShipClip[2].w=66;
       player2->ShipClip[2].h=78;

       player2->ShipClip[3].x=202;
       player2->ShipClip[3].y=0;
       player2->ShipClip[3].w=71;
       player2->ShipClip[3].h=78;

       player2->ShipClip[4].x=273;
       player2->ShipClip[4].y=0;
       player2->ShipClip[4].w=62;
       player2->ShipClip[4].h=78;

return player2;
}











// player's update
void Player::Update(double PlayerYmin){ // see the functions below
    this->Update_DeathCheck();
    this->Update_movement(PlayerYmin);
    this->Update_EnemyBulletCrashCheck();
    this->Update_HBall_fire();
}





void Player::Update_movement(double PlayerYmin){
    if( this->y!=Screen_h-100 && this->incomming) {this->y--;  }
    else{
        incomming=false;
        //player moving horisontaly
        if(moving){
            x+=speed*dirX;
            if(x < 0 )x=0;
            else if(x+67>Screen_w) x=Screen_w-67;
        }
        //player moving verticaly
        if(moving_up){
            y-=speed*dirY;
            if(y+57>Screen_h) y=Screen_h-57;
        }
        if(y<PlayerYmin)y=PlayerYmin;
        //player moving flames animation
        flames_moving_interval++;
        if(flames_moving_interval>10) flames_moving_interval=1;


        //player main animation
        animation_index_interval++;
        if (animation_index_interval>20000){
            animation_index_interval=0;
        }
        if(moving==1){
            if(dirX<0){
                if(animation_index_interval%20==0) {
                    animation_index--;
                    if(animation_index<-2) {animation_index=-2;}
                }
            }
        else if(animation_index_interval%20==0) {
                animation_index++;
                if(animation_index>2) {animation_index=2;}
            }
        }
        if(moving==0) {
            if(animation_index<0)
                if(animation_index_interval%20==0)
                    animation_index++;
            if(animation_index>0)
                if(animation_index_interval%20==0)
                    animation_index--;

        }



    }

}

void Player::Update_EnemyBulletCrashCheck(){
    vector<Bullet*>& Benemy = Bullet::Benemy;
    vector<Bullet*>::iterator it;
    int k=0,i=0;
    if(alive && !incomming){
        while(Benemy.size() > 0 && k<Benemy.size()){
             if(Benemy[k]->x+3>=x+23 && Benemy[k]->x+3<=x+43)
                if(Benemy[k]->y+11>=y && Benemy[k]->y+11<=y+67){
                    BoomP::create_boom(Benemy[k]->x,Benemy[k]->y, 6);
                    it=Benemy.begin()+k;
                    SDL_FreeSurface(Benemy[k]->sprite);
                    delete *it;
                    Benemy.erase(Benemy.begin()+k);

                     health--;
                }
              if(Benemy[k]->x+3>=x && Benemy[k]->x+3<=x+67)
                    if(Benemy[k]->y+11>=y+20 && Benemy[k]->y+11<=y+36){
                        BoomP::create_boom(Benemy[k]->x,Benemy[k]->y, 6);
                        it=Benemy.begin()+k;
                        SDL_FreeSurface(Benemy[k]->sprite);
                        delete *it;
                        Benemy.erase(Benemy.begin()+k);
                        health--;
                    }
            k++;
        }
    }
}


void Player::Update_DeathCheck(){
    if(health<1) {
        if(alive && weapon_level>1)
        weapon_level--;
        alive=false;
    }
    /*if(!alive && lives>0){
        player->lives--;
        player->alive=true;
        player->x=(Screen_w/2)-33;
        player->y=Screen_h+20;
        player->health=10;
        player->incomming=true;
    }*/
}




void Player::Update_HBall_fire(){
    if(alive){
        HBall_interval++;
        if(HBall_interval==50){
            HBall_interval=0;
            if(HBall_level>3) HBall_level=3;
            this->Update_firePlayerHBall(HBall_level);
        }
    }
}


void Player::Update_firePlayerHBall(int h){
    if(h==1)
    {
        HBall::Create_HBall(HBall::HBplayer,"Images/HBall.bmp", this->x+26,this->y+20,-1,0 );
    }

    if(h==2)
    {
        HBall::Create_HBall(HBall::HBplayer,"Images/HBall.bmp", this->x+14,this->y+31,-0.9239,-0.3827 );
        HBall::Create_HBall(HBall::HBplayer,"Images/HBall.bmp", this->x+38,this->y+31,-0.9239,0.3827 );
    }

     if(h==3)
     {
         Update_firePlayerHBall(2);
         Update_firePlayerHBall(1);
     }
}

void Player::firePlayerBullet(int h){
    switch(h){
    case 1:
        {
            FireBullet(Bullet::Bplayer,"Images/Bulet_90.bmp",player->x+30,player->y-8,0,-1,1);
            break;
        }
    case 2:
        {
            FireBullet(Bullet::Bplayer,"Images/Bulet_90.bmp",player->x+15,player->y+15,-0.1951,-0.981,1);
            FireBullet(Bullet::Bplayer,"Images/Bulet_90.bmp",player->x+47,player->y+15,0.1951,-0.981,1);
            break;
        }
    case 3:
        {
            firePlayerBullet(1);
            firePlayerBullet(2);
            break;
        }
    case 4:
        {
            FireBullet(Bullet::Bplayer,"Images/Bulet_75_left.bmp",player->x+15,player->y+15,-0.3827,-0.9239,4);
            FireBullet(Bullet::Bplayer,"Images/Bulet_75_right.bmp",player->x+47,player->y+15,0.3827,-0.9239,2);
            firePlayerBullet(2);
            break;
        }
    case 5:
        {
            firePlayerBullet(1);
            firePlayerBullet(4);
            break;
        }
    case 6:
        {
            firePlayerBullet(4);
            FireBullet(Bullet::Bplayer,"Images/Bulet_75_left.bmp",player->x,player->y+10,-0.5556,-0.8315,4);
            FireBullet(Bullet::Bplayer,"Images/Bulet_75_right.bmp",player->x+63,player->y+10,0.5556,-0.8315,2);
            break;
        }
    case 7:
         {
             firePlayerBullet(1);
             firePlayerBullet(6);
             break;
         }
    case 8:
         {
             FireBullet(Bullet::Bplayer,"Images/Bulet_45_left.bmp",player->x,player->y+10,-0.707,-0.707,5);
             FireBullet(Bullet::Bplayer,"Images/Bulet_45_right.bmp",player->x+63,player->y+10,0.707,-0.707,3);
             firePlayerBullet(6);
             break;
         }
    case 9:
         {
             firePlayerBullet(1);
             firePlayerBullet(8);
             break;
         }
    }
}
void Player::inc_score(int value){ //increment score
    this->Player_score+=value;
    this->life_score+=value;
    if(life_score>2000){
        this->lives++;
        life_score-=2000;
    }
}



//Special BlitSurface func for the player - used by the player's Render func
void apply_surface( double x, double y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}




void Player::Render(SDL_Surface* screen){
    SDL_Rect destination;
    if(alive){
				destination.x=x;
				destination.y=y;
				if (animation_index==-2){ //blit the correct picture for the player's state
					apply_surface( destination.x, destination.y, sprite, screen, &ShipClip[ 0 ] );
				} else if (animation_index==-1){
					apply_surface( destination.x, destination.y, sprite, screen, &ShipClip[ 1 ] );
				} else if (animation_index==0){
					apply_surface( destination.x, destination.y, sprite, screen, &ShipClip[ 2 ] );
				} else if (animation_index==1){
					apply_surface( destination.x, destination.y, sprite, screen, &ShipClip[ 3 ] );
				} else if (animation_index==2){
				apply_surface( destination.x, destination.y, sprite, screen, &ShipClip[ 4 ] );
			}
            // player flame animation - the correct place for each picture of the player's state
            if(flames_moving_interval<=5){
                if(animation_index==-2){
                    destination.x=x+24;
                    destination.y=y+57;
                }
                if(animation_index==-1){
                    destination.x=x+29;
                    destination.y=y+57;
                }
                if(animation_index==0){
                    destination.x=x+28;
                    destination.y=y+57;
                }
                if(animation_index==1){
                    destination.x=x+31;
                    destination.y=y+57;
                }
                if(animation_index==2){
                    destination.x=x+29;
                    destination.y=y+57;
                }
				SDL_BlitSurface(flames_moving,0, screen, &destination);
            }
    }
}
