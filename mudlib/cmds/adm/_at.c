// Zor 93

#include <security.h>

create() {

   seteuid(getuid());

}



int help() {

  write( @TEXT

Syntax: <at [place|person] do [action]>



Command executes [action] as if it were being typed at the named

location or person's location.



See also: tell

TEXT

  );

  return 1;

}



cmd_at(string arg) {

   string foo,bar;

   object whar,don_quixote;

   if (!arg) {write("Usage: at <place | person> do <action>\n");

      return 1;}

   if (sscanf(arg,"%s do %s",foo,bar) != 2)

      {write("Usage: at <place | person> do <action>\n"); return 1;}

   if (!whar = find_player(foo))

      if (!whar = find_living(foo))

      {   string tmp;

      tmp = resolv_path((string)this_player()->get_path(),foo);

      if (!file_exists(tmp+".c"))

         {write("Could not find "+foo+".\n"); return 1;}

      call_other(tmp,"???");

      if(!whar = find_object(tmp)) {write("Couldnt find "+foo+".\n");

         return 1;}}

   if (living(whar)) whar = environment(whar);

   don_quixote = environment(this_player());

   this_player()->move(whar);

   if(environment(this_player()) == whar) {

      seteuid(UID_FORCE);

      this_player()->force_me(bar);

      seteuid(getuid());

   }

   else write("Failed move call.\n");

   this_player()->move(don_quixote);

   return 1;

}

