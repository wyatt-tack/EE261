typedef struct dms
	{
	int degrees;
	int minutes;
	int seconds;
	} Coord;

typedef struct point
	{
	Coord Latitude;
	Coord Longitude;
	} Location;

const char WANTED_RECORD[] = ":=";
//const char WANTED_CALLSIGN[]="K6CMG-7";
//const char WANTED_CALLSIGN[]="KN6LHP-10";
const char WANTED_CALLSIGN[] = "KC6YIR-1";
