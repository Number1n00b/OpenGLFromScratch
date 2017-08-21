/*
TODO LIST:
NAMING CONVENTION:
Classes and Functions: FULL CamelCase
Variables/Parameters: under_scores
Class Member Variables:
                    private: m_VariableName
                    public: variableName

4) Rewrite what is not mine, or use other, industry standard, free libaries (obj_loader and stb_image).

6) Find a way to initialise GLEW outside of Display.cpp so that if it fails we can close the program. (Do memory management too, deleting context etc).

8) Find out how to draw UI elements. (Possibly use a different shader).

9) Restructure main into an app class with all the variables required, use main to initialise and start the app class.

11) Make 'escape' toggle a pause menu, during the pause menu the mouse is NOT clipped to the screen. else it is.

12) Idk man... make the UI work with text. FreeType not working FeelsBadMan

13) Sound?! :O

14) Framerate independant movement. (Change Update() to Update(timestep))

15) Load .mtl files and learn how to use them.

18) Fix camera movement jitter / stuttering and check why normalise sometimes returns NAN in camera.

19) Create spawner class to spawn objects. (Factory Pattern?)

NOTES:
To make the camera track an object, simply set its lookDirection to object.pos - cam.pos
*/

//Standard libs.
#include <iostream>
#include <windows.h>

//Graphics libs.
#include <GL/glew.h>

//This took me much to long to solve. Stops SDL from redefining main causing
//undefined reference to WinMain@16.
#define SDL_MAIN_HANDLED

//Libraries for mouse pointer manipulation.
#include <SDL.h>
#include <SDL_syswm.h>

#include "main.h"

//Output
#include "../display/Display.h"

//Model Classes
#include "../model/Mesh.h"
#include "../shaders/Shader.h"
#include "../model/Texture.h"
#include "../model/Transform.h"
#include "../model/Camera.h"
#include "../model/Player.h"
#include "../model/WorldObject.h"
#include "../model/OscilatingObject.h"

//Input
#include "../input/InputEventHandler.h"

//Moise position, used to capture and reset mouse on pause / unpause.
int prev_cursor_X = 0;
int prev_cursor_Y = 0;

//Game state variables.
GAME_STATE game_state;
bool Game::should_close = false;

//Window paramentrs.
int Window::window_width = 1080;
int Window::window_height = 800;

//FPS params.
const int TARGET_FPS = 60;
const double MS_PER_FRAME = 1000.0 / TARGET_FPS;

//Container for all objects in the world, Iterated over every Update() call.
std::vector<WorldObject*> world_objects;

//Globals for display, camera and events.
Display *main_window;
Camera *main_camera;
InputEventHandler *event_handler;

//Using / Namespace declarations.
using std::cin;
using std::cout;
using std::endl;
using glm::vec3;

void Initialise() {
    //Craete the window and context.
    main_window = new Display(Window::window_width, Window::window_height, "Main window.");

    //Create the event handler.
    event_handler = new InputEventHandler();

    //Create the main camera.
    vec3 cam_position = vec3(0, 0, 10);
    vec3 cam_look_direction = vec3(0, 0, -1);
    vec3 cam_up_direaction = vec3(0, 1, 0);
    float cam_fov = 70;
    float cam_z_near = 0.01;
    float cam_z_far = 1000;
    main_camera = new Camera(cam_position, cam_look_direction, cam_up_direaction, cam_fov, main_window->GetAspectRatio(), cam_z_near, cam_z_far);

    //Register global event listeners.
    event_handler->RegisterMouseListener(main_camera);
    event_handler->RegisterKeyboardListener(main_camera);

    //Set the camera for our drawable class as the main camera.
    WorldObject::SetCamera(main_camera);

    Game::ResumeGame();
}


void CreateWorldObjects() {
    //Here we create all of the objects that start out in the world. Later we can have a list of startup objects and just iterate through it, creating them all.

    //Create the basic shaders.
    Shader *standard_shader = new Shader("./res/basicShader");

    //Load our tectures.
    Texture* piranahs_tex = new Texture("./res/download.jpg");
    Texture* bricks_tex = new Texture("./res/bricks.jpg");
    Texture* floor_tex = new Texture("./res/sand.jpg");

    Texture* x_tex = new Texture("./res/x.jpg");
    Texture* y_tex = new Texture("./res/y.jpg");
    Texture* z_tex = new Texture("./res/z.jpg");
    Texture* blue = new Texture("./res/blue.jpg");

    //Load the game object meshes.
    Mesh* monkey_mesh = new Mesh("./res/monkey3.obj");
    Mesh* car_mesh = new Mesh("./res/myCar.obj");
    Mesh* plane_mesh = new Mesh("./res/6x6_plane.obj");

    //This transform ensures the monkeys face the right direction on spawn.
    Transform oriented_monkey;
    oriented_monkey.SetRotation(-3.14 / 2, 3.14, 0);

    //Create our drawable game objects.
    vec3 x_axis = vec3(1, 0, 0);
    vec3 y_axis = vec3(0, 1, 0);
    vec3 z_axis = vec3(0, 0, 1);
    float speed = 0.02;
    float amplitude = 5;

    //Create oscilating monkeys for perspective.
    WorldObject* monkey_x = new OscilatingObject("Monkey Number One", standard_shader, x_tex, monkey_mesh, oriented_monkey, x_axis, speed, amplitude);
    world_objects.push_back(monkey_x);

    WorldObject* monkey_y = new OscilatingObject("Monkey Number Two", standard_shader, y_tex, monkey_mesh, oriented_monkey, y_axis, speed, amplitude);
    world_objects.push_back(monkey_y);

    WorldObject* monkey_z = new OscilatingObject("Monkey Number Three", standard_shader, z_tex, monkey_mesh, oriented_monkey, z_axis, speed, amplitude);
    world_objects.push_back(monkey_z);

    //Create a plane. Floor?
    vec3 floor_pos = vec3(0, -3, 0);
    WorldObject* floor = new OscilatingObject("Monkey Number Three", standard_shader, z_tex, monkey_mesh, oriented_monkey, z_axis, speed, amplitude);
    world_objects.push_back(floor);

    //Create the player.
    /*Transform car_behind;
    car_behind.SetPos(0, -2, 20);
    car_behind.SetRotation(0, 3.14/2, 0);
    Player* car = new Player("Player One", standard_shader, blue, car_mesh, car_behind, event_handler);
    world_objects.push_back(car);*/
}


int main(int argc, char *argv[]) {
	cout << "====== Starting Program... ======" << endl;

    //Initalise the basics, Camera, UI, window, eventhandler.
    Initialise();

    CreateWorldObjects();
    for (std::vector<WorldObject*>::iterator it = world_objects.begin(); it != world_objects.end(); it++) {
        cout << "Name: " << (*it)->name << endl;
    }

    //Main loop setup.
	cout << "\nEntering main loop." << endl;

    double curr_time = 0;
    double prev_time = SDL_GetTicks();
    double dt = 0;

    double time_since_last_frame = 0;

    int num_frames = 0;
    int fps_timer_start = prev_time;
    int fps_timer_end;

    //The main loop!
	while (!Game::should_close) {
        //Always handle events regardless of state.
        //Currently this works because WorldObjects only "Update" In the inner if statement: ie. when game is running.
        //However, the event norifications are ALWAYS sent. So if somethign changes in the "NotifyEvent" method, it will change even in pause menu.
        event_handler->HandleSDLEvents();

        curr_time = SDL_GetTicks();

        //dt here is time per loop
        dt = curr_time - prev_time;
        prev_time = curr_time;

        time_since_last_frame += dt;

        //Cap FPS and render only when needed. @NOTE: Physics updates done only on every render call.
        if (time_since_last_frame >= MS_PER_FRAME) {
            num_frames++;

            //This is just to display FPS, once I figure out how to do text in OpenGL.
            if (num_frames == 100) {
                fps_timer_end = curr_time;
                //cout << "FPS: " << (float(num_frames) / (float(fps_timer_end - fps_timer_start) / 1000.0)) << endl;
                fps_timer_start = fps_timer_end;
                num_frames = 0;
            }

            //Do physics updates
            if (game_state == RUNNING) {
                //Update all our objects.
                for (std::vector<WorldObject*>::iterator it = world_objects.begin(); it != world_objects.end(); it++) {
                    (*it)->Update();
                }

                //Update the main camera.
                main_camera->Update();
            }

            //Render
            Window::DrawFrame();

            time_since_last_frame = 0.0;
        }
	}

    game_state = CLOSING;

	cout << "End of main loop." << endl;

	cout << "\nFreeing resources..." << endl;

	cout << "Deinitialising SDL..." << endl;
	SDL_Quit();

	cout << "====== Ending Program... ======" << endl;

	return 0;
}


void Window::ResizeWindow(int width, int height) {
    main_window->UpdateViewport(width, height);
    main_camera->NotifyScreenResize(width, height);

    Window::window_width = width;
    Window::window_height = height;
}

void Window::DrawFrame() {
    //Clear the window.
    main_window->Clear(0.5, 0.5, 0.5, 0.5);

    //Draw our drawables.
    for (std::vector<WorldObject*>::iterator it = world_objects.begin(); it != world_objects.end(); it++) {
        (*it)->Draw();
    }

    //Swap buffers.
    //@NOTE that main_window is of type Display. Naming could be better here.
    //This is where the mouse warpng is done, while game is running.
    main_window->Update();
}

void Game::FailAndExit(std::string message){
	cout << "\n======\nTHE PROGRAM HAS FAILED\n======\n" << message << endl;
	cin.get();
	exit(-1);
}

void Game::TogglePause() {
    if (game_state == PAUSED) {
        Game::ResumeGame();
    }
    else if (game_state == RUNNING) {
        Game::PauseGame();
    }
}

void Game::PauseGame() {
    game_state = PAUSED;

    //Let go of the cursor.
    SetCursorClip(false);
    SDL_ShowCursor(true);

    //Put the cursor back to where it was before we took control.
    SDL_WarpMouseInWindow(NULL, prev_cursor_X, prev_cursor_Y);

    //Then ignore the mouse event generated.
    SDL_PumpEvents();
    SDL_FlushEvent(SDL_MOUSEMOTION);

    cout << "Pausing..." << endl;
}

void Game::ResumeGame() {
    game_state = RUNNING;

    //Empty the event queue so that actions done while paused does not affect the game.
    SDL_PumpEvents();
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        //Do nothing.
    }
    //Save the position of the mouse before we take over.
    SDL_GetMouseState(&prev_cursor_X, &prev_cursor_Y);

    //Grab the cursor.
    SetCursorClip(true);
    SDL_ShowCursor(false);

    cout << "Resuming... " << endl;
}


//@Robustness, this may have to be re-called every time the window is resized.
void Game::SetCursorClip(bool clip) {
    if (!clip) {
        //Unclip the cursor.
        ClipCursor(nullptr);
    }
    else {
        //Clip the cursor to the window. (Just incase. This isn't really needed since we're warping the mouse to center all the time.)
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(main_window->GetWindow(), &wmInfo);
        HWND hwnd = wmInfo.info.win.window;

        RECT rect;
        GetClientRect(hwnd, &rect);

        POINT ul;
        ul.x = rect.left;
        ul.y = rect.top;

        POINT lr;
        lr.x = rect.right;
        lr.y = rect.bottom;

        MapWindowPoints(hwnd, nullptr, &ul, 1);
        MapWindowPoints(hwnd, nullptr, &lr, 1);

        rect.left = ul.x;
        rect.top = ul.y;

        rect.right = lr.x;
        rect.bottom = lr.y;

        ClipCursor(&rect);
    }
}
