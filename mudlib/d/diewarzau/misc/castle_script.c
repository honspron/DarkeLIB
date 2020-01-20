//  Castle script.

#include <security.h>

void start_manage() {
  call_out("manage_castles", 3, this_player());
  return;
}

void manage_castles(object tp) {
  string *dir1, *cdir, table;
  int *num_array = ({ 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20 });
  object *inv, ob, dest;
  int i, j;

  seteuid(UID_DAMNED_DATA);
  cdir = get_dir("/d/damned/data/castles/*");
  cdir = distinct_array(map_array(cdir,
    (: (arrange_string($1, strsrch($1, $2))) :),
    "."));
  message("info", sprintf("%O", cdir), tp);
  i = sizeof(cdir);
  message("info", sprintf("Iterating over %d castles.",
    i), tp);
  table = sprintf("Castles found: %d\n%'-='60s\n", i,
    "");
  while(i--) {
    reset_eval_cost();
    message("info", sprintf("Iterating over castle #%d.",
    i+1), tp);
    dir1 = map_array(num_array, (: (sprintf($2, $1)) :),
      "/d/damned/virtual/"+cdir[i]+"_room_%d.castle");
    j = sizeof(dir1);
    dest = load_object(sprintf("/d/damned/virtual/%s_room_1.castle",
      cdir[i]));
    inv = ({});
    while(j--) {
      inv += filter_array(all_inventory(load_object(dir1[j])),
        (: call_other :), "query_is_locker");
    }
    table += sprintf("%s's Castle: %d lockers moved/runes dested\n\n",
      cdir[i], sizeof(inv));
    map_array(filter_array(inv,
      (: !(call_other($1, $2)) :), "is_rune"),
      (: call_other :), "move", dest);
    map_array(filter_array(inv, (: call_other :), "is_rune"),
      (: call_other :), "remove");
  }
  tp->more(explode(table, "\n"));
  return;
}
