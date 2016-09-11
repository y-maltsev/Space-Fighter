#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <vector>
#include <Cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Cstdlib>
#include <Windows.h>
using namespace std;
#include "GameClasses.hh"// a file containing all classes in the game
#include "GlobalVariables.hh"
#include "EventHandler.hh"
#include "MainMenu.hh"
#include "Bullets.hh"
#include "Booms.hh"
#include "HomingMissiles.hh"
#include "Bonusses.hh"
#include "Player.hh"
#include "Enemyes.hh"
#include "Bosses.hh"
#include "LevelManager.hh"
#include "GUI.hh"
#include "Phases.hh"
#include "Bomb.hh"
#undef main





void init(){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	screen = SDL_SetVideoMode(Screen_w, Screen_h, 24,SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	SDL_WM_SetCaption("PlaneFight","PEW PEW");
	intro_pic=SDL_LoadBMP("Images/Imena.bmp");
    bg1=SDL_LoadBMP("Images/SP.bmp");
    bg2=SDL_LoadBMP("Images/SP.bmp");
	player = player->Init();


    Mmenu = new Main_menu();
    Mmenu->Init();
    gui2 = new GUI();
	gui2->Init();

    Suicide_phase_1* ra = new Suicide_phase_1();
    ra->Init();
    GamePhase* a = ra;
    LevelManager::currentPhase = a;
}


void render(){
		SDL_FillRect(screen, 0, 0);
		SDL_Rect destination;

    if(intro==900){
        if(!Mmenu->main_menu){
			//backgrounds
			destination.x=0;
			destination.y=bgY1;
			SDL_BlitSurface(bg1,0, screen, &destination);
			destination.x=0;
			destination.y=bgY2;
			SDL_BlitSurface(bg2,0, screen, &destination);
			destination.x=0;

            //render everything else
			LManager.Render();

        }
        else{
        Mmenu->Update();
        Mmenu->Render();
        }
    }
    else{
        destination.x=0;
        destination.y=0;
        SDL_BlitSurface(intro_pic,0, screen, &destination);
        if(intro==899) SDL_FreeSurface(intro_pic);
    }
    SDL_Flip(screen);
}


void Main_Update(){
    if(intro==900){
        if(!Mmenu->main_menu){
            //moving background
            bgY1+=0.4;
            bgY2+=0.4;
            if(bgY1>=Screen_h)bgY1=-Screen_h;
            if(bgY2>=Screen_h)bgY2=-Screen_h;
            //the rest update
            LManager.Update();
        }
    }else{
        intro++;
        if(intro==300){
            SDL_FreeSurface(intro_pic);
            intro_pic=SDL_LoadBMP("Images/Presents.bmp");
        }
        if(intro==600)
        {
            SDL_FreeSurface(intro_pic);
            intro_pic=SDL_LoadBMP("Images/MainTheme.bmp");
        }
    }
}



const int FPS = 100;
const DWORD TIME_PER_FRAME = 1000 / FPS;
const float FRACTION_TIME_PER_FRAME = (float)TIME_PER_FRAME / 1000.0f;

void run(){
DWORD lastTime= GetTickCount();
SDL_Event event;
srand ( time(NULL) );
	while(1){
        DWORD currentTime = GetTickCount();
        if(intro==900)
		if(SDL_PollEvent(&event)){
            if(!EventHandler(event)) break;

		}
			while( currentTime - lastTime >= TIME_PER_FRAME)
        {
            Main_Update();
            lastTime += TIME_PER_FRAME;

        }
          render();
	}
}

void destroy(){
SDL_FreeSurface(gui2->life_message);
SDL_FreeSurface(gui2->bomb_message);
SDL_Quit();
}

int main(int argc, char *argv[]){
srand ( time(NULL) );

init();
run();
destroy();

return 0;
}

