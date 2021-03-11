 #include <log4cplus/logger.h>
 #include <log4cplus/consoleappender.h>
 using namespace log4cplus;
 using namespace log4cplus::helpers;
 int main()
{
	SharedAppenderPtr _append(new ConsoleAppender());
	_append->setName("append test");

	Logger _logger = Logger::getInstance("test");

	_logger.addAppender(_append);

	/*LOG4CPLUS_DEBUG(_logger, "This is the FIRST log message");
	
	LOG4CPLUS_WARN(_logger, "This is the SECOND log message");*/
	return 0;
}