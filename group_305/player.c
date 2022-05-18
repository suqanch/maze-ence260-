/** @file   player.c
    @author Rohan Mathias & Zhenyuan He
    @date   21/10/2021
    @brief player mover
    @note This encaplsules all the movement needed for the player
*/
#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

#include "system.h"
#include "navswitch.h"
#include "tinygl.h"
#include "player.h"


/* initialises a person in the correct position in the matrix */
person_t person_init(void)
{
    person_t person;
    person.pos.x = 4;
    person.pos.y = 6;
    return(person);
}


/* function to update person position*/
person_t move_person(person_t person)
{
    if (navswitch_push_event_p (NAVSWITCH_WEST) && person.pos.x > 0)
    {           
        person.pos.x = person.pos.x - 1;
    }

    else if (navswitch_push_event_p (NAVSWITCH_EAST) && person.pos.x < TINYGL_WIDTH-1)
    {  
        person.pos.x = person.pos.x + 1;
    }

    else if (navswitch_push_event_p (NAVSWITCH_SOUTH) && person.pos.y < TINYGL_HEIGHT-1)
    {  
        person.pos.y = person.pos.y + 1;
    }   

    else if (navswitch_push_event_p (NAVSWITCH_NORTH) && person.pos.y > 0)
    { 
        person.pos.y = person.pos.y - 1;
    }
    return(person); 
}

