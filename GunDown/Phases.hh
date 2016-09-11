#include <vector>
using namespace std;



//Suicides1 Formation  Functions start
//--------------------------------------------------------------------------------------------------------------------


void Suicide_phase_1::Init(){
    Suiciders_count=100*LevelManager::Level;
    Suiciders_interval=0;
    starting_text_time=0;

}

GamePhase* Suicide_phase_1::OnUpdate(){



    if(starting_text_time<400) {starting_text_time++;
        SDL_Color textColor = { 124, 255, 255 };
        TTF_Font *font = NULL;
        font = TTF_OpenFont( "Alexis.ttf", 50 );
        stringstream prebuffer;
        string buffer;

        prebuffer <<"Level "<< LevelManager::Level<<": Bombarders!!!";
        buffer = prebuffer.str();
        prebuffer.str("");
        starting_text = TTF_RenderText_Solid(font,buffer.c_str(), textColor);
    }



    if(Bomb::bomb!=NULL) Bomb::Update();
    player->Update(0);
    Bonus::Update();
    Bullet::Update_all_Bullets();
    HBall::Player_HomingBall_Update();
    Enemy::Update_all_Enemyes();
    BoomP::Update();
    if(starting_text_time==400){
        Suiciders_interval++;
        if(Suiciders_count>0 && Suiciders_interval%25==0)
        {
            bool bonusss;
            if(rand()%2+1 == 1) bonusss=true;
            Suicide::create_Suicide("Images/BSuicide.bmp",bonusss);
            Suiciders_count--;
        }
    }
    for(int i=0;i<Enemy::Emanager.size();i++){
        Enemy::Emanager[i]->destroing_Enemy();
    }
    gui2->Update();
    if(Suiciders_count==0 && Enemy::Emanager.size()==0){
        Suicide_phase_2* ret = new Suicide_phase_2();
        return ret;
    }
    else return this;

}

void Suicide_phase_1::Render(){
    player->Render(screen);
    Bullet::Render_all_Bullets();
    Bonus::Render();
    HBall::Player_HomingBall_Render();
    Enemy::Render_all_Enemyes();
    BoomP::Render();
   if(Bomb::bomb!=NULL) Bomb::Render();
   gui2->Render();
   if(starting_text_time<400 && starting_text_time>100){
    SDL_Rect destination;
    destination.x= 500;
    destination.y = 400;
    SDL_BlitSurface( starting_text, NULL, screen, &destination );
   }
}

void Suicide_phase_1::OnLeave(){}






//Suicides1 Formation  Functions end
//--------------------------------------------------------------------------------------------------------------------



//Suicides2 Formation  Functions start
//--------------------------------------------------------------------------------------------------------------------



void Suicide_phase_2::Init(){
Suiciders_count=150*LevelManager::Level;
Suiciders_interval=0;
starting_text_time=0;
}

GamePhase* Suicide_phase_2::OnUpdate(){

    if(starting_text_time<400) {starting_text_time++;
        SDL_Color textColor = { 124, 255, 255 };
        TTF_Font *font = NULL;
        font = TTF_OpenFont( "Alexis.ttf", 50 );
        stringstream prebuffer;
        string buffer;

        prebuffer <<"Level "<< LevelManager::Level<<": Suiciders!!!";
        buffer = prebuffer.str();
        prebuffer.str("");
        starting_text = TTF_RenderText_Solid(font,buffer.c_str(), textColor);
    }


   if(Bomb::bomb!=NULL) Bomb::Update();
    player->Update(0);
    Bonus::Update();
    Bullet::Update_all_Bullets();
    HBall::Player_HomingBall_Update();
    BoomP::Update();
    if(starting_text_time==400){
        Suiciders_interval++;
        if(Suiciders_interval==9001) Suiciders_interval=0;
        if(Suiciders_count>0 && Suiciders_interval%(25/LevelManager::Level)==0)
        {
            bool bonusss;
            if(rand()%2+1 == 1) bonusss=true;
            Suicide::create_Suicide("Images/PSuicide.bmp",bonusss);
            Suiciders_count--;
        }
         for(int i=0;i<Enemy::Emanager.size();i++){
            Enemy::Emanager[i]->destroing_Enemy();
        }
        Enemy::Update_all_Enemyes();
    }
    gui2->Update();
    if(Suiciders_count==0 && Enemy::Emanager.size()==0){
        RoyalGuardFormation* ret = new RoyalGuardFormation();
        return ret;
    }
    else return this;

}

void Suicide_phase_2::Render(){
    player->Render(screen);
    Bullet::Render_all_Bullets();
    Bonus::Render();
    HBall::Player_HomingBall_Render();
    Enemy::Render_all_Enemyes();
    BoomP::Render();
   if(Bomb::bomb!=NULL) Bomb::Render();
   gui2->Render();
   if(starting_text_time<400 && starting_text_time>100){
    SDL_Rect destination;
    destination.x= 500;
    destination.y = 400;
    SDL_BlitSurface( starting_text, NULL, screen, &destination );
   }
}

void Suicide_phase_2::OnLeave(){}












//Suicides2 Formation  Functions end
//--------------------------------------------------------------------------------------------------------------------



//Royal Guard Formation  Functions start
//--------------------------------------------------------------------------------------------------------------------
void RoyalGuardFormation::Init(){
    this->kills=1;
    this->weave_interval=0;
    this->line_des=0;
    this->line=SDL_LoadBMP("Images/line.bmp");
    int x_,
        y_=-252,
        Ymax_=0;
    bool bonus;
    int random;
        for(int i=1;i<=3;i++){
            x_=67;
            for(int k=1;k<=(Screen_w-170)/90;k++){
                random==rand()%5+1;
                if(random==5) bonus=true;
                Royal_Guard::create_RGenemy(x_,y_,Ymax_,bonus);
                bonus=false;
                x_+=90;
            }
            y_+=84;
            Ymax_+=84;
        }
    starting_text_time=0;
}






void RoyalGuardFormation_newline(); //used by OnUpdate - spawns new line of Royal Guards - see definiton below the OnUpdate

GamePhase* RoyalGuardFormation::OnUpdate(){

    if(starting_text_time<400) {starting_text_time++;
        SDL_Color textColor = { 124, 255, 255 };
        TTF_Font *font = NULL;
        font = TTF_OpenFont( "Alexis.ttf", 50 );
        stringstream prebuffer;
        string buffer;

        prebuffer <<"Level "<< LevelManager::Level<<": Royal Guards!";
        buffer = prebuffer.str();
        prebuffer.str("");
        starting_text = TTF_RenderText_Solid(font,buffer.c_str(), textColor);
    }

   if(Bomb::bomb!=NULL) Bomb::Update();
    player->Update(line_des);
    Bonus::Update();
    Bullet::Update_all_Bullets();
    HBall::Player_HomingBall_Update();

    BoomP::Update();
    vector<Enemy*>& Emanager = Enemy::Emanager; // renaming for easyer use

     // all royal guards move specificly for the level
    if(starting_text_time==400){
        for(int i=0;i<Emanager.size();i++){
            Emanager[i]->x+=Emanager[i]->dirX*Emanager[i]->speed;
            if(Emanager[i]->x+83>=Screen_w) Royal_Guard::dirE=false;
            else if(Emanager[i]->x<=0) Royal_Guard::dirE=true;
            if(Royal_Guard::dirE)Emanager[i]->dirX=0.05;
            else Emanager[i]->dirX=-0.05;
            if(Emanager[i]->y!=Emanager[i]->Ymax) Emanager[i]->y+=0.5;
            if(Emanager[i]->y>=Screen_h-80) {

                RoyalGuardPushPlayerBack* ret = new RoyalGuardPushPlayerBack();
                return ret;
            }
        }
        //calculate purple line Y position
        double Y_line = 0;
        for(int i=0;i!=Emanager.size();i++){
            if(Y_line < Emanager[i]->y+Emanager[i]->height+12)
            Y_line = Emanager[i]->y+Emanager[i]->height+12;
        }
        if(line_des < Y_line) line_des+=1;
        else if(line_des > Y_line) line_des-=1;

        // spawn new line of royal guards every N seconds(depending on the level)
        if(kills>0) {
            this->weave_interval++;
            if(weave_interval== 100001) weave_interval=0;
            if(weave_interval%(500/LevelManager::Level)==0)
            RoyalGuardFormation_newline();
        }

         Enemy::Update_all_Enemyes();

        // check for player killing blows
        for(int i=0;i<Emanager.size();i++){
            if(Emanager[i]->destroing_Enemy()) {kills--; i--;}
        }
    }
    // check is the level's phase is still operation or finished and if it is finished call next phase
    gui2->Update();
    if(kills>0 || Emanager.size() > 0)
    return this;
    else{
        Boss1_Phase* ret = new Boss1_Phase();
         return ret;
    }
}





void RoyalGuardFormation_newline(){
    bool bonus=false;
    int x_=67;
    for(int i=0;i<Enemy::Emanager.size();i++){
        Enemy::Emanager[i]->Ymax+=84;
    }
    for(int k=1;k<=(Screen_w-170)/90;k++){
            int random=rand()%10+1;
            if(random==10)bonus=true;
			Royal_Guard::create_RGenemy(x_,-84,0,bonus);
			x_+=90;
			bonus=false;
    }
}






 void RoyalGuardFormation::Render(){

    player->Render(screen);
    Bullet::Render_all_Bullets();
    Bonus::Render();
    HBall::Player_HomingBall_Render();
    Enemy::Render_all_Enemyes();
    BoomP::Render();
    SDL_Rect destination;
    destination.x=0;
    destination.y=line_des;
    SDL_BlitSurface(this->line,0, screen, &destination);
   if(Bomb::bomb!=NULL) Bomb::Render();
   gui2->Render();
   if(starting_text_time<400 && starting_text_time>100){
    SDL_Rect destination;
    destination.x= 500;
    destination.y = 400;
    SDL_BlitSurface( starting_text, NULL, screen, &destination );
   }
 }



 void RoyalGuardFormation::OnLeave(){
    SDL_FreeSurface(line);
}
//Royal Guard Formation function definiton end
//-------------------------------------------------------------------------------------------------------------


//Royal Guard Push Back function definiton start
//-------------------------------------------------------------------------------------------------------------

void RoyalGuardPushPlayerBack::Init(){}
GamePhase* RoyalGuardPushPlayerBack::OnUpdate(){
    vector<Enemy*>& Emanager = Enemy::Emanager;
    vector<Enemy*>::iterator ite;
      player->alive=false;
        for(int i=0;i!=Emanager.size();i++){
			if(Emanager[i]->y>=Screen_h) {
                ite=Emanager.begin()+i;
                SDL_FreeSurface(Emanager[i]->sprite);
                delete *ite;
                Emanager.erase(Emanager.begin()+i);
                i--;
			}
			else Emanager[i]->y+=2;
        }

        while(Bonus::Bonusl.size() > 0 ) {
            vector<Bonus*>::iterator itb = Bonus::Bonusl.begin();
            SDL_FreeSurface(Bonus::Bonusl[0]->sprite);
            delete *itb;
            Bonus::Bonusl.erase(Bonus::Bonusl.begin());
        }

        while(BoomP::booms.size()>0){
            vector<BoomP*>::iterator itboom = BoomP::booms.begin();
            SDL_FreeSurface(BoomP::booms[0]->sprite);
            delete *itboom;
            BoomP::booms.erase(BoomP::booms.begin());
        }

         while(Bullet::Bplayer.size()>0){
            vector<Bullet*>::iterator it = Bullet::Bplayer.begin();
            SDL_FreeSurface(Bullet::Bplayer[0]->sprite);
            delete *it;
            Bullet::Bplayer.erase(Bullet::Bplayer.begin());
        }

        while(Bullet::Benemy.size()>0){
            vector<Bullet*>::iterator it = Bullet::Benemy.begin();
            SDL_FreeSurface(Bullet::Benemy[0]->sprite);
            delete *it;
            Bullet::Benemy.erase(Bullet::Benemy.begin());
        }
        while(HBall::HBplayer.size()>0){
            vector<HBall*>::iterator it = HBall::HBplayer.begin();
            SDL_FreeSurface(HBall::HBplayer[0]->sprite);
            delete *it;
            HBall::HBplayer.erase(HBall::HBplayer.begin());
        }


        //release the mode(restart the level)
        if(Emanager.size()==0){
            player->alive=true;
            player->health=10;
            player->x=(Screen_w/2)-33;
            player->y=Screen_h+20;
            player->incomming=true;;
            player->moving=false;
            Suicide_phase_1* ret = new Suicide_phase_1();
            return ret;
        }
        else return this;

}

void RoyalGuardPushPlayerBack::Render(){
        Enemy::Render_all_Enemyes();
        gui2->Render();
}
void RoyalGuardPushPlayerBack::OnLeave(){}





//Royal Guard Push Back function definiton end
//-------------------------------------------------------------------------------------------------------------


//Boss1_phase function definiton start
//-------------------------------------------------------------------------------------------------------------




     void Boss1_Phase::Init(){
     Boss_1::Create_Boss_1();
     starting_text_time=0;
     }




     GamePhase* Boss1_Phase::OnUpdate(){
         if(starting_text_time<400) {starting_text_time++;
                SDL_Color textColor = { 124, 255, 255 };
                TTF_Font *font = NULL;
                font = TTF_OpenFont( "Alexis.ttf", 50 );
                stringstream prebuffer;
                string buffer;

                prebuffer <<"Level "<< LevelManager::Level<<": Boss!!!";
                buffer = prebuffer.str();
                prebuffer.str("");
                starting_text = TTF_RenderText_Solid(font,buffer.c_str(), textColor);
        }
        vector<Enemy*>& Emanager = Enemy::Emanager;
        player->Update(0);
        Bonus::Update();
        Bullet::Update_all_Bullets();
        HBall::Player_HomingBall_Update();
        BoomP::Update();
        if(starting_text_time==400){
        Emanager[0]->x+=Emanager[0]->dirX*Emanager[0]->speed;
        if(Emanager[0]->x+137>=Screen_w) Emanager[0]->dirX=-0.1;
        if(Emanager[0]->x<=0) Emanager[0]->dirX=0.1;
        Enemy::Update_all_Enemyes();
        }

        gui2->Update();
        if(Emanager[0]->destroing_Enemy()) {
            while(Bullet::Benemy.size()>0){
                vector<Bullet*>::iterator it = Bullet::Benemy.begin();
                SDL_FreeSurface(Bullet::Benemy[0]->sprite);
                delete *it;
                Bullet::Benemy.erase(Bullet::Benemy.begin());
            }
            LevelManager::Level++;
            Suicide_phase_1* ret = new Suicide_phase_1();
            return ret;
        }
        else return this;
     }



     void Boss1_Phase::Render(){
        player->Render(screen);
        Bullet::Render_all_Bullets();
        Bonus::Render();
        HBall::Player_HomingBall_Render();
        Enemy::Render_all_Enemyes();
        BoomP::Render();
        gui2->Render();
        if(starting_text_time<400 && starting_text_time>100){
            SDL_Rect destination;
            destination.x= 600;
            destination.y = 400;
            SDL_BlitSurface( starting_text, NULL, screen, &destination );
       }
     }





     void Boss1_Phase::OnLeave(){

     }





//Boss1_phase function definiton end
//-------------------------------------------------------------------------------------------------------------








