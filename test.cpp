#include "pathplanning.h"

void pathplanning(Map* mymap, Path* mypath)//return an object Path with the best path and total expected points in it (most of the rest variable are unusable/false)
{
    if (mypath->nbNodeNotVisited >= 1)
    {
        for(int i=1; i< N; i++)//test all nodes (could be smarter !!!)
        {
            if (mypath->visited[i] == 0 && (mymap->dist[mypath->actual_node][i] + mymap->dist[0][i]+ mymap->node[i][4]) < mypath->timeleft)//si le noeud n'a pas encore été visité et est atteignable à temps => si tps d'aller au noeud + tps d'action au noeud + temps de retour à la base est < temps restant
            {
                printf("chemin possible allons-y, new path created from node %d", i);
                Path newpath = *mypath;//créer nouveau path avec même intérieur que mypath
                Path* pnewpath = &newpath;//adresse de newpath

                pnewpath->timeleft = pnewpath->timeleft - (mymap->dist[0][i]+ mymap->node[i][4]); //timeleft update
                pnewpath->totalPoints = pnewpath->totalPoints + mymap->node[i][3]; //point number update
                pnewpath->actual_node = i;//actual node for simulation
                pnewpath->visited[i] = 1;//set analysing node as visited
                pnewpath->obj[pnewpath->objnb] = i;//node added to the path obj list
                pnewpath->objnb++;
                pnewpath->nbNodeNotVisited--;

                pathplanning(mymap, pnewpath)
            }
        }
    }
    else
    {
        printf("end of line\n");
        if (mymap->mypath->totalPoints < pnewpath->totalPoints || (mymap->mypath->totalPoints == pnewpath->totalPoints && mymap->mypath->timeleft < pnewpath->timeleft)) //to be changed
        {
            mymap->mypath->totalPoints = pnewpath->totalPoints;
            mymap->mypath->timeleft = pnewpath->timeleft;
            for(int i = 0; i < N-1; i++)
                mymap->mypath->obj[i] = pnewpath->obj[i];
            printf("\npath updated !!!!!\n");
        }
    }
}
