inherit "/std/Object";
int spoken_words;

void init() {
   ::init();
   add_action("read", "read");
   add_action("say_it", "say");

}

void create() {
  ::create();
  set_name("cauldren");
  set_id( ({ "cauldren", "black cauldren", "mysterious cauldren" }) );
  set_short("A mysterious black cauldren");
  set_long(
    "This mysterious looking black cauldren has an almost unmistakable magic aura "+
  "about it. While it is large enough to cook a hearty meal for a band of rogues, "+
  "it is light enough for the bearer to carry with him. There are runes inscribed "+
"on the side of the cauldren in very old language stemming back to the god Dagda.");
  set_weight(50);
  set_value(500);
  return;
}

int read(string str) {
   if(!str) {
      return 0;
   }   
     if((str != "rune") && (str != "cauldren")) {
      notify_fail("Read what?\n");
      return 0;
   }
     write(
          "There are 3 distinctly different messages on the side of the cauldren.\n"+
                "Dean Mairteoil\n"+
                "Dean Caoirioil\n"+
                "Dean Muiceoil\n"
         );
   return 1;
}
int say_it(string str) {
   object ob, tp;
 
   if(spoken_words == 1)
      return 0;
 
   if(!str)
      return 0;
 
   if(strsrch(str, "dean mairteoil") == -1)
         return 0;
 
   spoken_words = 1;

   return 1;
}


