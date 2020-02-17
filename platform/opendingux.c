/*
 * Hocoslamfy, OpenDingux platform-specific code file
 * Copyright (C) 2014 Nebuleon Fumika <nebuleon@gcw-zero.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <stdbool.h>
#include <stdint.h>

#include "SDL.h"

#include "platform.h"

void InitializePlatform(void)
{
	Uint32 i;
    Uint32 joystick_count = SDL_NumJoysticks();
    printf("%d joysticks\n", joystick_count);
    
    if(joystick_count > 0)
    {
        for(i=0;i<joystick_count;i++)
        {
            SDL_JoystickOpen(i);
        }
        SDL_JoystickEventState(SDL_ENABLE);
    }
}

Uint32 ToNextFrame(void)
{
	// OpenDingux waits for vertical sync by itself.
	return 16;
}

bool IsEnterGamePressingEvent(const SDL_Event* event)
{
	return (event->type == SDL_KEYDOWN
	    && (event->key.keysym.sym == SDLK_LCTRL  /* A */
	     || event->key.keysym.sym == SDLK_RETURN /* Start */))
		 || (event->type == SDL_JOYBUTTONDOWN
	    && (event->jbutton.button == 1  /* A */
	     || event->jbutton.button == 9 /* Start */));
}

bool IsEnterGameReleasingEvent(const SDL_Event* event)
{
	return (event->type == SDL_KEYUP
	    && (event->key.keysym.sym == SDLK_LCTRL  /* A */
	     || event->key.keysym.sym == SDLK_RETURN /* Start */))
		 || (event->type == SDL_JOYBUTTONUP
	    && (event->jbutton.button == 1  /* A */
	     || event->jbutton.button == 9 /* Start */));		 
}

const char* GetEnterGamePrompt(void)
{
	return "A/Start";
}

bool IsExitGameEvent(const SDL_Event* event)
{
	return event->type == SDL_QUIT
	     || (event->type == SDL_KEYDOWN
	    && (event->key.keysym.sym == SDLK_LALT   /* B */
	     || event->key.keysym.sym == SDLK_ESCAPE /* Select */))
	     || (event->type == SDL_JOYBUTTONDOWN
	    && (event->jbutton.button == 2  /* B */
	     || event->jbutton.button == 8 /* Select */));	
}

const char* GetExitGamePrompt(void)
{
	return "B/Select";
}

bool IsBoostEvent(const SDL_Event* event)
{
	return (event->type == SDL_KEYDOWN
	    && (event->key.keysym.sym == SDLK_LCTRL  /* A */
	     || event->key.keysym.sym == SDLK_LALT   /* B */
	     || event->key.keysym.sym == SDLK_LSHIFT /* GCW Zero: X; Dingoo A320: Y */
	     || event->key.keysym.sym == SDLK_SPACE  /* GCW Zero: Y; Dingoo A320: X */))
	     || (event->type == SDL_JOYBUTTONDOWN
	    && (event->jbutton.button == 1  /* A */
	     || event->jbutton.button == 2 /* B */
	     || event->jbutton.button == 0 /* X */		 
	     || event->jbutton.button == 3 /* Y */));
}

const char* GetBoostPrompt(void)
{
	return "A/B/X/Y";
}

bool IsPauseEvent(const SDL_Event* event)
{
	return (event->type == SDL_KEYDOWN
	    && event->key.keysym.sym == SDLK_RETURN /* Start */)
	     || (event->type == SDL_JOYBUTTONDOWN
	    && event->jbutton.button == 9 /* Start */);	
}

bool IsScoreToggleEvent(const SDL_Event* event)
{
	return (event->type == SDL_KEYDOWN
	    && event->key.keysym.sym == SDLK_BACKSPACE) /* R */
	     || (event->type == SDL_JOYBUTTONDOWN
	    && event->jbutton.button == 5 /* R */);	
}

const char* GetScoreTogglePrompt(void)
{
	return "R1";
}

const char* GetPausePrompt(void)
{
	return "Start";
}
