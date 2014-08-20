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


#include <cmath>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <GL/glew.h>

//#include <chrono.h>
//#include <thread.h>

#include "turtle.hpp"



void turtle_t::reset(void) 
{ 
  dir=0.0;
  pos.x=0.0;
  pos.y=0.0;
  
}

void turtle_t::clear(void)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
}

void turtle_t::set_pos(const vertex_t _pos)
{ 
  pos=_pos;
  
}

void turtle_t::set_pos(const double _x, const double _y)
{ 
  pos.x=_x;
  pos.y=_y;
}

void turtle_t::set_dir(const double _dir)
{ 
  dir=_dir;
}

void turtle_t::set_col(const color_t _col)
{ 
  col=_col; 
}

void turtle_t::set_col(const double _r, const double _g, const double _b)
{ 
  col.r=_r;
  col.g=_g;
  col.b=_b;

}

void turtle_t::set_bgcol(const double _r, const double _g, const double _b)
{
  glClearColor(_r,_g,_b,1.0);
 }

void turtle_t::scale(const double _s)
{ glLoadIdentity(); 
  glScaled(1/_s,1/_s,1.0d);
  
}

void turtle_t::turn_left(const double _angle)    
{
 
   dir=fmod(dir+_angle,360);

 }

void turtle_t::turn_right(const double _angle)
{
  dir=fmod(dir-_angle,360);
  if(dir<0)
    dir=dir+360;
 
 }

void turtle_t::forward(const double _dist)  
{
double new_x,new_y,result;
result =dir*(M_PI/180);
new_x=pos.x+(_dist*cos(result));
new_y=pos.y+(_dist*sin(result));
  glBegin(GL_LINES);
  glVertex2f(pos.x,pos.y);
  glVertex2f(new_x,new_y);
  glEnd();
pos.x=new_x;
pos.y=new_y;
}

void turtle_t::back(const double _dist)   
{ 
double new_x,new_y,new_angle,result;
   new_angle=fmod(dir+180,360);
result =new_angle*(M_PI/180);
new_x=pos.x+(_dist*cos(result));
new_y=pos.y+(_dist*sin(result));
  glBegin(GL_LINES);
  glVertex2f(pos.x,pos.y);
  glVertex2f(new_x,new_y);
  glEnd();
pos.x=new_x;
pos.y=new_y;
  
}

void turtle_t::forward_move(const double _dist)
{ 
double new_x,new_y,result;
result =dir*(M_PI/180);
pos.x=pos.x+(_dist*cos(result));
pos.y=pos.y+(_dist*sin(result));
}

void turtle_t::backward_move(const double _dist)
{
double new_x,new_y,new_angle,result;
 new_angle=fmod(dir+180,360);
result =new_angle*(M_PI/180);
pos.x=pos.x+(_dist*cos(result));
pos.y=pos.y+(_dist*sin(result));
  
}


void turtle_t::repeat(const unsigned int &_n, const turtle_com_list_t &_replist)
{
turtle_com_list_t::iterator liter1;
turtle_com_list_t replist=_replist;
int times=_n;

while(times>0){
      for( liter1 = replist.begin(); liter1!=replist.end(); liter1++)
	{
	  exec(*liter1);
	}
  times--;
}
}

void turtle_t::pause(const double _t)
{ 
  //glLoadIdentity(); 
 // glScaled(1/_t,1/_t,1.0d);
 // std::cout<<"hi";
 usleep(1000000);
 
}
void turtle_t::exec(turtle_com_t *com)
{
  if (com->cname==F)
    {
      turtle_fwd_t* fcom = dynamic_cast<turtle_fwd_t*>(com);
      if (fcom) forward(fcom->dist);
    }
  else if (com->cname==B)
    {
      turtle_bck_t* bcom = dynamic_cast<turtle_bck_t*>(com);
      if (bcom) back(bcom->dist);
    }
  else if (com->cname==L)
    {
      turtle_lft_t* lcom = dynamic_cast<turtle_lft_t*>(com);
      if (lcom) turn_left(lcom->angl);
    }
  else if (com->cname==R)
    {
      turtle_rht_t* rcom = dynamic_cast<turtle_rht_t*>(com);
      if (rcom) turn_right(rcom->angl);
    }
  else if (com->cname==MF)
    {
      turtle_mfwd_t* mfcom = dynamic_cast<turtle_mfwd_t*>(com);
      if (mfcom) forward_move(mfcom->dist);
    }
  else if (com->cname==MB)
    {
      turtle_mbck_t* mbcom = dynamic_cast<turtle_mbck_t*>(com);
      if (mbcom) backward_move(mbcom->dist);
    }
  else if (com->cname==CLS)
    {
      turtle_cls_t* clscom = dynamic_cast<turtle_cls_t*>(com);
      if (clscom) clear();
    }
  else if (com->cname==RESET)
    {
      turtle_rst_t* rstcom = dynamic_cast<turtle_rst_t*>(com);
      if (rstcom) reset();
    }
  else if (com->cname==COL)
    {
      turtle_col_t* colcom = dynamic_cast<turtle_col_t*>(com);
      if (colcom) set_col(colcom->r, colcom->g, colcom->b);
    }
  else if (com->cname==BGCOL)
    {
      turtle_bgcol_t* bgcolcom = dynamic_cast<turtle_bgcol_t*>(com);
      if (bgcolcom) set_bgcol(bgcolcom->r, bgcolcom->g, bgcolcom->b);
    }
  else if (com->cname==SCALE)
    {
      turtle_scale_t* scalecom = dynamic_cast<turtle_scale_t*>(com);
      if (scalecom) scale(scalecom->s);
    }
  else if (com->cname==REPEAT)
    {
      turtle_rep_t *repcom = dynamic_cast<turtle_rep_t*>(com);

      if (repcom)
	{
	  unsigned int times = repcom->times;
	  turtle_com_list_t sublist = repcom->replist;
	  repeat(times, sublist);
	}
     }
  else if ((com->cname==ENDREP) || (com->cname==END) || (com->cname==BEGIN)) 
    {
      //These commands are place holders and used for program structure
      //But no execution is necessary - generate a NoOP
      ;
    }
   else if ((com->cname==PAUSE)) 
    {
       turtle_pause_t *pausecom = dynamic_cast<turtle_pause_t*>(com);
       if(pausecom)
	 pause(pausecom->t);
    }
  else
    {
      std::cerr<<"Unknown Command: Ignoring"<<std::endl;
      exit(-1);
    }
}

