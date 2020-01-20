//    Maxwell's Underground Mudlib 
//    Case

inherit "/std/bag_logic";
 
void create() {
  ::create();
    set_name("long wooden case");
    set_id( ({ "wooden case","case" }) );
   set_short("an old wooden case" );
    set_long("This old wooden case is covered in mold and dust. It is "
    "about six feet long and a foot deep.");
    set_weight(1000);
    set_value(0);
    set_possible_to_close(1);
    set_max_internal_encumbrance(500);
    this_object()->reset();
}
int get(){
    write("It appears to be stuck to the floor.");
    return 0;
}
void reset(){
    ::reset();
    if(!present("longsword"))
       new("/wizards/maxwell/objects/weapons/longs")->move(this_object());
    toggle_closed();
    return;
}
