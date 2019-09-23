#include "a64sim.h"

@interface ObjScaffold : NSObject
@property (nonatomic, readwrite, assign) Scaffold *my_scaffold;

- (void)freerun;
@end
