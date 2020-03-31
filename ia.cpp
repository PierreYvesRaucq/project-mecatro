#include "ia.h"
#include <stdio.h>
#include <stdlib.h>


void computecmd(CtrlStruct *theCtrlStruct, Map *mymap)
{
    switch(theCtrlStruct->theUserStruct->state)
    {

    case 0: //en calibration
    {
        calib(theCtrlStruct);
    }
    break;

    case 1: //action
    {
        nodeaction(theCtrlStruct, mymap);
    }
    break;

    case 2: //navigation
    {
        middle_controller(theCtrlStruct, mymap);
    }
    break;

    case 3: //test
    {
        //...
    }
    break;

    case 4: //potent field mode
    {
        avoid(theCtrlStruct, mymap);//cfr upobstacle_avoidance
    }

    default: //stop
    {
        theCtrlStruct->theUserStruct->wantedspeedl = 0;
        theCtrlStruct->theUserStruct->wantedspeedr = 0;
        //change_state(); //could be interresting to create a fct that check if the state has to be changed
    }
    break;
    }
}

void initpos(CtrlStruct *theCtrlStruct, int wallnb)
{
    if (wallnb == 1)
    {
        theCtrlStruct->theUserStruct->posxyt[0] = 0;//x = 0
        theCtrlStruct->theUserStruct->posxyt[2] = 0;//orientation = 0
    }
    else if (wallnb == 2)
    {
        theCtrlStruct->theUserStruct->posxyt[1] = 0;//y = 0
        theCtrlStruct->theUserStruct->posxyt[2] = M_PI/2;//orientation = 90
    }
    else if (wallnb == -1)
    {
        theCtrlStruct->theUserStruct->posxyt[0] = 0;//x = 0
        theCtrlStruct->theUserStruct->posxyt[2] = 0;//orientation = 0
    }
    else
    {
        theCtrlStruct->theUserStruct->posxyt[1] = 2000;//y = 2000
        theCtrlStruct->theUserStruct->posxyt[2] = M_PI/2;//orientation = 90
    }
}

void middle_controller(CtrlStruct *structure, Map *mymap)
{
    double dest[2];
    dest[0] = mymap->node[mymap->mypath->obj[mymap->mypath->dest_lnb]][0];
    dest[1] = mymap->node[mymap->mypath->obj[mymap->mypath->dest_lnb]][1];
    dest[2] = mymap->node[mymap->mypath->obj[mymap->mypath->dest_lnb]][2];
    //optimisation : ne doit pas être updatet tout le temps
    //should test if dest still exist

    double deltax = structure->theUserStruct->posxyt[0] - objpos[0];
    double deltay = structure->theUserStruct->posxyt[1] - objpos[1];
    double dist = sqrt(pow(deltax, 2)+pow(deltay,2));
    double diagangle = atan(((structure->theUserStruct->posxyt[1])-objpos[1])/((structure->theUserStruct->posxyt[0])-objpos[0]));//vérif angle < 0
    double diffangle = diagangle - (structure->theUserStruct->posxyt[2]);

    //moving state orientation ?
    if (fabs(diffangle) > M_PI/6 || fabs(dist) < 0.05) //needs to be reoriented (if on obj pos or too desoriented)
        structure->theUserStruct->action_state = 1;

    //apply
    if (structure->theUserStruct->action_state == 1)//mode orientation
    {
        rot(structure, diffangle);
        if (fabs(diffangle) < M_PI/20) //orientation almost perfect
        {
            if (fabs(dist) < 0.05)
            {
                structure->theUserStruct->action_state = 0;//end of the action should be resetted
                mymap->mypath->dest_lnb++;
                structure->theUserStruct->state = 1;//passer en mode action
            }
            else
                structure->theUserStruct->action_state = 0;//passer en mode déplacement (+-) rectiligne
        }
    }
    else
    {
        double centerangle = M_PI - (M_PI_2 - diffangle)*2; //triangle isocele
        double curv_radius = dist/(sin(centerangle/2))*2;//to be verified
        structure->theUserStruct->wantedspeedl = dist*KL*(curv_radius+WIDTH)/curv_radius;//to be verified (<0 ? if dist <0 ?)
        structure->theUserStruct->wantedspeedr = dist*KL*(curv_radius-WIDTH)/curv_radius;
    }
}

void rot(CtrlStruct *structure, double angle)
{
    structure->theUserStruct->wantedspeedl = KR*angle;
    structure->theUserStruct->wantedspeedr = -KR*angle;
}

void calib(CtrlStruct *theCtrlStruct)
{
    switch(theCtrlStruct->theUserStruct->action_state)
    {
    case 0: // goback
    {
        theCtrlStruct->theUserStruct->wantedspeedl = -10; //vitesse a determiner
        theCtrlStruct->theUserStruct->wantedspeedr = -10; //vitesse a determiner

        if (theCtrlStruct->theCtrlIn->u_switch[0])
        {
            theCtrlStruct->theUserStruct->wantedspeedr = 0;

            if (theCtrlStruct->theCtrlIn->u_switch[1])
            {
                theCtrlStruct->theUserStruct->wantedspeedl = 0;
                initpos(theCtrlStruct, theCtrlStruct->theUserStruct->side);
                theCtrlStruct->theUserStruct->action_state = 1;
            }
        }
    }
    case 1 : //goforward
    {
        theCtrlStruct->theUserStruct->wantedspeedl = 10; //a definir
        theCtrlStruct->theUserStruct->wantedspeedr = 10; //a definir

        if (theCtrlStruct->theUserStruct->posxyt[0] >= 50) //a definir verif posx or posy
        {
            theCtrlStruct->theUserStruct->wantedspeedl = 0;
            theCtrlStruct->theUserStruct->wantedspeedl = 0;
            //setPos (50)
            theCtrlStruct->theUserStruct->action_state = 2;
        }
    }

    case 2 : //turn
    {
        theCtrlStruct->theUserStruct->wantedspeedl = 10*theCtrlStruct->theUserStruct->side; //a definir
        theCtrlStruct->theUserStruct->wantedspeedr = -10*theCtrlStruct->theUserStruct->side; //a definir
        if (theCtrlStruct->theUserStruct->posxyt[2] >= M_PI/2)
        {
            theCtrlStruct->theUserStruct->wantedspeedl = 0;
            theCtrlStruct->theUserStruct->wantedspeedr = 0;
            theCtrlStruct->theUserStruct->action_state = 3;
        }
    }
    case 3: //goback
    {
        theCtrlStruct->theUserStruct->wantedspeedl = -10; //a definir
        theCtrlStruct->theUserStruct->wantedspeedr = -10; //a definir

        if (theCtrlStruct->theCtrlIn->u_switch[0])
        {
            theCtrlStruct->theUserStruct->wantedspeedr = 0;

            if (theCtrlStruct->theCtrlIn->u_switch[1])
            {
                theCtrlStruct->theUserStruct->wantedspeedl = 0;
                initpos(theCtrlStruct, 2*theCtrlStruct->theUserStruct->side);
                theCtrlStruct->theUserStruct->action_state = 4;
            }
        }
    }
    case 4 : //goforward
    {
        theCtrlStruct->theUserStruct->wantedspeedl = 10; //a definir
        theCtrlStruct->theUserStruct->wantedspeedr = 10; //a definir
        if (theCtrlStruct->theUserStruct->posxyt[0] >= 50) //verif if posx ou posy
        {
            theCtrlStruct->theUserStruct->wantedspeedl = 0;
            theCtrlStruct->theUserStruct->wantedspeedl = 0;
            theCtrlStruct->theUserStruct->action_state = 0;
            theCtrlStruct->theUserStruct->state = 10;
        }
    }
    }
}

void nodeaction(CtrlStruct *theCtrlStruct, Map *mymap)
{
    switch (mymap->mypath->objnb)
    {
    case 0 :
    {
        //...
    }
    break;
    case 1:
    {
        //...
    }
    break;
    default : //if no action is needed
    {
        mymap->mypath->visited[mymap->mypath->actual_node];
        mymap->mypath->objnb++;//go to next obj
        theCtrlStruct->theUserStruct->state = 2;//in navigation mode
    }
    break;
    }
}
