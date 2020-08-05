/*
 * Window.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Nr5
 */

#include "Window.h"
#include <iostream>
#include <SDL2/SDL.h>

#include "./ui/Panel.h"
#include "./ui/Label.h"

#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include "ShaderProgram.h"
#include <ctime>

#include <SDL2/SDL_ttf.h>

#include "Scene.h"
	int Panel::screenwidth=1920;
	int Panel::screenheight=1080;
	
Window::Window(int x, int y, int width,int height, const char* title,unsigned int sdlflags):Panel(0,0,width,height,0) {
	Panel::screenwidth=width;
	Panel::screenheight=height;
	
	
	
	running =1;
	
	sdlwin=SDL_CreateWindow(title , x,  y,width,height,SDL_WINDOW_OPENGL|sdlflags);

    if (!sdlwin) {
        printf("Could not create window: %s\n", SDL_GetError());
    }

    sdl_renderer =SDL_CreateRenderer(sdlwin,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);


	glcontext = SDL_GL_CreateContext(sdlwin);
	window_id= SDL_GetWindowID( sdlwin ); 

    //renderer=new Scene();


}
void Window::winrun(){
	Window::run();
}
bool Window::run(){
	std::clock_t start;
	double duration;
	
	
	
	Panel::screenwidth=width;
	Panel::screenheight=height;
	
		
		if (SDL_GL_MakeCurrent(sdlwin,  glcontext)){
			std::cout << "'Window.cpp' Error: change glcontext failed\n";
		}

			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


			draw(0,0,0,0,width,height);
			
			//glFlush();
			duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			//std::cout<<"render: "<<duration<<"s\n";
			

			SDL_Event event;

			while (SDL_PollEvent(&event)){
				if (event.window.windowID == window_id){
					if(event.type == SDL_WINDOWEVENT){
							if ((event.window.event == SDL_WINDOWEVENT_CLOSE )&& closelistener && *closelistener){
									(*closelistener)(this);
							}
							if ((event.window.event == SDL_WINDOWEVENT_RESIZED )){
									width= event.window.data1;
									height= event.window.data2;
							}
							
							
					}else{
							handle_input(event,0,0,0,0,width,height,lastx,lasty);
					}
					//if (event.type==SDL_KEYDOWN)
					lastx=event.motion.x;
					lasty=event.motion.y;
				}
			}
			
		
		SDL_GL_SwapWindow(sdlwin);
		
		return Panel::run();

		
		
}

Window::~Window() {
	SDL_DestroyWindow(sdlwin );
	// TODO Auto-generated destructor stub
}

