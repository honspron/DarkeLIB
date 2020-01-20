/*
 * Cleanmem, a soft reboot to clean out as much memory as possible.
 *
 * Diewarzau 7/16/96
 * DarkeLIB 1.0
 */

int cmd_cleanmem(string null) {
  object *obs;

  obs = objects((: (member_array("std/room.c", 
				 deep_inherit_list($1)) >= 0) :));
  write("Rooms found: "+sizeof(obs));
  write("Cleaning all rooms...");
  map_array(obs, (: call_other :), "clean_up");
  write("Done with cleanup.");
  return 1;
}

int help() {
  message("help",
"This command forces a clean up on all rooms loaded into memory.  "
"Usually this takes about 15 sec. and frees about 3-4 meg of memory.\n"
"\n"
"Syntax: cleanmem\n", this_player());
  return 1;
}

