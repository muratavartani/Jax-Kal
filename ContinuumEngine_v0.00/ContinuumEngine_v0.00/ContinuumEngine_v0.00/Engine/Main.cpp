#include "ContinuumEngine.h"
#include "../Game/Game.h"


int main(int argc, char* args[]) {

	ContinuumEngine::GetInstance()->SetGameInterface(new Game());
	////VERSION 1
	//if (!ClassEngine::GetInstance()->Initialize("GAM301 Engine", 800, 600)) {
	//	std::cout << "Engine failed to initialize" << std::endl;
	//	return 0;
	//}

	//VERSION 2
	ContinuumEngine::GetInstance()->Initialize("Continuum Engine", 800, 600);

	ContinuumEngine::GetInstance()->Run();


	return 0;
}