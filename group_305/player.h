/**  @file   player.h
     @author Rohan Mathias & Zhenyuan He
     @date   21/10/2021
     @brief  This creates a person(bit) able to move around the screen with the navswitch

*/

#ifndef PLAYER_H
#define PLAYER_H

#include "system.h"

/*Creates a person with attributes of current x and y coordinates */
struct person 
{

    tinygl_point_t pos;
};

typedef struct person person_t;

/* initialises a person */
person_t person_init(void);

/* function to update person position*/
person_t move_person(person_t person);

#endif
