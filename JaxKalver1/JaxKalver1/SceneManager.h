#pragma once
#include <memory>
#include <thread>
#include "Window.h"
#include "Scene.h"

namespace JAX {

	class SceneManager {
	private:
		SceneManager();
		~SceneManager();

		Window windowInstance;
		Scene *currentScene;
		///std::unique_ptr is a smart pointer that destroys the object it points to when the unique_ptr goes out of scope.
		static std::unique_ptr<SceneManager> instance;
		/// Since my destructor is private the template std::unique_ptr needs access to it so I made it a friend.
		/// However, std::default_delete is the default destruction policy used by std::unique_ptr 
		/// when no deleter is specified, therefore I'll make std::default_delete my friend as well. 
		friend std::default_delete<SceneManager>;
		bool isRunning;
		unsigned int frameRate; /// Frames / second

	public:
		///kill any default constructor or operator that the compiler might create
		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;
		SceneManager& operator=(SceneManager&&) = delete;
		static SceneManager* getInstance();
		void Run();
		bool Initialize();
		void Update(const float deltaTime);
		void Render() const;
		void HandleEvents();
	};





}