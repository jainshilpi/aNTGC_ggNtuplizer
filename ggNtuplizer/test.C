template<typename typeA, typename typeB>
void setbit(typeA & x, typeB bit) {
  typeA a = 1;
  x |= (a << bit);
}
