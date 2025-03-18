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
#include "LinkedList.hpp"
#include "Loop.hpp"

using namespace std;


int main(int agrv, char* args[]) {
    cout << "Program Start" << endl;
    cout << SDL_GetPrefPath("Oddity", "Swipe") << "\n";
    if(SDL_Init(SDL_INIT_VIDEO) > 0){
        cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
    }
    if(!(IMG_Init(IMG_INIT_PNG))){
        cout << "IMG_Init HAS FAILED. ERROR:" << SDL_GetError() << endl;
    }
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        cout << "SDL_MIXER HAS FAILED. ERROR:" << SDL_GetError() << endl;
    }
    cout << "Init Passed" << endl;
    RenderWindow window("hi", 1280, 720);

    SDL_Texture* blockTexture = window.loadTexture("res/gfx/DefaultBlock.png");
    SDL_Texture* loopTexture = window.loadTexture("res/gfx/Loop.png");
    
    //Mix_Music* gMusic = Mix_LoadMUS("res/dev/death-odyssey.mp3"); UNCOMMENT MEMORY CLEANUP

    //Mix_VolumeMusic(50);

    //Mix_PlayMusic(gMusic, -1);

    vector<vector<Collider*>> colliderFlags = vector<vector<Collider*>>(3);

    map<int, unordered_set<Entity*>> renderLayers;
    SDL_Rect blockSize;
    blockSize.x = 0;
    blockSize.y = 0;
    blockSize.w = 63;
    blockSize.h = 12;
    LinkedList<Block> blocks(new Block(Vector2f(0,0), blockTexture, &renderLayers, &colliderFlags, blockSize, BlockType::DEFAULT ,Vector2f(4, 4)));
    for (size_t i = 0; i < 8; i++)
    {
        blocks.Add(new Block(Vector2f(0,(i+1) * 70), blockTexture, &renderLayers, &colliderFlags, blockSize, BlockType::DEFAULT, Vector2f(i + 1, 4)));
    }
    Loop loop(Vector2f(300,300), Vector2f(4,4), loopTexture, &renderLayers, &colliderFlags, BlockType::DEFAULTLOOP, blockSize);

    cout << "Loop Address: " << loop.GetInnerCollider() << "\n";

    bool gameRunning = true;
    SDL_Event event;
    Block* heldObject = nullptr;
    Vector2f clickedPos;

    cout << "Game Start" << endl;
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
                    Collider* collision = utils::CheckMouseCollisions(Vector2f(event.button.x, event.button.y), &colliderFlags, {2});
                    if(collision != nullptr){
                        heldObject = collision->GetParent();
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
                        Collider* neighbor;
                        neighbor = heldObject -> getTopCollider().CheckForCollisions({1});
                        if(neighbor != nullptr){
                            if(neighbor -> GetParent() -> getChild() != nullptr){
                                Block* iterator = heldObject;
                                while(iterator -> getChild() != nullptr){
                                    iterator = iterator -> getChild();
                                }
                                iterator -> setChild(neighbor -> GetParent() -> getChild());
                                iterator -> getChild() -> setParent(iterator);
                            }
                            if(neighbor -> GetParent() -> GetType() == BlockType::DEFAULTLOOP){
                                neighbor -> GetParent() -> setChild(heldObject, neighbor);
                            }
                            else{
                                neighbor -> GetParent() -> setChild(heldObject);
                            }
                            heldObject -> setPos(neighbor->GetParent() -> getPos() + Vector2f(neighbor -> GetFrame().x * neighbor -> GetParent() -> getScale().x, neighbor -> GetFrame().y * neighbor -> GetParent() -> getScale().y));
                            heldObject -> setParent(neighbor -> GetParent());
                        }
                        heldObject -> SetLayer(0);
                        heldObject = nullptr;
                    }
                    
                }
            }
        }
        window.clear();

        for(auto layer : renderLayers){
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