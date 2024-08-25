#include "squa.h"

void getname(){
    SQUA_MessageBox("1 + 1 = 2", "What is 1 + 1?");
}

int main(int argc, char const *argv[])
{
    SQUA_Init(false);
    
    SQUA_CreateButton(10, 15, "Greet", SQUA_ConvertToListener(getname));

    while (1)
    {
        int res = SQUA_Begin();
        if (res == 1)
            break;
    }

    SQUA_Terminate();
    return 0;
}
