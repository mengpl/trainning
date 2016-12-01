//============================================================================
// Name        : log4cpp.cpp
// Author      : mengpl
// Version     : v0.1
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include "log4cpp.h"

int main(void) 
{

    std::string initFileName = "log4cpp.conf";
    try
    {
        log4cpp::PropertyConfigurator::configure(initFileName);
    }
    catch(log4cpp::ConfigureFailure& f) 
    {
        std::cout << "Configure Problem " << f.what() << std::endl;
        return -1;
    }
    

    log4cpp::Category& root = log4cpp::Category::getRoot();

    log4cpp::Category& sub1 = 
        log4cpp::Category::getInstance(std::string("sub1"));

    log4cpp::Category& sub2 = 
        log4cpp::Category::getInstance(std::string("sub1.sub2"));

    root.warn("Storm is coming");

    sub1.debug("Received storm warning");
    sub1.info("Closing all hatches");

    sub2.debug("Hiding solar panels");
    sub2.error("Solar panels are blocked");
    sub2.debug("Applying protective shield");
    sub2.warn("Unfolding protective shield");
    sub2.info("Solar panels are shielded");

    sub1.info("All hatches closed");

    root.info("Ready for storm.");

    return EXIT_SUCCESS;
}
