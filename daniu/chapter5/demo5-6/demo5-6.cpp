int main() {
    char ch = 'a';
    char *cp = &ch;
    // ++,--操作符
    char *cp2 = ++cp;
    char *cp3 = cp++;
    char *cp4 = --cp;
    char *cp5 = cp--;

    // ++ 左值
    //++cp2 = 97;
    //cp2++ = 97;

    // *++, ++*
    *++cp2 = 98;
    char ch3 = *++cp2;
    *cp2++ = 98;
    char ch4 = *cp2++;

    // ++++, ----操作符等
    int a = 1, b = 2, c, d;
    //c = a++b;                  // error
    c = a++ + b;
    //d = a++++b;             // error
    char ch5 = ++*++cp;

    return 0;
}

