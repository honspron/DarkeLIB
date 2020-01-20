//The Elementalists spell room.
//	DarkeLIB 0.1
//original coding by Diewarzau, remodeling by Mushroom.

inherit "/std/guilds/spell_room";

void create() {
  ::create();
  set("short", "The Elementalist's Spell Library");
  set("long", 
	"You look around the immense library and see a uncountable "
	"number of old leather bound books. The library is physicaly "
	"separated into many sections. These sections contain old books "
	"of lore on the for elements. Whoever compiled this mass of "
	"knowledge must have lived a long time. In the center of building "
	"you see a table. It seems to be a place where students of "
	"different disciplines can congregate and learn more about the "
	"awesome powers of the elements. There are a few elementalists "
	"in different parts of the room, researching their deadly spells. "
	"You should join them and become wise in the way of the elements: "
	"%^BOLD%^%^RED%^Fire, %^BLUE%^Water, %^CYAN%^Air, "
	"%^RESET%^%^ORANGE%^Earth, %^CYAN%^Cold, "
	"%^FLASH%^%^BOLD%^%^CYAN%^Electricity, "
	"%^RESET%^%^CYAN%^Ice, %^FLASH%^%^BOLD%^%^WHITE%^Wind, "
	"%^RESET%^%^YELLOW%^Inertia, %^GREEN%^Vacid, "
     "%^RESET%^and %^B_WHITE%^%^BLACK%^Chaos.%^RESET%^\n");
  set_property("light", 2);
  set_property("indoors", 1);
  set_join_room("/d/damned/guilds/join_rooms/elementalist_join");
  set_items( ([
   ({"book", "books"}) : "There are many books of spells here.",
	"table" : "This is a very old oak table with a design made of "
			"brass. It is a round table split into four sections: "
			"%^RED%^%^BOLD%^Fire, %^BLUE%^Water, %^CYAN%^Air, %^RESET%^"
			"and %^ORANGE%^Earth.%^RESET%^",
	"design" : "There is a different design on each section of the "
			"table. Each depicts one of the four basic elements: "
			"%^RED%^%^BOLD%^Fire, %^BLUE%^Water, %^CYAN%^Air, %^RESET%^"
			"and %^ORANGE%^Earth.%^RESET%^",
	"library" : "The library is a large room split into many sections: "
     "%^BOLD%^%^RED%^Fire, %^BLUE%^Water, %^CYAN%^Air, "
     "%^RESET%^%^ORANGE%^Earth, %^CYAN%^Cold, "
     "%^FLASH%^%^BOLD%^%^CYAN%^Electricity, "
     "%^RESET%^%^CYAN%^Ice, %^FLASH%^%^BOLD%^%^WHITE%^Wind, "
     "%^RESET%^%^YELLOW%^Inertia, %^GREEN%^Vacid, "
	"%^RESET%^and %^B_WHITE%^%^BLACK%^Chaos.%^RESET%^",
	"Earth" : "%^ORANGE%^The earth section is made from the purest soil. "
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
	"Fire" : "%^RED%^%^BOLD%^The inferno like air of this section bakes "
			"everything to a nice golden brown. The desert like heat "
			"has made you thirsty. The design on the table is a "
			"smouldering picture of a conflageration.%^RESET%^",
]) );
  set_exits( ([ "west" : "/d/damned/guilds/elementalist/ele_train" ]) );

  add_spell("summon lesser elemental");
  add_spell("summon elemental");
  add_spell("lesser essential blade");
  add_spell("essential blade");
  add_spell("greater essential blade");
  add_spell("elemental presence");
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
  add_spell("body of elements");
  add_spell("elemental transformation");
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

  
