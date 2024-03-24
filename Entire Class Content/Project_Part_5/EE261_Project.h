#ifndef EE261_PROJECT_H_INCLUDED
#define EE261_PROJECT_H_INCLUDED

typedef struct dms{
int degrees;
int minutes;
int seconds;
}Coord;

typedef struct point{
Coord Latitude;
Coord Longitude;
} Location;


#endif // EE261_PROJECT_H_INCLUDED
