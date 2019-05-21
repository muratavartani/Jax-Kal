//#include <ContinuumEngine2D/ContinuumEngine2D.h>
#include <ContinuumEngine3D/Engine/ContinuumEngine.h>
#include <firebase/app.h>
#include <firebase/database.h>
#include <firebase/auth.h>
#include <firebase/future.h>
#include "Game.h"
#include <SDL/SDL.h>

int main(int argc, char* args[]) {
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	auto Width = current.w;
	auto Height = current.h;

	ContinuumEngine3D::ContinuumEngine::GetInstance()->SetGameInterface(new Game());
	//
	ContinuumEngine3D::ContinuumEngine::GetInstance()->Initialize("Continuum Engine", 1280, 720, 0);
	//
	ContinuumEngine3D::ContinuumEngine::GetInstance()->Run();

	//firebase::AppOptions appOptions = firebase::AppOptions();

	//appOptions.set_api_key("AIzaSyDQ1LtKg6yHb3Aam15gsM_ctcY67Ml7ebI");
	//appOptions.set_app_id("1:233010284521:ios:736284f2073f7d66");
	//appOptions.set_database_url("https://companionapp-314bc.firebaseio.com");
	//appOptions.set_project_id("companionapp-314bc");
	//appOptions.set_storage_bucket("companionapp-314bc.appspot.com");
	//appOptions.set_messaging_sender_id("233010284521");


	//appOptions.LoadFromJsonConfig("C:\\Users\\Khoi Vu\\source\\repos\\Project4\\google-services-desktop.json");

	/*firebase::App* app = firebase::App::Create(appOptions);
	firebase::database::Database *database = firebase::database::Database::GetInstance(app);*/
	//firebase::database::DatabaseReference dbref = database->GetReference();
	//firebase::database::DatabaseReference dbref = database->GetReference("companionapp-314bc");
	////dbref.Child("score").Child("Khoi").SetValue("1000");
	//firebase::Future<firebase::database::DataSnapshot> result = dbref.GetReference().Child("score").Child("Khoi").GetValue();

	//bool check = false;

	//while (!check)
	//{
	//	if (result.status() != firebase::kFutureStatusPending) {
	//		if (result.status() != firebase::kFutureStatusComplete) {
	//			printf("ERROR: GetValue() returned an invalid result.");
	//			// Handle the error...
	//		}
	//		else if (result.error() != firebase::database::kErrorNone) {
	//			printf("ERROR: GetValue() returned error %d: %s", result.error(),
	//				result.error_message());
	//			// Handle the error...
	//		}
	//		else {
	//			firebase::database::DataSnapshot snapshot = *result.result();
	//			printf("HAHAHHAHAHAHAHA\n");
	//			printf(snapshot.key());
	//			// Do something with the snapshot...
	//			check = true;
	//		}
	//	}
	//}

	return 0;
}