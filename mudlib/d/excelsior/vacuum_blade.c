inherit "std/weapon";

void create() {
::create();
   set_name("blade");
   set("id",({"Excelsior's Vacuum Blade","blade"}));
   set("short",
      "Excelsior's Vacuum Blade");
   set("long","Though extremely heavy, that magic radiating from it allows "+
"you to wield it with extreme and deadly agility. This blade "+
"is gaurenteed to cause a vacuum effect every time it is used.");
   set_weight(1);
   set("value",10000);
   set_ac(8);
   set_wc(30, "vacuum" );
   set_type("blade");
   set_quality(6);
   set_property("no decay",1);
   set_auto_critical("vacuum E");
}
