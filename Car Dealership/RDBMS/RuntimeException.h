#ifndef RUNTIMEEXCEPTION_H_
#define RUNTIMEEXCEPTION_H_

#include <iostream>
#include <string>

using namespace std;

class RuntimeException {// generic run-time exception
 private:
   string errorMsg;
 public:
   RuntimeException(const string& err) { errorMsg = err; }
   string getMessage() const { return errorMsg; }
};

inline std::ostream& operator<<(std::ostream& out, const RuntimeException& e)
{
   out << e.getMessage();
   return out;
}

#endif
