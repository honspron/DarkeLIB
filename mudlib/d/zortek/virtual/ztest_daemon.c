// terrain_daemon.c
// This file reads in the map of TMI-2's terrain and the accompanying
// descriptions. It defines two procedures which take a pair of integers
// and return the short and long description of the room at the x,y
// coordinates passed. It runs as a daemon, and it will load the first
// time it's called. Written by Mobydick@TMI in July 1992, to interact
// with a modified version of the virtual room server written by Truilkan
// and Whiplash. Added the exits function and corrected a bug in the
// terrain reader

#define COLUMNS  8
#define ROWS     15
#define NUMDESCS 32
#define DOMAIN      "/wizards/zortek/virtual/ztest/"
#define TERRAINFILE "ztest.terrain"
#define DESCFILE    "ztest.descs"
#define EXITFILE    "ztest.exits"
#define LITEFILE    "ztest.lite"
#define MOBFILE     "ztest.mob"

mixed *terrain ;
string *descs, *day_descs, *night_descs ;
mixed *exits ;
mixed *lite ;
mixed *mobs;

void create() {
  int i ;
  string str, str2 ;

  seteuid(getuid()) ;
  terrain = allocate(ROWS) ;
  exits = allocate(ROWS) ;
  descs = allocate(NUMDESCS) ;
  day_descs = allocate(NUMDESCS) ;
  night_descs = allocate(NUMDESCS) ;
  lite = allocate(ROWS) ;
  mobs = allocate(ROWS) ;

  for (i=0 ; i<ROWS ; i++) {
    str = read_file (DOMAIN+TERRAINFILE,i+1,1) ;
    sscanf (str,"%s\n",str2) ;
    terrain[i] = explode (str2," ") ;
  }
  for (i=0 ; i<ROWS ; i++) {
    str = read_file (DOMAIN+EXITFILE,i+1,1) ;
    sscanf(str,"%s\n",str2) ;
    exits[i] = explode (str2," ") ;
  }
  for (i=0 ; i<ROWS ; i++) {
    str = read_file (DOMAIN+LITEFILE,i+1,1) ;
    sscanf(str,"%s\n",str2) ;
    lite[i] = explode (str2," ") ;
  }
  for (i=0 ; i<NUMDESCS ; i++) {
    str = read_file(DOMAIN+DESCFILE,i*3+1,1) ;
    sscanf(str,"%s\n",descs[i]) ;
    day_descs[i] = read_file(DOMAIN+DESCFILE,i*3+2,1) ;
    night_descs[i] = read_file(DOMAIN+DESCFILE,i*3+3,1) ;

  }
  for (i=0 ; i<ROWS ; i++) {
    str = read_file (DOMAIN+MOBFILE,i+1,1) ;
    sscanf(str,"%s\n",str2) ;
    mobs[i] = explode (str2," ") ;
  }
}

string get_short(int x, int y) {
  int i ;

  sscanf(terrain[x][y],"%d",i) ;
  return descs[i] ;
}

string get_day_long(int x, int y) {
  int i ;

  sscanf(terrain[x][y],"%d",i) ;
  return day_descs[i] ;
}

string get_night_long(int x, int y) {
  int i ;

  sscanf(terrain[x][y],"%d",i) ;
  return night_descs[i] ;
}

int get_exits(int x, int y) {
  int i ;

  sscanf(exits[x][y],"%d",i) ;
  return i ;
}

int get_lite(int x, int y) {
  int i;

  sscanf(lite[x][y], "%d",i) ;
  return i ;
}

string get_mob(int x, int y) {
  string i;
  sscanf(mobs[x][y], "%s",i) ;
  return i;
}
