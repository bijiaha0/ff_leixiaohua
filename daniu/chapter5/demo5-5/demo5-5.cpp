using namespace std;

int main() {
    char ch = 'a';

    // &操作符
    //&ch = 97;                      // &ch左值不合法
    char *cp = &ch;                // &ch右值
    //&cp = 97;                      // &cp左值不合法
    char **cpp = &cp;            // &cp右值

    // *操作符
    *cp = 'a';                           // *cp左值取变量ch位置
    char ch2 = *cp;                 // *cp右值取变量ch存储的值
    //*cp + 1 = 'a';                 //  *cp+1左值不合法的位置
    ch2 = *cp + 1;                  //  *cp+1右值取到的字符做ASCII码+1操作
    *(cp + 1) = 'a';                  //  *(cp+1)左值语法上合法，取ch后面位置
    ch2 = *(cp + 1);                //  *(cp+1)右值语法上合法，取ch后面位置的值

    return 0;
}

