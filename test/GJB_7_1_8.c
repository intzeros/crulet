void void_para_func(void *p_1){
  /*...*/
}

void void_para_func2(int *p_1){
  /*...*/
}

void static_p(unsigned int p_1, unsigned short p_2){
  int y = 0;
  void *v_ptr = &y;
  y = (int)(p_1 + p_2);
  void_para_func(v_ptr);
  void_para_func2(v_ptr);
}