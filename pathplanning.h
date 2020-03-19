#ifndef PATHPLANNING_H_INCLUDED
#define PATHPLANNING_H_INCLUDED

#include<stdio.h>
#include <stdlib.h>
#include "struct.h"

#define N 8 //number of node

typedef struct Path{
    int nbNodeNotVisited;
    int visited[N];//1 if the node number i has been visited, 0 if not
    int obj[N];//list of node to follow from the actual nodes towards node 0
    double totalPoints;//number of point expected with this path
    double timeleft;//[s]
    int actual_node;//where you are (physically or in simulation calculation)
    int objnb;//number of obj already passed (or added to the path for calculation)
} Path;


typedef struct Map //contient la carte + le path
{
    double dist[N][N];//tableau des dist entre noeuds (en temps) !!! il faut que tous les noeuds puissent retourner � la base de fa�on rectiligne (� priori pas de probl�me vu la map), base = node 0
    double node[N][5];//[0]: position x, [1]: position y, [2]: needed orientation (infinity if no orientation needed), [3]: nb de points qu'il y moy de se faire � ce noeudnoeud, [4]: cout de l'action (tps)
    int step;
    Path* mypath;
} Map;

void initpath (Map* mymap);
void adaptpath(Map* mymap);
void pathplanning(Map* mymap, Path* mypath);
Map* initmap();
void readmap(Map* mymap);


#endif // PATHPLANNING_H_INCLUDED
