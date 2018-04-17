void static_p(void);

extern int e1;

unsigned int duplicate = 0u;

void static_p(void){
  enum Name_type{
    e1,
    duplicate,
    static_p
  }EnumVar;

  EnumVar = e1;
}