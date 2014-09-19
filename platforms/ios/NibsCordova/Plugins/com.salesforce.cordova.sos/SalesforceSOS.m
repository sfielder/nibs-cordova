#import <SOS/SOS.h>
#include "SalesforceSOS.h"
#include "SOSApplication.h"

@implementation SalesforceSOS

// Args: email
- (void)startSOS:(CDVInvokedUrlCommand*)command {
     if (command.arguments.count > 0) {
         [SOSApplication sharedInstance].email = [command.arguments objectAtIndex:0];
     }
     [[SOSApplication sharedInstance] startSession];
 }

// Args: account, app, [email, retry, expire]
- (void)setup:(CDVInvokedUrlCommand*)command {
    CDVPluginResult* pluginResult = nil;
    if (command.arguments.count >= 2) {
        NSMutableDictionary *args = [NSMutableDictionary dictionary];
        [args setObject:[command.arguments objectAtIndex:0] forKey:@"account"];
        [args setObject:[command.arguments objectAtIndex:1] forKey:@"app"];
        if (command.arguments.count > 2) {
            [args setObject:[command.arguments objectAtIndex:2] forKey:@"email"];
        }
        if (command.arguments.count > 3) {
            [args setObject:[command.arguments objectAtIndex:3] forKey:@"retry"];
        }
        if (command.arguments.count > 4) {
            [args setObject:[command.arguments objectAtIndex:4] forKey:@"expire"];
        }
        
        [[SOSApplication sharedInstance] setSessionOptions:args];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:nil];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_JSON_EXCEPTION
                                     messageAsDictionary:@{@"error":@"must supply account and app arguments at least"}];
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)setupMessages:(CDVInvokedUrlCommand*)command {
    SOSApplication *sos = [SOSApplication sharedInstance];
    for (int i = 0; i < command.arguments.count; i++ ){
        NSString *val = [command.arguments objectAtIndex:i];
        switch (i) {
            case 0:
                sos.alertTitle = val;
                break;

            case 1:
                sos.connectMessage = val;
                break;

            case 2:
                sos.disconnectMessage = val;
                break;
                
            case 3:
                sos.agentDisconnectMessage = val;
                break;
                
            case 4:
                sos.retryMessage = val;
                break;
                
            case 5:
                sos.timeoutMessage = val;
                break;

            default:
                break;
        }
    }
    [sos setupMessages];
}

 @end

/**
 *  In this guide we will be customizing some of the default SOS behavior.
 *
 *  As the name of the guide suggests this is basic customization restricted to setting a few properties.
 *  The SOSUIComponents class provides access to toggle/customize most UI behavior.
 *  The SOSScreenAnnotations class provides the ability to modify properties related to line drawing.
 *
 */
@implementation SOSApplication

@synthesize email;

- (id)init {
    self = [super init];
    self.retrySeconds = 10;
    self.expireSeconds = 60;

    self.alertTitle = @"Live Video Chat";
    self.connectMessage = @"Talk to a Nibs Chocolatier now";
    self.disconnectMessage = @"Thanks for trying video chat";
    self.agentDisconnectMessage = @"Thank you";
    self.retryMessage = @"Would you still like to view chat with a Nibs Chocolatier?";
    self.timeoutMessage = @"We're sorry, all of our Chocolatiers are busy right now";

    return self;
}

/**
 *  In the first example we we're doing a basic integration with no customization.
 *  Here we will be modifying the language presented to the user for various popups, and changing the look of the line drawing.
 */
- (void)setup {
    
    // First grab a pointer to the SOSSessionManager singleton.
    SOSSessionManager *sos = [SOSSessionManager sharedInstance];
    SOSScreenAnnotations *annotations = [sos annotations];
    
    self.email = @"tester@example.com";
    [self setupMessages];
    
    [annotations setLineWidth:18.f]; // this changes the width of the line drawn by the agent
    [annotations setLineColor:[UIColor magentaColor]]; // this changes the color of the line drawn by the agent
}

- (void)setupMessages {
    SOSSessionManager *sos = [SOSSessionManager sharedInstance];
    SOSUIComponents *components = [sos uiComponents];

    [components setAlertTitle:self.alertTitle]; // Sets the title used for UI Alerts.
    [components setConnectMessage:self.connectMessage];
    [components setDisconnectMessage:self.disconnectMessage];
    [components setAgentDisconnectMessage:self.agentDisconnectMessage];
    
    [components setConnectionRetryMessage:self.retryMessage];
    [components setConnectionTimedOutMessage:self.timeoutMessage];
    
    
}
- (void)setSessionOptions:(NSDictionary*)options {
    if ([options objectForKey:@"account"] != nil) {
        self.account = [options objectForKey:@"account"];
    }
    if ([options objectForKey:@"app"] != nil) {
        self.app = [options objectForKey:@"app"];
    }
    if ([options objectForKey:@"email"] != nil) {
        self.email = [options objectForKey:@"email"];
    }
    if ([options objectForKey:@"retry"] != nil) {
        self.retrySeconds = [[options objectForKey:@"retry"] intValue];
    }

    if ([options objectForKey:@"expire"] != nil) {
        self.expireSeconds = [[options objectForKey:@"expire"] intValue];
    }

}

/**
 *  For this example we will also set the retry and expiry proprties of the options object.
 *  By default the user will be asked to retry every 30 seconds while waiting for an agent.
 *
 *  Sessions will also remain in the queue for 30 minutes unless an agent accepts, or the user cancels.
 */
- (SOSOptions *)getSessionOptions {
    
    SOSOptions *opts = [SOSOptions optionsWithAccount:self.account
                                          application:self.app
                                                email:self.email];
    
    [opts setSessionRetryTime:self.retrySeconds * 1000]; // Set the retry prompt for 10 seconds (10,000 ms)
    [opts setSessionExpireTime:self.expireSeconds * 1000]; // Have the request automatically end after 60 seconds.
    
    return opts;
}

/**
 * In the previous example, everytime we pressed an SOS button it would attempt to start a new session.
 * If you try to start a session while a session is active/connecting this would return an error.
 * In most cases it's safe to ignore this error, but our first example just tossed an alert to the user.
 *
 * Instead; let's add a check for the session state, and then prompt the user to cancel the session.
 */
- (void)startSession {
    SOSSessionManager *sos = [SOSSessionManager sharedInstance];
    if ([sos state] != SOSSessionStateInactive) {
        // We're either connecting, or are in a session already.
        
        // Calling stopSession will prompt the user to cancel the session. If they cancel, this method does nothing.
        // Otherwise it will begin the shutdown flow.
        [sos stopSession];
        return;
    }
    
    SOSOptions *opts = [self getSessionOptions];
    [sos startSessionWithOptions:opts completion:^(NSError *error, SOSSessionManager *sos) {
        if (error) {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error"
                                                            message:[error localizedDescription]
                                                           delegate:nil
                                                  cancelButtonTitle:@"Ok"
                                                  otherButtonTitles:nil];
            
            [alert show];
        }
    }];
}

#pragma mark - Singleton

+ (instancetype)sharedInstance {
    static id instance;
    static dispatch_once_t once;
    
    dispatch_once(&once, ^{
        instance = [[self alloc] init];
    });
    
    return instance;
}

@end