//NTF Shower Stall
//Coded By Traer
//7/10/99
inherit "std/room";
void create() {
	::create();
        set_property("indoors", 1);
	set_property("light", 4);
        set("short", "Shower stall");
        set("long", "You have stepped into a grimey shower stall. This stall is unlike the others in that it does not seem to be very well kept. Looking around you see that the tiles in the wall are cracked and there is writing all over them. The faucet appears to be working although the shower fixture seems to leak quite a bit. The towel rack is bent and there are rust stains on the floor. There appears to be an outline of something around the drain as well.\n");
	set_items(([
	"floor" :
    "Looking closer at the floor you get an uneasy feeling when you notice that the outline of a body.",
        "towel rack" :
        "The towel rack hangs loosely due to missing screws from one side.",
        "faucet" :
        "The faucet reads \"Hot/Cold\"",
        "rust" :
        "The rust stains on the floor do not look right for some reason. The appear in a oval surrounding the wall which supports the shower fixtures.",
	]));
        add_exit("/d/daybreak/room/ntf/shower", "out");
        add_exit("/d/damned/guilds/thief/thief4", "bathe");
        add_invis_exit("bathe");
        add_pre_exit_function( "bathe", "take_shower" );
}
int take_shower() {
    write("As you turn the shower on to bathe, the wall swings around and pushes you into a hidden passage!\n");
    return 1;
}
