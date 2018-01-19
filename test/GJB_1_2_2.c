void test_p(int p_1);

void static_p(void (* p)(int))
{
    p = test_p;
}
