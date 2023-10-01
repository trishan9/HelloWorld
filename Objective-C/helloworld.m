#import <Foundation/Foundation.h>

int main (int arg, const char * argv[])
{
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
   NSLog (@"Hello, world!");
   [pool drain];
   return 0;
}
