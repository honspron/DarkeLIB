void redo_stuff() {
  string file_tmp;
  int i, j;

  for(i=1;i<=2;i++) {
    for(j = 0;j <= 2; j++) {
      file_tmp = read_file(sprintf("/d/damned/inn/hall_%d.c", (i*10 + j)));
      file_tmp = replace_string(file_tmp,
	"locked(sprintf("door %d", i), 0)",
	"locked(sprintf(\"door %d\", i), 1)")
      write_file(sprintf("/wizards/diewarzau/hall_%d.c", (i*10+j)), file_tmp);
    }
  }
  return
}
