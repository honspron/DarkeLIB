//    Maxwell's Underground Mudlib 
//            Chest

inherit "/std/bag_logic";
 
void create() {
  ::create();
    set_name("wooden chest");
    set_id( ({ "wooden chest","chest" }) );
   set_short("an old wooden chest" );
    set_long("This old wooden chest is covered in mold and dust. The sides "
    "of the chest are held together with long strips of metal.");
    set_weight(100000);
    set_value(70);
    set_possible_to_close(1);
    set_max_internal_encumbrance(500);
    new("/wizards/maxwell/objects/weapons/pick")->move(this_object());
    toggle_closed();
}

