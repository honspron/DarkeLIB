// /wizards/excelsior/newbie/rooms/fr2.1

inherit "std/room";

int check_mobs();

// we will call the monster file /wizards/excelsior/newbie/mon/teddy_bear,
// and the room /wizards/excelsior/newbie/rooms/fr2.1

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
	set("short","Frolicking in the woods");
	set("long","You continue to frolick in the woods of wayreth. To the "+
		"northeast you can see the city of New Faerie Dust, but you don't "+
		"pay attention to them. You would rather run around and be free. You "+
		"suddenly get the urge to take off your clothes and run around even "+
		"freer, but then you remember the telecommunications bill and realize "+
		"that that would be indecent. You could be arrested!");
	set_items((["woods":"They make you happy",
		"wayreth":"That is the name of the woods. You see them around you.",
		"city":"You can make it out over the trees",
		"telecommunications bill":"A piece of legislation with no regards for "+
			"civil rights. Do you get the feeling that the people who are so "+
			"afraid of porno on the net have probably never even seen a computer "+
			"keyboard too?"
,
		"brook":"You can't see it, you can just hear it."]));
	set_exits((["southwest":"/wizards/excelsior/newbie/rooms/fr1.2",
		"southeast":"/wizards/excelsior/newbie/rooms/fr3.2"]));	
	set_listen("default","You hear a brook to your east.");
	set_smell("default","Even you smell clean in this environment.");
}

int check_mobs() {
  object *all;

  all = filter_array(livings(), "my_mob_filter", this_object());
  if(!all) return 0;
  return sizeof(all);
}


// Also define this in the room:

int my_mob_filter(object mob) {
  if(base_name(mob) == "/wizards/excelsior/newbie/mon/teddy_bear") 
    return 1;                                     
  return 0;                                       
}
