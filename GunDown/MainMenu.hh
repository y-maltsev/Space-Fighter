#include<sstream>

void Main_menu::Init(){
    main_menu=true;
    menu_index=1;
    Logo=SDL_LoadBMP("Images/logo.bmp");
    textColor = { 0, 255,0 };
    textColor2= { 255, 255, 0};
    font = NULL;
    if( TTF_Init() == -1 )
    {
           return;
    }
    font = TTF_OpenFont( "Alexis.ttf", 56 );

}
void Main_menu::Update(){

    switch(menu_index){
        case 1:
        {
            message1=TTF_RenderText_Solid( font,"Resume",textColor2);
            message2=TTF_RenderText_Solid( font,"New Game",textColor);
            message3=TTF_RenderText_Solid( font,"Exit",textColor);
            break;
        }
        case 2:
        {
            message1=TTF_RenderText_Solid( font,"Resume",textColor);
            message2=TTF_RenderText_Solid( font,"New Game",textColor2);
            message3=TTF_RenderText_Solid( font,"Exit",textColor);
            break;
        }
        case 3:
        {
            message1=TTF_RenderText_Solid( font,"Resume",textColor);
            message2=TTF_RenderText_Solid( font,"New Game",textColor);
            message3=TTF_RenderText_Solid( font,"Exit",textColor2);
            break;
        }
        default:
        {
            menu_index=1;
            break;
        }
    }
}

void Main_menu::Render(){
SDL_Rect destination;
destination.x= Screen_w/2-145;
destination.y = 100;
SDL_BlitSurface( Logo,NULL, screen, &destination );
destination.x= Screen_w/2-120;
destination.y = Screen_h/2-175;
SDL_BlitSurface( message1,NULL, screen, &destination );
SDL_FreeSurface(message1);
destination.x= Screen_w/2-150;
destination.y = Screen_h/2-75;
SDL_BlitSurface( message2,NULL, screen, &destination );
SDL_FreeSurface(message2);
destination.x= Screen_w/2-64;
destination.y = Screen_h/2+25;
SDL_BlitSurface( message3,NULL, screen, &destination );
SDL_FreeSurface(message3);
}
