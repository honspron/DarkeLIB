//    A virtual server for forged weapons.
//    The file is of the format: "<armour-name>.armour"
//    Weapon types are parsed from a text file /d/damned/data/armour_types
//
//    DarkeLIB 0.1
//    -Diewarzau 8/14/95

#include "/d/damned/virtual/virtual_table.h"
#include <std.h>

inherit "/std/virtual/compile";
inherit ARMOUR;

void virtual_setup(string arg);

void create() {
  seteuid(getuid(this_object()));
  ::create();
  return;
}

void virtual_setup(string arg) {
  object db;
  class v_table this_armour;
  int max, i;

  set_name(replace_string(arg, "-", " "));
  set("id", ({ query_name() }) );
  seteuid(getuid());
  db = load_object("/d/damned/data/armour_db");
  this_armour = (class v_table)db->get_table(arg);
  if(!this_armour) {
    error("Virtual armour type not found: \""+arg+"\"\n");
    return;
  }
  max = sizeof(this_armour->funcs);
  for(i=0;i<max;i++) {
    switch(sizeof(this_armour->args[i])) {
    case 0:
    default:
      call_other(this_object(), this_armour->funcs[i]);
      break;
    case 1:
      call_other(this_object(), this_armour->funcs[i],
        this_armour->args[i][0]);
      break;
    case 2:
      call_other(this_object(), this_armour->funcs[i],
        this_armour->args[i][0],
        this_armour->args[i][1]);
      break;
    case 3:
      call_other(this_object(), this_armour->funcs[i],
        this_armour->args[i][0],
        this_armour->args[i][1],
        this_armour->args[i][2]);
      break;
    case 4:
      call_other(this_object(), this_armour->funcs[i],
        this_armour->args[i][0],
        this_armour->args[i][1],
        this_armour->args[i][2],
        this_armour->args[i][3]);
      break;
    }
  }
  return;
}

