#include "SalesforceSOS.h"
#include "SOSApplication.h"

@implementation SalesforceSOS

 - (void)startSOS:(CDVInvokedUrlCommand*)command {
     if (command.arguments.count > 0) {
         [SOSApplication sharedInstance].email = [command.arguments objectAtIndex:0];
     }
     [[SOSApplication sharedInstance] startSession:nil];
 }

 @end
 