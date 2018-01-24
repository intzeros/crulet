_Bool foo(unsigned * p1, unsigned * p2)
{
    unsigned * p3 = p1 + (p2 - p1) / 2, * p4 = p1 - p2[0];
    return p4 < p3;
}
