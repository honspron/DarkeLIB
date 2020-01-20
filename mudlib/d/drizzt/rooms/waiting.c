//      from the Nightmare mudlib
//      an example workroom for new immortals

inherit "/std/room";

void create() {
    seteuid(getuid());
    set_property("light", 2);
    set_property("indoors", 1);
    set("short", "Drizzt's waiting room.");
    set("night long", "I am too lazy to write a long desc.\n");
    set("day long", "I am too lazy to write a long desc.\n")
;
    set_exits( 
	({
        "/d/standard/square", "/d/standard/adv_main","/d/standard/adv_inner"
        ,"/d/standard/boards/projects"
	}),
	({
        "square", "hall", "boards", "proj"
	})
    );
}
