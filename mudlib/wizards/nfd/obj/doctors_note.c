// /d/nfd/obj/doctors_note

// ok, this is a nice doctor's note that mama request for her

// kid. HA! I laf at you for no reason. Muahahahaha.

// -Excelsior!>([]



#undef \

   inherit "std/Object";



   void init() {

      ::init();

      add_action("read_note","read");

}



   void create() {

      ::create();

      set_name("note");

      set("id",({"note","doctor's note","paper","googooga"}) );

      set("short","A fine doctor's note");

      set("long","This is a doctors note telling of the state of the child "+

	 "you recently brought to the hospital. If you know what's good for "+

	 "you you will return to the child's mother with it. You can 'read' "+

	 "it to see what it says for yourself if you so desire. ");

set_value( 1 );

      set_weight( 1 );

}



   int read_note(string str) {

      if ( id(str) ) {

write("_________________________________________________________\n"+

"|                                                        |\n"+

"|      |\\| |~ |\\ A A |_|                                 |\n"+

"|      | | |~ |/ |V| | |                                 |\n"+

"| --------------------------------------                 |\n"+

"|     Patient:       An generic child                    |\n"+

"|                      (legal guardian unknown)          |\n"+

"|     Treated for:  An unknown foriegn agent-            |\n"+

"|                    severe allegic reaction             |\n"+

"|                        similar to several other rec-   |\n"+

"|                                ent cases. (FILE #87)   |\n"+

"|      Current condition:  Critical                      |\n"+

"|                            %50 chance of survival      |\n"+

"|      Treatment:  Pain relievers, attempt to remove     |\n"+

"|          foriegn chemicals from body unsuccesful,      |\n"+

"|             cleric treatment underway                  |\n"+

"|      Doctor:  Dr. Sea U. Inheel n.o.g                  |\n"+

"| --------------------------------------                 |\n"+

"| This treatment has been payed for by your              |\n"+

"| wonderful NFD council of leaders and the NFD           |\n"+

"| department of health (Were not doctors, but we         |\n"+

"| play them on DarkeMud) because WE CARE.                |\n"+

"|________________________________________________________|\n");

return 1;

}

      else notify_fail("Read  _WHAT_?? Are you stupid or something? Guy.");

      return 0;

      return 0;

}

