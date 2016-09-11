#include <vector>
#include <iostream>
using namespace std;

bool LevelManager::Update()
{

    GamePhase* nextPhase = LevelManager::currentPhase->OnUpdate();
    if(nextPhase == NULL)
        return false;
    if(nextPhase != currentPhase)
        ChangePhase(nextPhase);
    return true;
}

void LevelManager::Render() { currentPhase->Render();}

void LevelManager::ChangePhase(GamePhase* phase)
{
    currentPhase->OnLeave();
    delete currentPhase;
    currentPhase = phase;
    currentPhase->Init();
}
