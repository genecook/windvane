#import <Foundation/Foundation.h>

#include "ObjCScaffold.h"

NSMutableString *RunLogBuffer;
NSMutableString *ErrorLogBuffer;
NSMutableString *TraceLogBuffer;

@implementation ObjScaffold

- (id)init {
  self = [super init];
  if (self) {
    RunLogBuffer   = [NSMutableString string];
    ErrorLogBuffer = [NSMutableString string];
    TraceLogBuffer = [NSMutableString string];
    _my_scaffold = new Scaffold("./a64sim.ini",NULL,NULL,NULL);
  }
  return self;
}

- (void)dealloc {
  delete _my_scaffold;
  //[super dealloc];  //<---not allowed on IOS
  NSLog(RunLogBuffer);
}

- (void)freerun {
  _my_scaffold->FreeRun(0,100,99);
  NSLog(RunLogBuffer);
  RunLogBuffer = [NSMutableString string];
  NSLog(TraceLogBuffer);
  TraceLogBuffer = [NSMutableString string];

}

@end
