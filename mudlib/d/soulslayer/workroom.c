//      from the Nightmare mudlib
//      an example workroom for new immortals

#include <std.h>

inherit ROOM;

void create() {
    ::create();
    
    // 5 to -5
    set_property("light", 1);
    set_property("indoors", 1);

    set("short", "Soulslayer's Room");
    set("night long", "It is night outside! May the powers of Evil rejoice.\n");
    set("day long", "It is day outside, how disgusting.. go to bed.\n");

    set_exits( ([
    	"square" : "/d/standard/square",
    	"hall"   : "/d/standard/adv_main",
    	"sl"     : "/wizards/soulslayer/shadowlands/entrance"
    ]));

    set_listen("default", "You hear the distant screams of innocent people echoing throughout the lands and smile contentedly to yourself- looks like it is going to be a good day.");
}

void reset() {
    ::reset();
    if( !present("concubine") )
        new("/wizards/soulslayer/concubine")->move(this_object());
}

string *query_obvious_exits()
{
    string *exits, *sorties;
    int i;

    sorties = query_exits();
    if(!sorties) return ({});
    else i = sizeof(sorties);
    exits = ({});
    while(i--)
      if(!invis_exit(sorties[i])) {
// Need dark_vision or ?light? AND detect invis/magic to see entrance
          if( strcmp(sorties[i], "sl") == 0 ) {
              if( strcmp(this_player()->query_cap_name(), "Soulslayer") == 0 )
                  exits += ({ sorties[i] });
          }
          else
              exits += ({ sorties[i] });
      }
    return (exits);
}

void init() {
    ::init();
}

