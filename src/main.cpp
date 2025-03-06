#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Block.hpp"
#include "Utils.hpp"
#include "LinkedList.hpp"

using namespace std;


int main(int agrv, char* args[]) {
    cout << "Program Start" << endl;
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
    
    Mix_Music* gMusic = Mix_LoadMUS("res/dev/death-odyssey.mp3");

    Mix_VolumeMusic(50);

    Mix_PlayMusic(gMusic, -1);

    vector<vector<Collider*>> colliderFlags = vector<vector<Collider*>>(2);

    LinkedList<Block> blocks(new Block(Vector2f(0,0), blockTexture, &colliderFlags, Vector2f(4, 4), 64, 14));
    blocks.Add(new Block(Vector2f(0,250), blockTexture, &colliderFlags, Vector2f(4, 4), 64, 14));

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
                    auto lambda = [&clickedPos, event, &heldObject](Block* block){
                        clickedPos = Vector2f(event.button.x - block -> getPos().x, event.button.y - block -> getPos().y);
                        if(clickedPos.x > 0 && clickedPos.x < block -> getCurrentFrame().w * block -> getScale().x
                            && clickedPos.y > 0 && clickedPos.y < block -> getCurrentFrame().h * block -> getScale().y){
                                heldObject = block;
                                return true;
                        }
                        return false;
                    };
                    Node<Block>* iterator = blocks.getFirstNode();
                    while(iterator != nullptr){
                        if(lambda(iterator -> getValue())){
                            break;
                        }
                        iterator = iterator -> getNextNode();
                    }
                    cout << heldObject << endl;
                    if(heldObject != nullptr){
                        cout << heldObject -> getChild() << endl;
                        if(heldObject -> getParent() != nullptr){
                            heldObject -> getParent() -> setChild(nullptr);
                            heldObject -> setParent(nullptr);
                        }
                    }
                }
            }
            if(event.type == SDL_MOUSEBUTTONUP){
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(heldObject != nullptr){
                        Collider* neighbor;
                        neighbor = heldObject -> getTopCollider().CheckForCollisions({1});
                        if(neighbor != nullptr){
                            heldObject->setPos(neighbor->GetParent() -> getPos() + Vector2f(0, 48));
                            neighbor -> GetParent() -> setChild(heldObject);
                            heldObject -> setParent(neighbor -> GetParent());
                        }
                        heldObject = nullptr;
                    }
                    
                }
            }
        }
        window.clear();

        Node<Block>* iterator = blocks.getFirstNode();
        while(iterator != nullptr){
            window.render(*(iterator -> getValue()));
            iterator = iterator -> getNextNode();
        }

        window.display();
    }
    std::cout << "exit" << "\n";
    window.cleanUp();

    SDL_DestroyTexture(blockTexture);

    Mix_FreeMusic(gMusic);

    SDL_Quit();
    IMG_Quit();
    Mix_Quit();

    return 0;
}