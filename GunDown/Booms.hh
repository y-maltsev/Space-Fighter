
void BoomP::create_boom(double x_, double y_,int index){
    int icX,icY; //indexChange missle's boom X and Y
    BoomP* boom = new BoomP;
    boom->sprite= SDL_LoadBMP("Images/BoomSmall.bmp");
    Uint32 colorkey = SDL_MapRGB( boom->sprite->format, 0, 0, 0);
	SDL_SetColorKey( boom->sprite, SDL_SRCCOLORKEY, colorkey );
    switch(index){ //create boom by the type missle (1-5 player bullets , 6 is enemy bullets , 8 player Homing ball)
        case 1:
            icX=2;
            icY=-7;
            break;
        case 2:
            icX=7;
            icY=-7;
            break;
        case 3:
            icX=19;
            icY=-7;
            break;
        case 4:
            icX=-7;
            icY=-7;
            break;
        case 5:
            icX=-7;
            icY=-7;
            break;
        case 6:
            icX=2;
            icY=14;
            break;
       /* case 7:
            icX=2;
            icY=0;
            boom->sprite= SDL_LoadBMP("Images/BoomCrash.bmp");  - currently unused - no enemy bullet and player bullet impact*/
            break;
        case 8:
            icX=-7;
            icY=-7;
            break;
    }
	boom->x=x_+icX;
	boom->y=y_+icY;
    boom->duration=0;
	BoomP::booms.push_back(boom);
}

void BoomP::Update(){
    vector<BoomP*>::iterator itboom;
    for(int i=0;i<BoomP::booms.size();i++){
         BoomP::booms[i]->duration++;
         if(BoomP::booms[i]->duration==15){
            itboom = BoomP::booms.begin()+i;
            SDL_FreeSurface(BoomP::booms[i]->sprite);
            delete *itboom;
            BoomP::booms.erase(BoomP::booms.begin()+i);
         }
     }
}

void BoomP::Render(){

    SDL_Rect destination;
    for(int i=0;i!=BoomP::booms.size();i++){
        destination.x=BoomP::booms[i]->x;
        destination.y=BoomP::booms[i]->y;
        destination.w=14;
        destination.h=14;
        SDL_BlitSurface(BoomP::booms[i]->sprite,0, screen, &destination);

    }
}
