#include "SalesforceSOS.h"
#include "SOSApplication.h"

@implementation SalesforceSOS

 - (void)startSOS:(CDVInvokedUrlCommand*)command {
     [[SOSApplication sharedInstance] startSession];
 }

 @end
 