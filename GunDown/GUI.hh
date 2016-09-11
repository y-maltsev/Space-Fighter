void GUI::Init(){
    this->life_message = SDL_LoadBMP("Images/shipcount.bmp");
    this->bomb_message = SDL_LoadBMP("Images/bombcount.bmp");
    textColor = { 255, 255, 255 };
     MainWColor = { 255, 0, 0 };
     SecWColor = { 0, 0, 255 };
}
void GUI::Update(){

    TTF_Font *font = NULL;
    font = TTF_OpenFont( "Alexis.ttf", 30 );
    stringstream prebuffer;
    string buffer;

    prebuffer <<"Score: "<< player->Player_score;
    buffer = prebuffer.str();
    prebuffer.str("");
    score_counter = TTF_RenderText_Solid( font,buffer.c_str(), textColor);

    prebuffer << "X" << player->lives;
    buffer = prebuffer.str();
    prebuffer.str("");
    life_counter = TTF_RenderText_Solid( font,buffer.c_str(), textColor);

    prebuffer << "X" << player->Player_bombs;
    buffer = prebuffer.str();
    prebuffer.str("");
    bomb_counter = TTF_RenderText_Solid( font,buffer.c_str(), textColor);

    prebuffer << player->weapon_level;
    buffer = prebuffer.str();
    prebuffer.str("");
    mainw_level = TTF_RenderText_Solid(font,buffer.c_str(), MainWColor);

    prebuffer << player->HBall_level;
    buffer = prebuffer.str();
    prebuffer.str("");
    secw_level = TTF_RenderText_Solid(font,buffer.c_str(), SecWColor);

    TTF_CloseFont( font );

}


void GUI::Render(){
    SDL_Rect destination;

    destination.x= 0;
    destination.y = Screen_h-30;
    SDL_BlitSurface( life_message,NULL, screen, &destination );

    destination.x= 50;
    destination.y = Screen_h-30;
    SDL_BlitSurface( life_counter,NULL, screen, &destination );
    SDL_FreeSurface(life_counter);

    destination.x= 0;
    destination.y = Screen_h-60;
    SDL_BlitSurface( bomb_message,NULL, screen, &destination );

    destination.x= 50;
    destination.y = Screen_h-60;
    SDL_BlitSurface( bomb_counter,NULL, screen, &destination );
    SDL_FreeSurface(bomb_counter);

    destination.x= 0;
    destination.y = 0;
    SDL_BlitSurface( score_counter,NULL, screen, &destination );
    SDL_FreeSurface(score_counter);

    destination.x= Screen_w-30;
    destination.y = Screen_h-60;
    SDL_BlitSurface( mainw_level,NULL, screen, &destination );
    SDL_FreeSurface(mainw_level);

    destination.x=  Screen_w-30;
    destination.y = Screen_h-30;
    SDL_BlitSurface( secw_level,NULL, screen, &destination );
    SDL_FreeSurface(secw_level);
}
