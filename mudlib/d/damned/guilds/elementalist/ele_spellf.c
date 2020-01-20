//The Elementalists spell room.
//	DarkeLIB 0.1
//original coding by Diewarzau, remodeling by Mushroom.

inherit "/std/guilds/spell_room";

void create() {
  ::create();
  set("short", "The Elementalist's Fire Spell Library");
  set("long", 
	"%^RED%^%^BOLD%^This quarter of the library is devoted only to "
	"the study of fire. The many books are shelved on magical flames "
	"that are very hot, yet do not seem to burn the books. There are "
	"a few elementalist mages learning the ways of fire, and also a "
	"few just sitting around trying to get a tan.");
  set_property("light", 2);
  set_property("indoors", 1);
  set_join_room("/d/damned/guilds/join_rooms/elementalist_join");
  set_items( ([
   ({"book", "books"}) : "There are many books of spells here.",
	"library" : "The library is a large room split into four sections: "
			"%^RED%^%^BOLD%^Fire, %^BLUE%^Water, %^CYAN%^Air, %^RESET%^"
			"and %^YELLOW%^Earth.%^RESET%^",
	"Earth" : "%^YELLOW%^The earth section is made from the purest soil. "
			"The design on the table is of a sorceror using the powers "
			"of the earth in both good and evil. There are great mounds "
			"of earth being moved by magic.%^RESET%^",
	"Air" : "%^CYAN%^%^BOLD%^This area of the library does not really "
			"have walls, rather the books are held up by gusts of "
			"wind. On the table there is an image of tornado's and "
			"hurricanes reshaping the world.%^RESET%^",
	"Water" : "%^BLUE%^%^BOLD%^You look around this area of formed water. "
			"Amazingly, the books in this section stay dry. On the "
			"table, the design of tidalwaves and floods changes back "
			"and forth from solid to liquid.%^RESET%^",
	"Fire" : "%^RED%^%^BOLD%^The inferno like air of this quarter bakes "
			"everything to a nice golden brown. The desert like heat "
			"has made you thirsty. The design on the table is a "
			"smouldering picture of a conflageration.%^RESET%^",
]) );
  set_exits( ([ "center" : "/d/damned/guilds/elementalist/ele_spell" ]) );

  add_spell("summon lesser elemental");
  add_spell("summon elemental");
  add_spell("lesser essential blade");
  add_spell("essential blade");
  add_spell("greater essential blade");
  add_spell("elemental curse");
  add_spell("elemental bane");
  add_spell("summon greater elemental");
  add_spell("summon elemental dragon");
  add_spell("lesser elemental bolt");
  add_spell("elemental bolt");
  add_spell("greater elemental bolt");
  add_spell("lesser elemental storm");
  add_spell("elemental storm");
  add_spell("greater elemental storm");
  add_spell("lesser elemental strike");
  add_spell("elemental strike");
  add_spell("greater elemental strike");
  add_spell("lesser elemental blade");
  add_spell("elemental blade");
  add_spell("greater elemental blade");
  add_spell("elemental shield");
  add_spell("elemental barrier");
  add_spell("elemental aegis");
  return;
}

  
