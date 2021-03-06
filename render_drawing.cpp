/*
 * CS475/CS675 - Computer Graphics
 *  ToyLOGO Assignment Base Code
 *
 * Copyright 2009-2014, Parag Chaudhuri, Department of CSE, IIT Bombay
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "render_drawing.hpp"

void leaf(turtle_t &turt, double length);
void starline(turtle_t &turt, double length)
{
  double factor;
factor=length/1.5;
 if(length<=0.002)
   return;
 else{
turt.forward(factor);
turt.turn_right(30);
turt.forward(factor);
starline(turt,factor);
turt.backward_move(factor);
turt.turn_left(60);
turt.forward(factor);
starline(turt,factor);
turt.backward_move(factor);
turt.turn_right(30);
turt.backward_move(factor);

}
     
     
}

void leaf(turtle_t &turt, double length)
{
  double factor,i;
  
factor=length/10;
 if(factor<=0.005)
   return;
 else{
  
   for(i=2.0;i<=4.2;i=i+0.2){
turt.forward(factor);
turt.turn_right(45);
leaf(turt,4.2*factor/i);
turt.forward(4.8*factor/i);
turt.backward_move(4.8*factor/i);
turt.turn_left(45);
turt.forward(factor/6);
turt.turn_left(45);
leaf(turt,4.2*factor/i);
turt.forward(4.8*factor/i);
turt.backward_move(4.8*factor/i);

turt.turn_right(45.15);

   }
turt.forward(factor/8);
turt.backward_move(length+3*factor);


}
     
     
}

void star(turtle_t &turt, double x)
{
  int i;
  double factor=x/10;
   turt.reset();
   turt.clear();
  turt.set_pos(0.0, -0.95);
  
   turt.turn_left(90);
   starline(turt,x);
}

void leaffirst(turtle_t &turt, double x)
{
   turt.reset();
   turt.clear();
  turt.set_pos(0.0, -0.8);
  
 turt.turn_left(90);
       leaf(turt, x);
    
}

void render_drawing(turtle_t &turt)
{
 
  //star(turt,0.5);
  leaffirst(turt,1.0);
}
