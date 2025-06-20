#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <SDL2/SDL_filesystem.h>
#include <SDL2/SDL_ttf.h>

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

using std::cout;

std::unordered_map<std::string, FuncHead*> functions;

std::vector<std::vector<Collider*>> flags = std::vector<std::vector<Collider*>>(6);

std::map<int, std::unordered_set<Entity*>> layers;

RenderWindow window("hi", 1280, 720);

TTF_Font* comic;

SDL_Texture* gapTexture = window.loadTexture("res/gfx/Gap.png");

SDL_Texture* varTexture = window.loadTexture("res/gfx/Variable.png");

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
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        cout << "SDL_MIXER HAS FAILED. ERROR:" << SDL_GetError() << "\n";
    }
    cout << "Init Passed" << "\n";

    window.changeBackground({82,79,61});

    comic = TTF_OpenFont("res/gfx/ComicNeueBold.ttf", 43);

    SDL_Texture* blockTexture = window.loadTexture("res/gfx/DefaultBlock.png");
    SDL_Texture* headTexture = window.loadTexture("res/gfx/DefaultHead.png");
    SDL_Texture* loopTexture = window.loadTexture("res/gfx/Loop.png");
    SDL_Texture* buttonTexture = window.loadTexture("res/gfx/Button.png");
    
    //Mix_Music* gMusic = Mix_LoadMUS("res/dev/death-odyssey.mp3"); UNCOMMENT MEMORY CLEANUP

    //Mix_VolumeMusic(50);

    //Mix_PlayMusic(gMusic, -1);
    
    SDL_Rect blockSize;
    blockSize.x = 0;
    blockSize.y = 0;
    blockSize.w = 13;
    blockSize.h = 14;

    SDL_Rect loopSize;
    loopSize.x = 0;
    loopSize.y = 0;
    loopSize.w = 19;
    loopSize.h = 14;

    SDL_Rect headSize;
    headSize.x = 0;
    headSize.y = 0;
    headSize.w = 21;
    headSize.h = 17;

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

    SDL_Rect bodyFrame;
    bodyFrame.x = 0;
    bodyFrame.y = 0;
    bodyFrame.w = 10;
    bodyFrame.h = 7;

    new Block(Vector2f(0,70), blockTexture, blockSize, BlockType::DEFAULT, 4, "Say: \"Hello World!\"", Vector2f(10, 4), {"x:", "y:", "z:"});
    new Block(Vector2f(0,140), blockTexture, blockSize, BlockType::DEFAULT, 4, "Say: \"Hello World!\"");
    new Block(Vector2f(0,210), blockTexture, blockSize, BlockType::DEFAULT, 4, "Say: \"Hello World!\"");

    new Loop(Vector2f(300,300), 4, loopTexture, BlockType::DEFAULTLOOP, loopSize, "repeat 3 times");
    new Loop(Vector2f(300,300), 4, loopTexture, BlockType::DEFAULTLOOP, loopSize, "repeat 3 times");
    new FuncHead(Vector2f(600,300), 4, headTexture, BlockType::DEFAULTHEAD, headSize, "main", Vector2f(10, 16));
    Button button(Vector2f(600,600),buttonTexture,buttonSize,Compilation::Compile,buttonFloatSize,Vector2f(4,4));

    Variable var(Vector2f(400, 400), varTexture, bodyFrame, Vector2f(4,4));

    Variable* heldVar = nullptr;
    Block* heldObject = nullptr;

    Vector2f clickedPos;
    bool gameRunning = true;
    SDL_Event event;

    cout << "Game Start" << "\n";
    while(gameRunning){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameRunning = false;
            }
            if(event.type == SDL_MOUSEMOTION){
                if(heldObject != nullptr){
                    heldObject -> setPos(Vector2f(event.motion.x, event.motion.y) - clickedPos);
                }
                if(heldVar != nullptr){
                    heldVar -> setPos(Vector2f(event.motion.x, event.motion.y) - clickedPos);
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT){
                    General::OnClick(event, heldObject, clickedPos, heldVar);
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
            }
        }
        window.clear();

        for(auto layer : layers){
            for(Entity* entity : layer.second){
                window.render(*entity);
            }
        }

        window.display();
    }
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
    Mix_Quit();

    utils::DeconstructFunctionHeads();

    return 0;
}