#include <stdio.h>
#include <set>

int binary_search()
{
    int elements[7] = {4,11,8,9,3,2,10};
    
    int iSearch = 4;

    // 1 sort 
    std::set<int> sort_elements;
    for(int i = 0; i < 7; ++i)
    {
        sort_elements.insert(elements[i]);
    }

    int i = 0;
    for(std::set<int>::iterator it = sort_elements.begin();
            it != sort_elements.end();++it,++i)
    {
        elements[i] = *it;
    }

    // 2 binary search
    int iMin = 0;
    int iMax = 7 -1;
    int iBinary = -1;

    while(iMin <= iMax)
    {
        iBinary = (iMax + iMin) / 2;
        if(elements[iBinary] == iSearch)
        {
            break;
        }
        if(elements[iBinary] > iSearch) iMax = iBinary-1;
        if(elements[iBinary] < iSearch) iMin = iBinary+1;
    }


    if(iBinary != -1)
        fprintf(stderr, "finally we find %d in elements's position is %d\n",iSearch,iBinary);
    else
        fprintf(stderr, "finally can not find %d,in elements \n",iSearch);

    return -1; // can not find
}

int main(int argc,char** argv)
{
    fprintf(stderr, "*********** for data struccure*************\n");
    
    // 1 binary_search
    binary_search();

    // 2 

    return 0;
}