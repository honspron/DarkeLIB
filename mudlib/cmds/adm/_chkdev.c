//    Command for adjusting dev and generally keeping game

//    balance.

//    DarkeLIB 1.0

//    -Diewarzau 1/14/95



#define TEMP "/open/chktemp"

#define DIR_SKILLS "/std/skills"

#define DIR_SPELLS "/std/spells"

#include <security.h>



int dev, fast_dev;

string *lines;



int read_skill(string file);

int read_spell(string file);

void write_skill(string file);

void write_spell(string file);



void write_skill(string file) {

  int i;

  

  seteuid(UID_ROOT);

  if(file_exists(DIR_SKILLS+"/"+file))

    rm(DIR_SKILLS+"/"+file);

  for(i = 0; i<sizeof(lines); i++) {

    if(replace_string(lines[i], "set_dev_cost", "") !=

      lines[i])

      lines[i] = sprintf("    set_dev_cost(%d);", dev);

    else if(replace_string(lines[i], "set_fast_dev_cost", "") !=

        lines[i])

      lines[i] = sprintf("    set_fast_dev_cost(%d);", fast_dev);

    write_file(DIR_SKILLS+"/"+file, lines[i] + "\n");

  }

  seteuid(getuid());

  return;

}



void write_spell(string file) {

  int i;

  

  seteuid(UID_ROOT);

  if(file_exists(DIR_SPELLS+"/"+file))

    rm(DIR_SPELLS+"/"+file);

  for(i = 0; i<sizeof(lines); i++) {

    if(replace_string(lines[i], "\"dev cost\"", "") !=

      lines[i])

      lines[i] = sprintf("    set_property(\"dev cost\", %d);", dev);

    else if(replace_string(lines[i], "\"fast dev cost\"", "") !=

        lines[i])

      lines[i] = sprintf("    set_property(\"fast dev cost\", %d);", fast_dev);

    write_file(DIR_SPELLS+"/"+file, lines[i] + "\n");

  }

  seteuid(getuid());

  return;

}



int read_skill(string file) {

  int i;

  int flag;

  

  lines = explode(read_file(DIR_SKILLS + "/" + file), "\n");

  i = sizeof(lines);

  dev = 0;

  fast_dev = 0;

  flag = 0;

  while(i--) {

    if(flag >= 2) continue;

    if(sscanf(lines[i], "%*sset_dev_cost(%d)%*s", dev) == 3) {

      flag++;

      continue;

    }

    if(sscanf(lines[i], "%*sset_fast_dev_cost(%d)%*s", fast_dev) == 3)

      flag++;

  }

  if(!dev && !fast_dev) return 0;

  printf(capitalize(replace_string(file, ".c", "")) +

    sprintf(" [%d / %d]: ", dev, fast_dev));

  return 1;

}



int read_spell(string file) {

  int i, flag, lev;

  object sp_ob;

  

  lines = explode(read_file(DIR_SPELLS + "/" + file), "\n");

  i = sizeof(lines);

  dev = 0;

  fast_dev = 0;

  flag = 0;

  sp_ob = find_object_or_load(DIR_SPELLS + "/" + replace_string(file, ".c", ""));

  lev = (int)sp_ob->query_property("spell level");

  while(i--) {

    if(flag >= 2) continue;

    if(sscanf(lines[i], "%*sset_property(\"dev cost\",%d)%*s", dev) == 3) {

      flag++;

      continue;

    }

    if(sscanf(lines[i], "%*sset_property(\"fast dev cost\",%d)%*s", fast_dev) == 3)

      flag++;

  }

  if(!dev && !fast_dev) return 0;

  printf(capitalize(replace_string(file, ".c", "")) +

    sprintf(", level %d [%d / %d]: ", lev, dev, fast_dev));

  return 1;

}



cmd_chkdev(string str) {

  string *dir;



  seteuid(getuid());

  if(str == "skills") {

    dir = get_dir(DIR_SKILLS + "/*.c");

    if(sizeof(dir) <= 1) {

      write("There are no skills!");

      return 1;

    }

    dir -= ({ "skill.c" });

    while(sizeof(dir) && !read_skill(dir[0]))

      dir = exclude_array(dir, 0);

    write("Enter 'abort' to stop.");

    input_to("adj_skill", 0, dir);

    return 1;

  } else if(str == "spells") {

    dir = get_dir(DIR_SPELLS + "/*.c");

    if(sizeof(dir) <= 1) {

      write("There are no spells!");

      return 1;

    }

    dir -= ({ "spell.c" });

    write("Enter 'abort' to stop.");

    while(sizeof(dir) && !read_spell(dir[0]))

      dir = exclude_array(dir, 0);

    input_to("adj_spell", 0, dir);

    return 1;

  }

  write("Usage: 'chkdev skills' or 'chkdev spells'.");

  return 1;

}



int help() {

  message("help",

  "This command has two uses: 'chkdev skills' and 'chkdev spells'.\n"

  "When invoked, it will go through all of the spells or skills, and "

  "ask for a new dev and fast dev cost.  To keep the old one, press enter.  "

  "To change it, type the new dev and fast dev costs, separated by a comma.",

  this_player());

  return 1;

}





void adj_skill(string str, string *dir) {

  string *lines;

  int i;

  

  if(str == "abort" || !sizeof(dir) || !dir) {

    write("Done updating!");

    return 1;

  }

  if(!str || !stringp(str) || !strlen(str)) {

    write_skill(dir[0]);

    dir = exclude_array(dir, 0);

    while(sizeof(dir) && !read_skill(dir[0]))

      dir = exclude_array(dir, 0);

    input_to("adj_skill", 0, dir);

    return;

  }

  else {

    if(sscanf(str, "%d,%d", dev, fast_dev) != 2) {

      write("Input the new dev and fast dev separated by a comma.\n"

           "Press enter for default.");

      read_file(dir[0]);

      input_to("adj_skill", 0, dir);

      return;

    }

    write("Skill updated.");

    write_skill(dir[0]);

    dir = exclude_array(dir, 0);

    while(sizeof(dir) && !read_skill(dir[0]))

      dir = exclude_array(dir, 0);

    input_to("adj_skill", 0, dir);

    return;

  }

  return;

}



void adj_spell(string str, string *dir) {

  string *lines;

  int i;

  

  if(str == "abort" || !sizeof(dir) || !dir) {

    write("Done updating!");

    return 1;

  }

  if(!str || !stringp(str) || !strlen(str)) {

    write_spell(dir[0]);

    dir = exclude_array(dir, 0);

    while(sizeof(dir) && !read_spell(dir[0]))

      dir = exclude_array(dir, 0);

    input_to("adj_spell", 0, dir);

    return;

  }

  else {

    if(sscanf(str, "%d,%d", dev, fast_dev) != 2) {

      write("Input the new dev and fast dev separated by a comma.\n"

           "Press enter for default.");

      read_file(dir[0]);

      input_to("adj_spell", 0, dir);

      return;

    }

    write("Spell updated.");

    write_spell(dir[0]);

    dir = exclude_array(dir, 0);

    while(sizeof(dir) && !read_spell(dir[0]))

      dir = exclude_array(dir, 0);

    input_to("adj_spell", 0, dir);

    return;

  }

  return;

}



      

