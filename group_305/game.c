/** @file   maze.c
    @author Rohan Mathias & Zhenyuan He
    @date   13/10/2021

    @defgroup group_305 A game where you have to make your way through a maze
*/
#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include "../fonts/font5x7_1.h"

#include "system.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pacer.h"
#include "pio.h"
#include "timer.h"
#include "ledmat.h"
#include "player.h"
#include "map.h"


/* Define polling rate in Hz.  */
#define LOOP_RATE 500
#define MESSAGE_RATE 10
#define TIMER_CLOCK_DIVISOR 256
#define TIME_SET 2000

/* creates an enum for the finite state machine:
this encapsules all the states*/
typedef enum game_state
{
    GAME_NAME,
    GAME_MAP,
    GAME_RUN,
    GAME_WIN,
    GAME_LOSE,
    GAME_RUN_2,
    MAP_2,
    GAME_WIN_2,
    GAME_LOSE_2,    

} game_states_t;


/* initialises the  tinygl reading */
void screen_init(void)
{
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

}


void show_text(char* string) 
{
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text (string);
    uint8_t start = 0;
    while (start == 0)
    {
        pacer_wait ();
        tinygl_update ();
        if (PIND & (1<<7)) {
            start = 1;
        }
    }

}


int main (void)
{
    /* initialises all the parameters */
    system_init();
    ledmat_init();
    screen_init();
    navswitch_init();

    //button init
    DDRD &= ~(1<<7);
    //counter init
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;

    //uint16_t tick;
    pacer_init(LOOP_RATE);

    /*creates the person needed to move around*/
    person_t person = person_init();

    /* the two matrix of mazes for each level needed 
    to check whether the player has walked into the wall*/
    int maze1[7][5] = {{1,1,0,1,1}, 
                       {1,0,0,0,0},
                       {1,1,1,0,1},
                       {0,0,0,0,1},
                       {0,1,0,1,1},
                       {0,0,0,0,0},
                       {1,1,1,1,0}};

    int maze2[7][5] = {{0,1,0,0,1},
                       {0,0,0,1,0},
                       {1,0,1,1,0},
                       {1,0,0,0,0},
                       {0,0,1,1,1},
                       {0,1,0,0,0},
                       {0,0,0,1,0}};
    
    /*shows the opening screen text*/
    show_text("Mazes! Push to start");
    uint16_t time_set = TIME_SET;


    game_states_t game_state = GAME_NAME;
    while(1) 
    {
        pacer_wait();
        
        switch(game_state)
        {
            /*first state: opening screen of maze*/
            case GAME_NAME:
                pacer_wait();
                tinygl_update ();
                if (PIND & (1<<7)) {
                    game_state = GAME_MAP;
                    tinygl_clear();
                }
                break;

            /*displays the map of the first level*/
            case GAME_MAP:
              
                map_show(time_set);
                game_state = GAME_RUN;
                break;

            /*encapasules the code needed to check win/lose and operation of game*/
            case GAME_RUN:               
                navswitch_update ();
                tinygl_draw_point(person.pos, 0);

                person = move_person(person);

                tinygl_draw_point(person.pos, 1);
                tinygl_update ();

                if (person.pos.y == 0 && person.pos.x == 2 && navswitch_push_event_p(NAVSWITCH_PUSH)){ 
                    game_state = GAME_WIN;
                    person.pos.y = 6;
                    person.pos.x = 4;
                }
                if (maze1[person.pos.y][person.pos.x] == 1) {
                    game_state = GAME_LOSE;
                    person.pos.x = 4;
                    person.pos.y = 6;
                }
                break;

            /*code for if the person wins the first level*/
            case GAME_WIN:
                show_text("win: press to continue");
                navswitch_update();
                if (PIND & (1<<7)) {
                    game_state = MAP_2;
                    tinygl_clear();
                }
                break;

            /*code for if the person loses the first level*/
            case GAME_LOSE:
                map_show(time_set);
                show_text("try again");
                if (PIND & (1<<7)) {
                    game_state = GAME_RUN;
                    tinygl_clear();
                }
                break;

            /*state to display the second level maze*/
            case MAP_2:
                map_show_2(time_set);
                game_state = GAME_RUN_2;
                break;
            
            /*state to run and check win/lose condition for second level*/
            case GAME_RUN_2:
                navswitch_update ();
                tinygl_draw_point(person.pos, 0);

                person = move_person(person);

                tinygl_draw_point(person.pos, 1);
                tinygl_update ();

                if (person.pos.y == 0 && person.pos.x == 2 && navswitch_push_event_p(NAVSWITCH_PUSH)){ 
                    game_state = GAME_WIN_2;
                    person.pos.y = 6;
                    person.pos.x = 4;
                }
                if (maze2[person.pos.y][person.pos.x] == 1) {
                    game_state = GAME_LOSE_2;
                    person.pos.y = 6;
                    person.pos.x = 4;
                }
                break;

            /*state for winning second level*/
            case GAME_WIN_2:
                show_text("WIN!!");
                if (PIND & (1<<7)) {
                    game_state = GAME_NAME;
                    tinygl_clear();
                }
                break;

            /*state for losing second level*/
            case GAME_LOSE_2:
                map_show_2(time_set);
                show_text("try again");
                if (PIND & (1<<7)) {
                    game_state = GAME_RUN_2;
                    tinygl_clear();
                }
                break;  
        }         
    }
    return (1);
}
