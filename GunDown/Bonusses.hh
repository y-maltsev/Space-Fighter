




void Bonus::create_bonus(double x_, double y_, int index)
{
    if(index==4) index=2;  // 3 primary weapon bonnusses to 1 secondary weapon bonus
    else index=1;          // index 2 = secondary weapon, index 1 = primary weapon bonus
    if(Bonusl.size()<9){
    Bonus* bonus = new Bonus;
	if(index==1)
	bonus->sprite=SDL_LoadBMP("Images/weapon.bmp");
	else bonus->sprite=SDL_LoadBMP("Images/weapon2.bmp");
	bonus->speed=0.5;
	bonus->x=x_;
	bonus->y =y_;
	bonus->index=index;
	bonus->dirY =1;
	bonus->dirX=0;
	Bonusl.push_back(bonus);
    }
}






void bonus_Update(int i);// update for 1 bonus - used by Bonus::Update

void Bonus::Update(){
    for(int i=0;i<Bonus::Bonusl.size();i++){
        bonus_Update(i);
    }
}






void bonus_Update(int i){// move the bonussses
                         // check 4 points of the bonus with number "i" are in the player's 2 "impact" parts ( 8 almost same checks).
                         // If yes increase weapon level by the index of the bonus, destroy the bonus.
                         // Check is the bonus below the screen. if yes destroy the bonus.

    bool get=true;
    vector<Bonus*>& Bonusl = Bonus::Bonusl;
    vector<Bonus*>::iterator itb;
    Bonusl[i]->y+=Bonusl[i]->speed*Bonusl[i]->dirY;

    if(Bonusl[i]->y>=Screen_h){
        itb=Bonusl.begin()+i;
        SDL_FreeSurface(Bonusl[i]->sprite);
        delete *itb;
        Bonusl.erase(Bonusl.begin()+i);
        return;
    }

    if(get)
    if(Bonusl[i]->x>=player->x && Bonusl[i]->x<=player->x+67)
                if(Bonusl[i]->y>=player->y+20 && Bonusl[i]->y<=player->y+36){

                if(Bonusl[i]->index==1)
                player->weapon_level++;
                else player->HBall_level++;

                itb=Bonusl.begin()+i;
                SDL_FreeSurface(Bonusl[i]->sprite);
                delete *itb;
                Bonusl.erase(Bonusl.begin()+i);
                get=false;
            }
    if(get)
     if(Bonusl[i]->x+30>=player->x && Bonusl[i]->x+30<=player->x+67)
            if(Bonusl[i]->y>=player->y+20 && Bonusl[i]->y<=player->y+36){

                if(Bonusl[i]->index==1)
                player->weapon_level++;
                else player->HBall_level++;

                itb=Bonusl.begin()+i;
                SDL_FreeSurface(Bonusl[i]->sprite);
                delete *itb;
                Bonusl.erase(Bonusl.begin()+i);

                get=false;
            }
    if(get)
     if(Bonusl[i]->x>=player->x && Bonusl[i]->x<=player->x+67)
                if(Bonusl[i]->y+30>=player->y+20 && Bonusl[i]->y+30<=player->y+36){

                if(Bonusl[i]->index==1)
                player->weapon_level++;
                else player->HBall_level++;

                itb=Bonusl.begin()+i;
                SDL_FreeSurface(Bonusl[i]->sprite);
                delete *itb;
                Bonusl.erase(Bonusl.begin()+i);

                get=false;
            }
    if(get)
     if(Bonusl[i]->x+30>=player->x && Bonusl[i]->x+30<=player->x+67)
                if(Bonusl[i]->y+30>=player->y+20 && Bonusl[i]->y+30<=player->y+36){

                if(Bonusl[i]->index==1)
                player->weapon_level++;
                else player->HBall_level++;

                itb=Bonusl.begin()+i;
                SDL_FreeSurface(Bonusl[i]->sprite);
                delete *itb;
                Bonusl.erase(Bonusl.begin()+i);

                get=false;
            }

    if(get)
       if(Bonusl[i]->x>=player->x && Bonusl[i]->x<=player->x+67)
            if(Bonusl[i]->y>=player->y && Bonusl[i]->y<=player->y+83){

                if(Bonusl[i]->index==1)
                player->weapon_level++;
                else player->HBall_level++;

                itb=Bonusl.begin()+i;
                SDL_FreeSurface(Bonusl[i]->sprite);
                delete *itb;
                Bonusl.erase(Bonusl.begin()+i);

                get=false;
            }
    if(get)
     if(Bonusl[i]->x+25>=player->x && Bonusl[i]->x+25<=player->x+67)
            if(Bonusl[i]->y>=player->y && Bonusl[i]->y<=player->y+83){

                if(Bonusl[i]->index==1)
                player->weapon_level++;
                else player->HBall_level++;

                itb=Bonusl.begin()+i;
                SDL_FreeSurface(Bonusl[i]->sprite);
                delete *itb;
                Bonusl.erase(Bonusl.begin()+i);

                get=false;
            }
    if(get)
     if(Bonusl[i]->x>=player->x && Bonusl[i]->x<=player->x+67)
            if(Bonusl[i]->y+25>=player->y && Bonusl[i]->y+25<=player->y+83){

                if(Bonusl[i]->index==1)
                player->weapon_level++;
                else player->HBall_level++;

                itb=Bonusl.begin()+i;
                SDL_FreeSurface(Bonusl[i]->sprite);
                delete *itb;
                Bonusl.erase(Bonusl.begin()+i);

                get=false;
            }
    if(get)
     if(Bonusl[i]->x+25>=player->x && Bonusl[i]->x+25<=player->x+67)
            if(Bonusl[i]->y+25>=player->y && Bonusl[i]->y+25<=player->y+83){

                if(Bonusl[i]->index==1)
                player->weapon_level++;
                else player->HBall_level++;

                itb=Bonusl.begin()+i;
                SDL_FreeSurface(Bonusl[i]->sprite);
                delete *itb;
                Bonusl.erase(Bonusl.begin()+i);

                get=false;
            }


}






void Bonus::Render(){
    SDL_Rect destination;
    for(int i=0;i!=Bonus::Bonusl.size();i++){
        destination.x=Bonus::Bonusl[i]->x;
        destination.y=Bonus::Bonusl[i]->y;
        SDL_BlitSurface(Bonus::Bonusl[i]->sprite,0, screen, &destination);
    }
}



