// WRITTEN: 931013 By: Mata : GAG will set the blocking variable.

int help() {
   write(@END
Syntax: <shutup [person] [channel]>

Applies a gag to the [channel] for [person], assuming, of course, that
it passes permission.

See also: tell, line, earmuff, lemote.
END
   );
   return 1;
}

int cmd_shutup (string borg) {
   /// u will be assimilated
   string person, channel, junk;
   object ob;
   int argc;
   
   if(!borg) { notify_fail("GAG whom?\n"); return 0; }
   argc = sscanf(borg+" ","%s %s %s ",person,channel,junk);
   if(argc > 0) {
      ob = find_player(person);
      if(ob) {
         if(argc > 1) {
            if(ob->set_blocking(channel)) {
               write("Channel: ["+channel+"] blocked.\n");
               tell_player(ob, "Due to abuse, "+this_player()->query_cap_name()+
                  " has banned your usage of the "+channel+" channel.\n");
            }
            else {
               write("Channel: ["+channel+"] cleared.\n");
               tell_player(ob, this_player()->query_cap_name()+" has removed the ban on your usage of the "+channel+" channel.\n");
            }
         }
         else 
            write("Not implemented yet.\n");
         return 1;
      }
      else {
         notify_fail("Player "+person+" not found.\n");
         return 0;
      }
   }
}

