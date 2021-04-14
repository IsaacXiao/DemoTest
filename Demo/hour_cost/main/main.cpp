

#include <iostream>
#include <string>
#include <string.h> // for strcmp
#include <stdio.h> // for fprintf
#include <stdlib.h> // for EXIT_FAILURE ���ӿɶ���
#include <assert.h>
#include <utility>



#include "../platform/IncludeHeader.h"

typedef void (*pFunc)(const char* date);
void SlowFunc();


int main(int argc, char *argv[])
{
    SlowFunc(); //��windows�¼������ᵼ�º�����ʱ�俪��Ϊ0���пղ��   
	if (argc != 2)
    {
        std::cerr << "main: Invalid Input Param!" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        if (strcmp(argv[1], "h") == 0)
        {
            SoManager hour_agent(std::string("./hour.dll"));            
			assert(hour_agent.IsValid());

            pFunc hour_ptr = (pFunc)hour_agent.GetFunc(std::string("GetHours"));

			assert(nullptr != hour_ptr);

            std::string date_input;
            std::cout << "please enter date:" << std::endl;
            std::cin >> date_input;

            hour_ptr(date_input.c_str());
        }
        else if (strcmp(argv[1], "c") == 0)
        {
            SoManager cost_agent(std::string("./libcost.dll"));
            
            //Ҳ����������assert�ó�����ָ���ĵط������������Ŵ�
            assert(cost_agent.IsValid());

            pFunc cost_ptr = (pFunc)cost_agent.GetFunc(std::string("GetCost"));
            assert( nullptr != cost_ptr );

            cost_ptr("dumb");
        }
        else    //��������������߰���ķǷ�����
        {   
            std::cerr << "main: Invalid Input Param!" << std::endl;
            return EXIT_FAILURE;            
        }
    }
    return EXIT_SUCCESS;
}

