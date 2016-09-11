#include <vector>
using namespace std;

//IMPORTANT
//--------------------------------------------------------------------------------------------------------------------------------------
// All classes' function definiton is in theyr specific file - the files are pointed for each class above the declaration
// All static vectors will be ranamed everywhere for easyer use(removing theyr class name)
//--------------------------------------------------------------------------------------------------------------------------------------

//USER INTERFACE
//-------------------------------------------------------------------------------------------------------

// MainMenu.hh
struct Main_menu{
bool main_menu;
int menu_index;
SDL_Surface *message1;
SDL_Surface *message2;
SDL_Surface *message3;
SDL_Surface *Logo;
SDL_Color textColor;
SDL_Color textColor2;
TTF_Font *font;
void Init();
void Update();
void Render();

};

//GUI.hh
struct GUI{
  SDL_Color textColor;
    SDL_Color MainWColor;
    SDL_Color SecWColor ;
SDL_Surface *score_counter;
SDL_Surface *life_counter;
SDL_Surface *life_message;
SDL_Surface *bomb_counter;
SDL_Surface *bomb_message;
SDL_Surface *mainw_level;
SDL_Surface *secw_level;
void Init();
void Update();
void Render();

};

//USER INTERFACE END
//-------------------------------------------------------------------------------------------------------

struct Entity { // main propertyes for every OBJECT in the game
	SDL_Surface* sprite;
	int moving,health;
	double x,y,dirX,speed,dirY;
};

//Player.hh
struct Player: Entity {
	int moving_up,
        lives,
        weapon_level,
        HBall_level,
        HBall_interval,
        animation_index,
        animation_index_interval, //the speed that the 5 pictures will change
        flames_moving_interval,
        Player_bombs,
        Player_score,
        life_score;

	bool alive,incomming,use_mouse; // incomming - forbids actions until the players is fully "arrived"(the whole picture is on the screen)
	SDL_Surface* flames_moving;
	SDL_Rect ShipClip[5];
	Player* Init();
	void Render(SDL_Surface* screen);
	void Update(double PlaYmin);
	void Update_movement(double PlayerYmin);
	void Update_EnemyBulletCrashCheck();
    void Update_DeathCheck();
    void Update_HBall_fire(); // the calculation when a Homing Ball(HB) should be fired
    void Update_firePlayerHBall(int h); // fires HB - used by Update_HBall_fire()
    void inc_score(int value);
    void firePlayerBullet(int h);

};

// Game Phases(enemy and boss entryes,movements,extra abilityes(except the normal ones) and etc.)
// And LevelManager - see after GamePhase classes
//--------------------------------------------------------------------------------------------------------------


struct GamePhase{ // the Base class
    int starting_text_time;
    SDL_Surface* starting_text;
    virtual GamePhase* OnUpdate() =0;
    virtual void Render() =0;
    virtual void Init() =0;
    virtual void OnLeave() =0;

};


//Cassual enemy phases


// Phases.hh
struct Suicide_phase_1:GamePhase{
    int Suiciders_count;
    int Suiciders_interval;
    void Init();
    GamePhase* OnUpdate();
    void Render();
    void OnLeave();
};

struct Suicide_phase_2:GamePhase{
    int Suiciders_count;
    int Suiciders_interval;
    void Init();
    GamePhase* OnUpdate();
    void Render();
    void OnLeave();
};

struct RoyalGuardFormation:GamePhase{

    int kills; // the needed kills for the level to end
    int weave_interval;
    SDL_Surface* line; // purple line (force field that pushes the player below it) - specific for this game phase
    double line_des; // Y destination of the line
    void Init();
    GamePhase* OnUpdate();
    void Render();
    void OnLeave();
};

// Phases.hh
struct RoyalGuardPushPlayerBack: GamePhase{ //additional phase to RoyalGuardFormation (see the next struct)
     void Init();
     GamePhase* OnUpdate();
     void Render() ;
     void OnLeave() ;
};






//Boss phases

// Phases.hh
struct Boss1_Phase:GamePhase{ // Levels.hh
    void Init() ;
    GamePhase* OnUpdate();
    void Render() ;
    void OnLeave() ;

};

// LevelManager.hh
struct LevelManager
{
    static int Level;
    static GamePhase* currentPhase;
    bool Update();
    void Render();
    void ChangePhase(GamePhase* phase);
};
GamePhase* LevelManager::currentPhase;

// Enemyes and Bosses- the object's prime abilityes, impact checks with player's missles
//--------------------------------------------------------------------------------------------------------------

//Base Class
// Enemyes.hh
struct Enemy: Entity {
    static vector<Enemy*> Emanager;
    double width, height; // the size of the enemy's picture
    double Ymax; // the enemy destination (the enemy comes from over the screen to this destination)
	bool bonus_hold;
	int fire_interval;
	int score_value;

	virtual void Update(){}
	virtual void Render(){}

    static void Update_all_Enemyes();
	static void Render_all_Enemyes();
	bool destroing_Enemy(); // bool for level's end check
};






//Cassual enemyes
// Enemyes.hh
struct Royal_Guard: Enemy{

    static int enemy_fire_rate;

    static bool dirE; // all Rguards move in the same direction

    static void create_RGenemy(int pos_x, int pos_y, int Ymax_, bool bonus);
    void Update();
    void Update_fire();
    void Update_impact_player_bullets();
    void Update_impact_player_HBalls();
    void Render();
};
bool Royal_Guard::dirE=true;
int Royal_Guard::enemy_fire_rate=200;


// Enemyes.hh
struct Suicide: Enemy{
    bool exploding;
    static void create_Suicide(char* sprite_name, bool bonus);
    void Update();
    void Update_movement();
    void Update_fire();
    void Update_impact_player_bullets();
    void Update_impact_player_HBalls();
    void Render();
    void explode();
};




//Bosses.hh
struct Boss_1 : Enemy{
    int prime_weap_interval;
    SDL_Surface* Lazer; //lazer
    SDL_Surface* charge_laser; // warning picture before lazer
    int lazer_interval;
    SDL_Surface* Shields;
    int LeftShield, RightShield;
    static void Create_Boss_1();
    void Update();
    void Render();

    // those functions are used for the Update
    void bossfirebullet(); // used by Boss_1_FirePrimeWeapon
    void Update_FirePrimeWeapon();
    void Update_FireLazer();
    void Update_ImpactPlayerBullets();
    void Update_ImpactPlayerHBalls();
    void Update_LeftShield();
    void Update_RightShield();
};





//Missliles
//--------------------------------------------------------------------------------------------------------------

// Bullets.hh
struct Bullet: Entity {
    static vector<Bullet*> Bplayer;  // Player bullet container
    static vector<Bullet*> Benemy;   // Enemy bullet container
    bool faction;
	int index; //the type "boom"(see BoomP class little below) that must follow when the bullet impact its "enemy"

    static void Render_all_Bullets();
    static void Update_all_Bullets();
};



//HomingMissiles.hh
struct HBall: Entity{ // Homing ball

     static vector<HBall*> HBplayer;
     int new_HBall, target_index;
     double target_x,target_y;
     bool has_target;
     static void Create_HBall(vector<HBall*>& HBplayer,char* sprite_name, double posX,double posY,double DirX,double DirY );
     void get_target();
     static void Player_HomingBall_Update();
     static void Player_HomingBall_Render();
};


//Bomb.hh
struct Bomb:Entity{

static void Create();
static void Update();
static void Render();
static Bomb* bomb;


};



//Player Upgrade objects
//--------------------------------------------------------------------------------------------------------------
struct Bonus: Entity { // weapon upgrades
static vector<Bonus*> Bonusl;
int index; // prime/secondary/third... weapon upgrade
static void create_bonus(double x_, double y_, int index);
static void Update();
static void Render();
};








//Cosmetic objects
//--------------------------------------------------------------------------------------------------------------

//Booms.hh
struct BoomP: Entity { // picture that loads when a missle impacts with its "enemy" - boomP = boom pack (it takes care for booms from any faction)
    static vector<BoomP*> booms;     // kartinka pri udar na bulet s korab
    int duration;
    static void create_boom(double x_, double y_,int index);
    static void Update();
    static void Render();
};




//End of Game Classes
//--------------------------------------------------------------------------------------------------------------
