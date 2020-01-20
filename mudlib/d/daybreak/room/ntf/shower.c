//NTF Shower
//Coded By Traer
//7/10/99
inherit "std/room";
void create() {
	::create();
        set_property("indoors", 1);
	set_property("light", 4);
        set("short", "The shower room");
	set("long", "Steam rises and swirls around you and the heat is nearly as unbearable as the stench. Bums and braggards from across the realm lie about as though this were a sauna at their local country club. The shower stalls line the outer walls of the room and off to one side is a row of sinks. Each stall has it's own curtain although most of them wide open with a swarthy looking sod behind it there is one that is tightly closed just near the wall.\n");
	set_items(([
	"floor" :
	"The floor is a white, marble tile very much like you have seen in the local hospitals. Very sanitary looking.",
	({ "shower", "shower stalls", "showers", "stalls", "walls", "towels", "soaps" }):
	"The shower stalls are meticulously sanitized each day with new towels and soaps being prepared for tomorrow's arrivals."
	]));
        add_exit("/d/daybreak/room/ntf/ntfkitchen", "kitchen");
        add_exit("/d/daybreak/room/ntf/stall", "stall");

}
void reset() {
	if(!present("bum"))
	{
	new("/d/daybreak/mon/showerbum")->move(this_object());
	}
}
