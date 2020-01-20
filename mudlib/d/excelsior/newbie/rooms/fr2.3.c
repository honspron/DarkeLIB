// /wizards/excelsior/newbie/rooms/fr2.3

inherit "std/room";

int check_mobs();

// we will call the monster file /wizards/excelsior/newbie/mon/teddy_bear,
// and the room /wizards/excelsior/newbie/rooms/fr2.3

void reset() {
	int n;
	::reset();
	n = 6-check_mobs();
	if(n <= 0) return;
	while(n > 0) {
		new("/wizards/excelsior/newbie/mon/teddy_bear")->move(this_object());
		n--;
	}
}

void create() {
	::create();
	set_property("light",2);
	set_property("indoors",0);
	set("short","Frisking about the woods");
	set("long","You continue to frisk about the woods of Wayreth. To the "+
		"northeast you can see the city of New Faerie Dust, but you don't "+
		"pay attention to them. You would rather run around and be free. If "+
		"you don't know what frisk means, you suck.");
	set_items((["woods":"They make you happy",
		"wayreth":"That is the name of the woods. You see them around you.",
		"city":"You can make it out over the trees",
		"frisk":"To romp, dance, cavort, prance, caper, rollick, frolic,  "+
			"or gambol.",
		"brook":"You can't see it, you can just hear it."]));
	set_exits((["northwest":"/wizards/excelsior/newbie/rooms/fr1.2",
		"northeast":"/wizards/excelsior/newbie/rooms/fr3.2",
		"south":"/wizards/excelsior/newbie/rooms/fr2.4"]));	
	set_listen("default","You hear a brook to your east.");
	set_smell("default","Even you smell clean in this environment.");
}

int check_mobs() {
  object *all;

  all = filter_array(livings(), "my_mob_filter", this_object());
  if(!all) return 0;
  return sizeof(all);
}

int my_mob_filter(object mob) {
  if(base_name(mob) == "/wizards/excelsior/newbie/mon/teddy_bear") 
    return 1;                                     
  return 0;                                       
}
