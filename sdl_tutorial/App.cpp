#include "App.h"
#include "Log.h"


App App::Instance;

App::App() {
}

// handle an event
void App::OnEvent(SDL_Event* Event) {
}

// Initialize the game
bool App::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Log("Unable to Init SDL: %s", SDL_GetError());
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		Log("Unable to Init hinting: %s", SDL_GetError());
	}

	// Create the main window
	if ((Window = SDL_CreateWindow(
		"My SDL Game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WindowWidth, WindowHeight, SDL_WINDOW_SHOWN)
		) == NULL) {
		Log("Unable to create SDL Window: %s", SDL_GetError());
		return false;
	}

	PrimarySurface = SDL_GetWindowSurface(Window);

	if ((Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		Log("Unable to create renderer");
		return false;
	}

	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);

	// Initialize image loading for PNGs
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		Log("Unable to init SDL_image: %s", IMG_GetError());
		return false;
	}

	// Load all of our Textures (see TextureBank class for expected folder)
	if (TextureBank::Init() == false) {
		Log("Unable to init TextureBank");
		return false;
	}

	return true;
}


void App::Loop() {
}

void App::Render() {
	SDL_RenderClear(Renderer);
	//TextureBank::Get("Test")->Render(0, 0);  // You should really check your pointers
	SDL_RenderPresent(Renderer);
}

// Release resources
void App::Cleanup() {
	TextureBank::Cleanup();

	if (Renderer) {
		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;
	}

	if (Window) {
		SDL_DestroyWindow(Window);
		Window = NULL;
	}

	IMG_Quit();
	SDL_Quit();
}

int App::Execute(int argc, char* argv[]) {
    // Initialize the game
    if (!Init()) return 0;

    SDL_Event Event;

    // Game loop
    while (Running) {
        // Check for events (handle one at a time)
        while (SDL_PollEvent(&Event) != 0) {
            OnEvent(&Event);
            if (Event.type == SDL_QUIT) Running = false;
        }

        Loop();       // move data around or whatever
        Render();     // render our game.

        SDL_Delay(1); // pause
    }

    Cleanup();

    return 1;
}

SDL_Renderer* App::GetRenderer() { return Renderer; }

App* App::GetInstance() { return &App::Instance; }

int App::GetWindowWidth() { return WindowWidth; }
int App::GetWindowHeight() { return WindowHeight; }

