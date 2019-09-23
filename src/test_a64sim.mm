#import <Foundation/Foundation.h>

#import "ObjCScaffold.h"

int main (int argc, const char *argv[]) {
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  NSLog(@"Dude!");

  ObjScaffold *scf = [[ObjScaffold alloc] init];

  [scf freerun];

  [scf release];

  [pool drain];
  return 0;
}
