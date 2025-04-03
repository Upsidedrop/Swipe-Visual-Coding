#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <SDL2/SDL_filesystem.h>

#include "RenderWindow.hpp"
#include "Block.hpp"
#include "Utils.hpp"
#include "Loop.hpp"
#include "FuncHead.hpp"
#include "Collider.hpp"

using std::cout;

std::vector<std::vector<Collider*>> flags = std::vector<std::vector<Collider*>>(3);

std::map<int, std::unordered_set<Entity*>> layers;

int main(int agrv, char* args[]) {
    cout << "Program Start" << "\n";
    
    if(SDL_Init(SDL_INIT_VIDEO) > 0){
        cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << "\n";
    }
    if(!(IMG_Init(IMG_INIT_PNG))){
        cout << "IMG_Init HAS FAILED. ERROR:" << SDL_GetError() << "\n";
    }
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        cout << "SDL_MIXER HAS FAILED. ERROR:" << SDL_GetError() << "\n";
    }
    cout << "Init Passed" << "\n";
    
    cout << SDL_GetPrefPath("Oddity", "Swipe") << "\n";

    RenderWindow window("hi", 1280, 720);

    SDL_Texture* blockTexture = window.loadTexture("res/gfx/DefaultBlock.png");
    SDL_Texture* headTexture = window.loadTexture("res/gfx/DefaultHead.png");
    SDL_Texture* loopTexture = window.loadTexture("res/gfx/Loop.png");
    
    //Mix_Music* gMusic = Mix_LoadMUS("res/dev/death-odyssey.mp3"); UNCOMMENT MEMORY CLEANUP

    //Mix_VolumeMusic(50);

    //Mix_PlayMusic(gMusic, -1);

    SDL_Rect blockSize;
    blockSize.x = 0;
    blockSize.y = 0;
    blockSize.w = 63;
    blockSize.h = 12;

    SDL_Rect headSize;
    headSize.x = 0;
    headSize.y = 0;
    headSize.w = 63;
    headSize.h = 15;

    new Block(Vector2f(0,0), blockTexture, blockSize, BlockType::DEFAULT, Vector2f(4, 4));
    for (size_t i = 0; i < 8; i++)
    {
        new Block(Vector2f(0,(i+1) * 70), blockTexture, blockSize, BlockType::DEFAULT, Vector2f(i + 1, 4));
    }
    new Loop(Vector2f(300,300), Vector2f(4,4), loopTexture, BlockType::DEFAULTLOOP, blockSize);
    new FuncHead(Vector2f(600,300), Vector2f(4,4), headTexture, BlockType::DEFAULTHEAD, headSize);

    bool gameRunning = true;
    SDL_Event event;
    Block* heldObject = nullptr;
    Vector2f clickedPos;

    cout << "Game Start" << "\n";
    while(gameRunning){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                gameRunning = false;
            }
            if(event.type == SDL_MOUSEMOTION){
                if(heldObject == nullptr){
                    continue;
                }
                heldObject -> setPos(Vector2f(event.motion.x, event.motion.y) - clickedPos);
            }
            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT){
                    Collider* collision = utils::CheckMouseCollisions(Vector2f(event.button.x, event.button.y), {2});

                    if(collision != nullptr){
                        heldObject = static_cast<Block*>(collision->GetParent());
                        clickedPos = Vector2f(event.button.x - heldObject -> getPos().x, event.button.y - heldObject -> getPos().y);
                    }
                    if(heldObject != nullptr){
                        if(heldObject -> getParent() != nullptr){
                            cout << "had parent" << "\n";
                            if(heldObject -> getParent() -> GetType() == BlockType::DEFAULTLOOP){
                                cout << "parent was loop" << "\n";
                                heldObject -> getParent() -> RemoveChild(heldObject);
                            }
                            else{
                                heldObject -> getParent() -> RemoveChild();
                            }
                            heldObject -> setParent(nullptr);
                        }
                        heldObject -> SetLayer(1);
                    }
                }
            }
            if(event.type == SDL_MOUSEBUTTONUP){
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(heldObject != nullptr){
                        Collider* neighborCol;
                        if(heldObject -> getTopCollider() != nullptr){
                            neighborCol = heldObject -> getTopCollider() -> CheckForCollisions({1});
                            if(neighborCol != nullptr){
                                Block* neighbor = static_cast<Block*>(neighborCol -> GetParent());

                                if(neighbor -> getChild() != nullptr){
                                    if(neighborCol == &(neighbor -> getBottomCollider())){
                                        Block* iterator = heldObject;
                                        while(iterator -> getChild() != nullptr){
                                            iterator = iterator -> getChild();
                                        }
                                        iterator -> setChild(neighbor -> getChild());
                                        iterator -> getChild() -> setParent(iterator);
                                    }
                                }
                                heldObject -> setPos(neighbor -> getPos() + Vector2f(neighborCol -> GetFrame().x * neighbor -> getScale().x, neighborCol -> GetFrame().y * neighbor  -> getScale().y));
                                if(neighbor -> GetType() == BlockType::DEFAULTLOOP){
                                    neighbor -> setChild(heldObject, neighborCol);
                                }
                                else{
                                    neighbor -> setChild(heldObject);
                                }
                                heldObject -> setParent(neighbor);
                            }
                        }
                        heldObject -> SetLayer(0);
                        heldObject = nullptr;
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

    //Mix_FreeMusic(gMusic);

    SDL_Quit();
    IMG_Quit();
    Mix_Quit();

    return 0;
}