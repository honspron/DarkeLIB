// a test

void start_test() {
  delayed_call("finish_test", 30, this_player(), "help me!");
  write(sprintf("%O", delayed_call_info()));
  return;
}

void int_test() {
  remove_delayed_call("finish_test");
  write(sprintf("%O", delayed_call_info()));
  return;
}

void finish_test(object who, string str) {
  message("info", "TEST FINISHED!", who);
  message("info", "Test str: "+str, who);
  return;
}

