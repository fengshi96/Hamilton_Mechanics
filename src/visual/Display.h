//
// Created by shifeng on 3/18/21.
//

#ifndef MCMC_DISPLAY_H
#define MCMC_DISPLAY_H
#include <string>
#include <SDL2/SDL.h>

class Display {
public:
    Display(int width, int height, const std::string& title);
    void Update();
    bool IsClosed();
    virtual ~Display();

private:
    Display(const Display& other) {}
//    Display& operator=(const Display& other) {}

    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    bool m_isClosed;
};


#endif //MCMC_DISPLAY_H
