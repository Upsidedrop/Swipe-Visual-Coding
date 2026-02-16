#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <SDL_filesystem.h>
#include <SDL_ttf.h>
#include <SDL_keyboard.h>

#include "RenderWindow.hpp"
#include "Block.hpp"
#include "Utils.hpp"
#include "Loop.hpp"
#include "FuncHead.hpp"
#include "Collider.hpp"
#include "Button.hpp"
#include "Compiler.hpp"
#include "TextBox.hpp"
#include "General.hpp"
#include "Gap.hpp"
#include "Variable.hpp"
#include "RandomDeletionStack.hpp"
#include "TextArea.hpp"

using std::cout;

std::unordered_map<std::string, FuncHead*> functions;

std::vector<std::vector<Collider*>> flags = std::vector<std::vector<Collider*>>(7);

std::map<int, RandomDeletionStack<Entity*>*> layers;

RenderWindow window("hi", 1280, 720);

TTF_Font* comic;

SDL_Texture* gapTexture = window.loadTexture("res/gfx/Gap.png");

SDL_Texture* varTexture = window.loadTexture("res/gfx/Variable.png");

Vector2f cameraPos(0, 0);
Vector2f lastCamPos;
float cameraZoom = 0.75;

bool isDragging = false;

int main(int agrv, char* args[]) {
    cout << "Program Start" << "\n";
    
    if(SDL_Init(SDL_INIT_VIDEO) > 0){
        cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << "\n";
    }
    if(!(IMG_Init(IMG_INIT_PNG))){
        cout << "IMG_Init HAS FAILED. ERROR:" << SDL_GetError() << "\n";
    }
    if(TTF_Init()){
        cout << "TTF_Init HAS FAILED. ERROR:" << TTF_GetError() << "\n";
    }
    // if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
    //     cout << "SDL_MIXER HAS FAILED. ERROR:" << SDL_GetError() << "\n";
    // }
    cout << "Init Passed" << "\n";

    window.changeBackground({82,79,61});

    comic = TTF_OpenFont("res/gfx/ComicNeueBold.ttf", 43);

    SDL_Texture* blockTexture = window.loadTexture("res/gfx/DefaultBlock.png");
    SDL_Texture* headTexture = window.loadTexture("res/gfx/DefaultHead.png");
    SDL_Texture* loopTexture = window.loadTexture("res/gfx/Loop.png");
    SDL_Texture* buttonTexture = window.loadTexture("res/gfx/Button.png");
    SDL_Texture* textAreaTexture = window.loadTexture("res/gfx/TextArea.png");
    
    //Mix_Music* gMusic = Mix_LoadMUS("res/dev/death-odyssey.mp3"); UNCOMMENT MEMORY CLEANUP

    //Mix_VolumeMusic(50);

    //Mix_PlayMusic(gMusic, -1);
    
    SDL_Rect blockSize;
    blockSize.x = 0;
    blockSize.y = 0;
    blockSize.w = 14;
    blockSize.h = 4;

    SDL_Rect loopSize;
    loopSize.x = 0;
    loopSize.y = 0;
    loopSize.w = 20;
    loopSize.h = 4;

    SDL_Rect headSize;
    headSize.x = 0;
    headSize.y = 0;
    headSize.w = 27;
    headSize.h = 4;

    SDL_Rect buttonSize;
    buttonSize.x = 0;
    buttonSize.y = 0;
    buttonSize.w = 37;
    buttonSize.h = 15;

    SDL_FRect buttonFloatSize;
    buttonFloatSize.x = 0;
    buttonFloatSize.y = 0;
    buttonFloatSize.w = 37;
    buttonFloatSize.h = 15;


    new Block(Vector2f(0,70), blockTexture, blockSize, BlockType::DEFAULT, 4, "Say: \"Hello World!\"",  Vector2f(10, 11), {"x:", "y:", "z:"});
    new Block(Vector2f(0,140), blockTexture, blockSize, BlockType::DEFAULT, 4, "Say: ", Vector2f(10, 11), {"Message:"}, CodeSnippet::PRINT);
    new Block(Vector2f(0,210), blockTexture, blockSize, BlockType::DEFAULT, 4, "Say: \"Hello World!\"", Vector2f(10, 11));

    new Loop(Vector2f(300,300), 4, loopTexture, BlockType::DEFAULTLOOP, loopSize, "repeat", Vector2f(10, 9), {" "});
    new Loop(Vector2f(300,300), 4, loopTexture, BlockType::DEFAULTLOOP, loopSize, "repeat", Vector2f(10, 9), {" "});
    new FuncHead(Vector2f(600,300), 4, headTexture, BlockType::DEFAULTHEAD, headSize, "main", Vector2f(10, 20), {});
    Button button(Vector2f(600,600),buttonTexture,buttonSize,Compilation::Compile,buttonFloatSize,Vector2f(4,4));

    new Variable(Vector2f(400, 600), varTexture, "Sensor", Vector2f(8,1));
    new Variable(Vector2f(400, 600), varTexture, "Sensor", Vector2f(8,1), 4, 0, {"first:","second:"});
    new Variable(Vector2f(400, 600), varTexture, "Sensor", Vector2f(8,1), 4, 0, {"first:","second:"});
    new Variable(Vector2f(400, 400), varTexture, "Add:", Vector2f(8,1), 4, 0, {" ","+"});

    new TextArea(Vector2f(400, 600), textAreaTexture, Vector2f(8,0.8), 4, 0);
    new TextArea(Vector2f(400, 600), textAreaTexture, Vector2f(8,0.8), 4, 0);

    Variable* heldVar = nullptr;
    Block* heldObject = nullptr;
    TextArea* selectedTextBox = nullptr;

    Vector2f clickedPos;
    bool gameRunning = true;
    SDL_Event event;

    SDL_StartTextInput();

    cout << "Game Start" << "\n";
    while(gameRunning){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameRunning = false;
            }
            if(event.type == SDL_MOUSEMOTION){
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(heldObject != nullptr){
                        heldObject -> setPos((Vector2f(event.motion.x, event.motion.y) - clickedPos) * (1/ cameraZoom));
                    }
                    if(heldVar != nullptr){
                        heldVar -> setPos(Vector2f(event.motion.x, event.motion.y) - clickedPos);
                    } 
                }

                if(isDragging){
                    cameraPos = Vector2f(clickedPos.x - event.button.x + lastCamPos.x, clickedPos.y - event.button.y + lastCamPos.y);
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT){
                    General::OnClick(event, heldObject, clickedPos, heldVar, selectedTextBox);
                }
                if(event.button.button == SDL_BUTTON_MIDDLE){
                    General::beginDragging(clickedPos, event);
                }
            }
            if(event.type == SDL_MOUSEBUTTONUP){
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(heldObject != nullptr){
                        General::BlockReleased(heldObject);
                    }
                    if(heldVar != nullptr){
                        General::VariableReleased(heldVar);
                    }
                }
                if(isDragging){
                    isDragging = false;
                }
            }
            if(event.type == SDL_KEYDOWN){
                if(selectedTextBox != nullptr){
                    if(event.key.keysym.sym == SDLK_BACKSPACE && selectedTextBox -> getText().length() > 0){
                        auto text = selectedTextBox -> getText();
                        text.pop_back();
                        selectedTextBox -> setText(text.c_str());
                    }
                    else if(event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL){
                        char* tempText = SDL_GetClipboardText();
                        auto text = selectedTextBox -> getText();
                        text += tempText;
                        selectedTextBox -> setText(text.c_str());
                        SDL_free(tempText);
                    }
                }
            }
            if(event.type == SDL_TEXTINPUT){
                if(selectedTextBox == nullptr){
                    continue;
                }
                if (!(SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V'))){
                    auto text = selectedTextBox -> getText();
                    text += event.text.text;
                    selectedTextBox -> setText(text.c_str());
                }
            }
        }
        window.clear();

        for(auto layer : layers){
            auto node = layer.second -> GetChild();
            while(node != nullptr){
                window.render(*node -> GetValue());
                node = node -> GetChild();
            }
        }

        window.display();
    }

    SDL_StopTextInput();

    std::cout << "exit" << "\n";
    window.cleanUp();

    SDL_DestroyTexture(blockTexture);
    SDL_DestroyTexture(headTexture);
    SDL_DestroyTexture(loopTexture);
    SDL_DestroyTexture(buttonTexture);

    TTF_CloseFont(comic);
    //Mix_FreeMusic(gMusic);

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    //Mix_Quit();

    utils::DeconstructFunctionHeads();
    utils::DeconstructLayers();

    return 0;
}
