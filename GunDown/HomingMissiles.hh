


void HBall::Create_HBall(vector<HBall*>& HBplayer,char* sprite_name, double posX,double posY,double DirX,double DirY ){
    HBall* hball = new HBall;
	hball->sprite=SDL_LoadBMP(sprite_name);
	Uint32 colorkey2 = SDL_MapRGB(hball->sprite->format,0,0,0);
    SDL_SetColorKey( hball->sprite, SDL_SRCCOLORKEY, colorkey2 );
	hball->speed=9;
	hball->x = posX;
	hball->y = posY;
	hball->dirY =DirX;
	hball->dirX=DirY;
	hball->new_HBall=0;
	hball->has_target=false;
	HBplayer.push_back(hball);
}

// UPDATE
//------------------------------------------------------------


//functions for the update - see definition below the update
void HBalls_move();
void HBalls_calculate_movement();

//the update itself
void HBall::Player_HomingBall_Update(){
    HBalls_calculate_movement();
    HBalls_move();
}




void HBalls_move(){
    vector<HBall*>& HBplayer = HBall::HBplayer;
    for(int i=0;i!=HBplayer.size();i++){
        HBplayer[i]->y+=HBplayer[i]->speed*HBplayer[i]->dirY;
        HBplayer[i]->x+=HBplayer[i]->dirX*HBplayer[i]->speed;
    }
}




void get_target(HBall* hball); //helpful function for HBalls_calculate movement

void HBalls_calculate_movement(){

    vector<HBall*>& HBplayer = HBall::HBplayer; // removing the class name for easyer use
    vector<Enemy*>& Emanager = Enemy::Emanager;

    for(int i=0;i!=HBplayer.size();i++){
        if(Emanager.size()!=0){
        if(!HBplayer[i]->has_target){
                get_target(HBplayer[i]); // see defininition after Hballs_calculate_movement
            }

        if(HBplayer[i]->new_HBall >15){

                bool left_move=false,down_move=false;
                if(Emanager[HBplayer[i]->target_index]->x+((Emanager[HBplayer[i]->target_index]->width/ 2) - 7) < HBplayer[i]->x) left_move=true;
                if(Emanager[HBplayer[i]->target_index]->y+((Emanager[HBplayer[i]->target_index]->height/ 2) - 7) > HBplayer[i]->y) down_move=true;
                double
                DirX,
                DirY,
                X_targ=HBplayer[i]->target_x+((Emanager[HBplayer[i]->target_index]->width / 2) - 7) - HBplayer[i]->x,
                Y_targ=HBplayer[i]->target_y+((Emanager[HBplayer[i]->target_index]->height / 2) - 7) - HBplayer[i]->y;

                if(Y_targ<0) Y_targ=-Y_targ;
                if(X_targ<0) X_targ=-X_targ;
                DirX=X_targ/sqrt(X_targ*X_targ+Y_targ*Y_targ);
                DirY=Y_targ/sqrt(X_targ*X_targ+Y_targ*Y_targ);
                if(left_move) DirX=-DirX;
                if(!down_move) DirY=-DirY;
                if (DirX < HBplayer[i]->dirX) {HBplayer[i]->dirX-=0.06;}
                if (DirX > HBplayer[i]->dirX) {HBplayer[i]->dirX+=0.06;}
                if (DirY < HBplayer[i]->dirY) {HBplayer[i]->dirY-=0.06;}
                if (DirY > HBplayer[i]->dirY) {HBplayer[i]->dirY+=0.06;}

        }
        else {HBplayer[i]->new_HBall++;}
        }
    }
}



void get_target(HBall* hball){
double target=100000;
    vector<Enemy*> Emanager = Enemy::Emanager;
    for(int k=0;k<Emanager.size();k++){
            double target_now=0;
            double target_center_Y=(Emanager[k]->height / 2 - 7);
            double target_center_X=(Emanager[k]->width / 2 - 7);

            if(Emanager[k]->x+target_center_X < hball->x)
                target_now += hball->x - Emanager[k]->x+target_center_X;
            else target_now += Emanager[k]->x+target_center_X - hball->x;

            if(Emanager[k]->y+target_center_Y < hball->y)
                target_now +=  hball->y - Emanager[k]->y+target_center_Y;
            else target_now += Emanager[k]->y+target_center_Y -  hball->y  ;

            if(target>target_now) {
                target=target_now;
                hball->target_x=Emanager[k]->x+34;
                hball->target_y=Emanager[k]->y+21;
                hball->target_index=k;
                hball->has_target=true;
            }
    }
}

//end of Homing Ball update
//-----------------------------------------------------------------

void HBall::Player_HomingBall_Render(){
        SDL_Rect destination;
    for(int i=0;i!=HBall::HBplayer.size();i++){
        destination.x=HBall::HBplayer[i]->x;
        destination.y=HBall::HBplayer[i]->y;
        destination.w=14;
        destination.h=14;
        SDL_BlitSurface(HBall::HBplayer[i]->sprite,0, screen, &destination);
    }
}







