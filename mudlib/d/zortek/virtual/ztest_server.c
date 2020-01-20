// v_server.c
// The virtual room server for TMI-2. This room is a direct copy of Truilkan's
// example ocean room. Two main differences are: 1) it is two-dimensional
// rather than three and 2) It has an attached terrain map which controls
// the room descriptions, causing it to have only finite size but more
// interesting rooms.
// August 1992 an exits map was added

#define BASE "/wizards/zortek/virtual/ztest/rooms/"
#define SUFFIX ".ztest"
#define MATRIX_DAEMON "/wizards/zortek/virtual/ztest_daemon.c"
#define MOBDIR "/wizards/zortek/canyon/mon/"
#define MOBCHANCE  50

#include <config.h>

inherit "/std/room" ;
inherit "/std/virtual/compile";

void virtual_setup(string arg)
{
    int x, y, i, wibble, cnt ;
    string north, south, east, west, mon_file ;
    object mon;

    room::create() ;
    sscanf(arg,"%d,%d",x,y) ;
    if(!arg) { x = 5; y = 5; }
    south = BASE + (x + 1) +  "," + y       + SUFFIX ;
    east = BASE + x       +  "," + (y + 1) + SUFFIX;
    north  = BASE + (x - 1) +  "," + y       + SUFFIX;
    west = BASE + x       +  "," + (y - 1) + SUFFIX;
    set("short", MATRIX_DAEMON->get_short(x,y));
    set("day long", MATRIX_DAEMON->get_day_long(x,y));
    set("night long", MATRIX_DAEMON->get_night_long(x,y));
    set_property("light", MATRIX_DAEMON->get_lite(x,y));
    set_property("night light", (int)MATRIX_DAEMON->get_lite(x,y)-2);
    set_exits( ({ 
               }),({ 
               }) );
    i = MATRIX_DAEMON->get_exits(x,y) ;
    if (!(i%2)) add_exit(west, "west");
    if (!((i/2)%2)) add_exit(east, "east");
    if (!((i/4)%2)) add_exit(south, "south");
    if (!((i/8)%2)) add_exit(north, "north");
    if(random(100) > MOBCHANCE) {
      mon_file = (string)MATRIX_DAEMON->get_mob(x,y);
      if ( mon_file ) {
        switch(mon_file) {
          case "A":
            cnt = random(8)+5;
            while(cnt--) {
            mon = new(MOBDIR+"mane.c");
            if(objectp(mon)) {
              switch(random(4)) {
                case 0: 
                  mon->set_short("Plebian Mane");
                  mon->set_level(random(3)+8);
                  break;
                case 1: 
                  mon->set_short("Servant Mane");
                  mon->set_level(random(3)+10);
                  break;
                case 2: 
                  mon->set_short("Courier Mane");
                  mon->set_level(random(3)+12);
                  break;
                case 3: 
                  mon->set_short("Patrol Mane");
                  mon->set_level(random(3)+14);
                  break;
                default:
              }
            }
            if(objectp(mon))
              mon->move(this_object());
            }
            break;
          case "B":
            cnt = random(8)+5;
            while(cnt--) {
            mon = new(MOBDIR+"lemure.c");
            if(objectp(mon)) {
              switch(random(4)) {
                case 0: 
                  mon->set_short("Serf Lemure");
                  mon->set_level(random(5)+10);
                  break;
                case 1: 
                  mon->set_short("Slothful Lemure");
                  mon->set_level(random(5)+12);
                  break;
                case 2: 
                  mon->set_short("Mumbling Lemure");
                  mon->set_level(random(5)+15);
                  break;
                case 3: 
                  mon->set_short("Patrol Lemure");
                  mon->set_level(random(5)+18);
                  break;
                default:
              }
            }
            if(objectp(mon))
              mon->move(this_object());
            }
            break;
          case "C":
            cnt = random(8)+5;
            while(cnt--) {
            mon = new(MOBDIR+"bone.c");
            if(objectp(mon)) {
              switch(random(4)) {
                case 0: 
                  mon->set_short("Soldier Bone Devil");
                  mon->set_level(random(5)+15);
                  break;
                case 1: 
                  mon->set_short("Mercenary Bone Devil");
                  mon->set_level(random(5)+17);
                  break;
                case 2: 
                  mon->set_short("Hero Bone Devil");
                  mon->set_level(random(5)+19);
                  break;
                case 3: 
                  mon->set_short("Champion Bone Devil");
                  mon->set_level(random(5)+21);
                  break;
                default:
              }
            }
            if(objectp(mon))
              mon->move(this_object());
            }
            break;
          case "D":
            cnt = random(8)+5;
            while(cnt--) {
            mon = new(MOBDIR+"f_mephit.c");
            if(objectp(mon)) {
              switch(random(4)) {
                case 0: 
                  mon->set_short("Flaming Mephit Guard");
                  mon->set_level(random(5)+10);
                  break;
                case 1: 
                  mon->set_short("Flaming Mephit Soldier");
                  mon->set_level(random(5)+12);
                  break;
                case 2: 
                  mon->set_short("Flaming Mephit Hero");
                  mon->set_level(random(5)+14);
                  break;
                case 3: 
                  mon->set_short("Flaming Mephit Champion");
                  mon->set_level(random(5)+16);
                  break;
                default:
              }
            }
            if(objectp(mon))
              mon->move(this_object());
            }
            break;
          case "E":
            cnt = random(8)+5;
            while(cnt--) {
            mon = new(MOBDIR+"sm_mephit.c");
            if(objectp(mon)) {
              switch(random(4)) {
                case 0: 
                  mon->set_short("Smokey Mephit Guard");
                  mon->set_level(random(5)+10);
                  break;
                case 1: 
                  mon->set_short("Smokey Mephit Soldier");
                  mon->set_level(random(5)+12);
                  break;
                case 2: 
                  mon->set_short("Smokey Mephit Hero");
                  mon->set_level(random(5)+14);
                  break;
                case 3: 
                  mon->set_short("Smokey Mephit Champion");
                  mon->set_level(random(5)+16);
                  break;
                default:
              }
            }
            if(objectp(mon))
              mon->move(this_object());
            }
            break;
          case "F":
            cnt = random(8)+5;
            while(cnt--) {
            mon = new(MOBDIR+"l_mephit.c");
            if(objectp(mon)) {
              switch(random(4)) {
                case 0: 
                  mon->set_short("Lava Mephit Guard");
                  mon->set_level(random(5)+10);
                  break;
                case 1: 
                  mon->set_short("Lava Mephit Soldier");
                  mon->set_level(random(5)+12);
                  break;
                case 2: 
                  mon->set_short("Lava Mephit Hero");
                  mon->set_level(random(5)+14);
                  break;
                case 3: 
                  mon->set_short("Lava Mephit Champion");
                  mon->set_level(random(5)+16);
                  break;
                default:
              }
            }
            if(objectp(mon))
              mon->move(this_object());
            }
            break;
          case "G":
            cnt = random(8)+5;
            while(cnt--) {
            mon = new(MOBDIR+"st_mephit.c");
            if(objectp(mon)) {
              switch(random(4)) {
                case 0: 
                  mon->set_short("Steam Mephit Guard");
                  mon->set_level(random(5)+10);
                  break;
                case 1: 
                  mon->set_short("Steam Mephit Soldier");
                  mon->set_level(random(5)+12);
                  break;
                case 2: 
                  mon->set_short("Steam Mephit Hero");
                  mon->set_level(random(5)+14);
                  break;
                case 3: 
                  mon->set_short("Steam Mephit Champion");
                  mon->set_level(random(5)+16);
                  break;
                default:
              }
            }
            if(objectp(mon))
              mon->move(this_object());
            }
            break;
          case "H":
            mon = new(MOBDIR+"damned_soul.c");
            if(objectp(mon))
              mon->move(this_object());
            break;
          default:
        }
      }
    }
}
