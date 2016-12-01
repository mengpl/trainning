//============================================================================
// Name        : log4cpp.cpp
// Author      : mengpl
// Version     : v0.1
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include "log4cpp.h"

int main(void) {
    // 1实例化一个layout 对象
    log4cpp::PatternLayout* layout =   new log4cpp::PatternLayout();
    layout->setConversionPattern("%d [%t] [%p] %m%n");
    // 2. 初始化一个appender 对象
    log4cpp::Appender* appender = new   log4cpp::FileAppender("default","./Program.log");
    // 3. 把layout对象附着在appender对象上
    appender->setLayout(layout);
    // 4. 实例化一个category对象
    log4cpp::Category& root = log4cpp::Category::getRoot(); 
    root.setPriority(log4cpp::Priority::WARN);
    root.addAppender(appender);
    
    log4cpp::Appender* appender2 = new log4cpp::OstreamAppender("console", &std::cout);
    log4cpp::Category& warn_log = log4cpp::Category::getInstance("mywarn");
    // 5. 设置additivity为false，替换已有的appender
    warn_log.setAdditivity(false);
    // 5. 把appender对象附到category上
    warn_log.setAppender(appender2);
    // 6. 设置category的优先级，低于此优先级的日志不被记录
    warn_log.setPriority(log4cpp::Priority::WARN);
    
    // use of functions for logging messages
    root.error("root error");
    root.info("root info");
    warn_log.error("warn_log error");
    warn_log.warn("warn_log warn");

    // printf-style for logging variables
    root.warn("%d + %d == %s ?", 1, 1, "two");

    // use of streams for logging messages
    root << log4cpp::Priority::ERROR << "Streamed root error";
    root << log4cpp::Priority::INFO << "Streamed root info";
    warn_log << log4cpp::Priority::ERROR << "Streamed warn_log error";
    warn_log << log4cpp::Priority::WARN << "Streamed warn_log warn";

    root.errorStream() << "Another streamed error";

    std::cout << std::setw(6) << std::setfill('0') << 100000 << std::endl;
    // log4cpp::Category::shutdown();

    return EXIT_SUCCESS;
}
