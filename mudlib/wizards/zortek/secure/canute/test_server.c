inherit "/std/virtual/compile";

void virtual_setup(string test) {
    if(find_player("diewarzau"))
	tell_object(find_player("diewarzau"), "Arg: "+test);
    return;
}
