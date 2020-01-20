///bin/dev/_people.c
//from the Nightmare mudlib
//created by Cynosure@Nightmare
//      check_invis() added by Plura 930201
//      sort_by_name() added by Plura 930201
//     parameters mort, newbie, wiz, arch, dead added by Plura 930204
//      and hmort aswell.

#include <writef.h>
#include <daemons.h>
#include <std.h>

#define DIV "---------------------------------------"
#define DIVIDER DIV+DIV
#define POSITIONS ({ "player", "high mortal", "immortal", "creator", "elder", \
		      "mentor", "arch", "head arch", "administrator" })


varargs int cmd_people(string order, string arg)
{   object *list;
   string line, str2, zone_name;
   string *argv;
   int i, do_more, time_zone, xyzpdq;
   
   if(!wizardp(this_player())) {
     write("This option is only available to wizards.");
     return 1;
   }
   line = DIVIDER + "\n";
   list = filter_array(users(), "check_invis", this_object());
   if(arg)
      {
      if(arg && !sizeof((argv=explode(arg," "))))
         argv = ({ arg });
      if(member_array("m",argv)!=-1||member_array("more",argv)!=-1)
         do_more = 1;
      if(member_array("w",argv)!=-1||member_array("wiz",argv)!=-1)
         list = filter_array(list, "check_wiz", this_object());
      if(member_array("arch",argv)!=-1)
         list = filter_array(list, "check_arch", this_object());
      if(member_array("mort",argv)!=-1)
         list = filter_array(list, "check_mort", this_object());
      if(member_array("hmort",argv)!=-1)
         list = filter_array(list, "check_hmort", this_object());
      if(member_array("newbie",argv)!=-1)
         list = filter_array(list, "check_newbie", this_object());
      if(member_array("dead",argv)!=-1)
         list = filter_array(list, "check_dead", this_object());
      if(member_array("a",argv)!=-1||member_array("alpha",argv)!=-1)
         list = sort_array(list, "sort_by_name", this_object());
      else
         list = sort_array(list, "sort_by_level", this_object());
   }
   else
      list = sort_array(list, "sort_by_level", this_object());
    list = (object *)this_object()->master_sort(list,order);

   if(!sizeof(list))
   {
      message("system","No players found.",
        this_player());
      return 1;
   }
   
   // Time zone code, by Docz
   zone_name = (string)this_player()->getenv("TZONE");
   time_zone = (int)TIME_D->query_tzone(zone_name);
   if (!zone_name)
      line += "                  Mud time is "+ctime(time())+"\n";
   else
      line += "                "+zone_name+" time is "+ctime(time_zone)+"\n";
   
   line += DIVIDER + "\n";
   
   for (i=0; i<sizeof(list); i++)
   {   string field;
      mixed val;
      
      if( !list[i]->query_name() ) continue;
      xyzpdq = (int)list[i]->query_age();
      if(xyzpdq>86400) field = (xyzpdq/86400 + " D");
      else if(xyzpdq>3600) field = (xyzpdq/3600) + " h";
      else field = (xyzpdq/60) + " m";
      line += sprintf("%-5s", field);
      if(list[i]->query_invis()) field = "("+capitalize((string)list[i]->query_name())+")";
      else field = (string)list[i]->query_name();
      if(field) field = capitalize(field);
      if (in_edit(list[i]) || in_input(list[i]))
         field = "*" + field;
      line += sprintf("%-12s", field);
      field = (string) list[i] -> query_ip();
      if (!field) field = "-";
      line += sprintf("%-25s", field[0..24]);
      xyzpdq = (int) list[i] -> query_level();
      field = ""+xyzpdq+"";
      if (!field) field = "-";
      line += sprintf("%-3s", field);
      val = query_idle(list[i]);
      if ( val <= 0 ) field = "";
      else if( val >= 3600 ) field = val/3600 + "h";
      else if( val >= 60 ) field = val/60 + "m";
      else field = "";
      line += sprintf("%-5s", field);
      val = environment(list[i]);
      if (!val) field = "(null)";
      else {
         field = file_name(val);
         if(sscanf(field, "/wizards/%s", str2) == 1) field = "~"+str2;
        }
      line += sprintf("%-25s", field[0..24]);
      line += "\n";
   }
   line += DIVIDER + "\n";
   if(do_more)
      this_player()->more(explode(line, "\n"));
   else
    message("Nsystem", line, this_player());
   return 1;
}

int
sort_by_level(object u1, object u2)
{
   int level1, level2;
   string name1, name2;
   
   level1 = (int)u1->query_level();
   level2 = (int)u2->query_level();
   if(wizardp(u1)) level1 += 100;
   if(wizardp(u2)) level2 += 100;
   if (level1 == level2) {
      name1 = (string)u1->query_name();
      name2 = (string)u2->query_name();
      if (name1 == name2)
         return 0;
      if (name1 < name2)
         return -1;
      else
         return 1;
   }
   if (level1 > level2)
      return -1;
   else
      return 1;
}

int
sort_by_name(object u1,object u2)
{
   string name1, name2;
   name1 = (string)u1->query_name();
   name2 = (string)u2->query_name();
   if(!name1 || !name2)
      return -1;
   if (name1 == name2)
      return 0;
   if (name1 < name2)
      return -1;
   else
      return 1;
}

// Levels redone by Valodin, July 12, 1993
int
get_pos(object ob)
{
  string *pos;
  int ret;
  pos = POSITIONS;
  ret = member_array(ob->query_position(), pos);
  if (ret == -1)
    // better error handling is needed, but for now...
    return 0;
  return ret;
}

int
check_invis(object ob)
{
   string *pos;
   pos = POSITIONS;
   if((int)ob->query_invis() && get_pos(this_player()) < get_pos(ob))
     return 0;
   return 1;
}

int
check_wiz(object ob)
{
   return wizardp(ob);
}

int
check_arch(object ob)
{
   string p;
   return (wizardp(ob) && ((p = (string)ob->query_position()) == "arch" || 
			   p == "head arch" || p == "administrator"));
}

int
check_hmort(object ob)
{
   return high_mortalp(ob);
}

int
check_mort(object ob)
{
   return (ob->is_player() && (string)ob->query_position() == "player");
}

int
check_newbie(object ob)
{
   return (ob->is_player() && ob->query_level() < 6 && 
	   (string)ob->query_position() == "player");
}

int
check_dead(object ob)
{
   return (int)ob->query_ghost();
}

void help_people() {
    message("help",
      "With -people specifier:\n"
      "Syntax: who -people [<more> <alpha> <a> <arch> <wiz> <hmort> <mort>]\n"
      "Gives a special listing of people online.\n\n"
      "See also: finger, users, who", this_player()
    );
}
