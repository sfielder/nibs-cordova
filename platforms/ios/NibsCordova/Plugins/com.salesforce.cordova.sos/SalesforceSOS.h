#include <Cordova/CDVPlugin.h>
#import <Cordova/CDVInvokedUrlCommand.h>

@interface SalesforceSOS : CDVPlugin

- (void)setup:(CDVInvokedUrlCommand*)command;
- (void)setupMessages:(CDVInvokedUrlCommand*)command;
- (void)startSOS:(CDVInvokedUrlCommand*)command;

@end

@class SOSOptions;

// This is a header file for an example SOS Application interface class.
// Each target will have it's own implemenentation of this class. This is where the majority
// of SOS specific code will live.

/**
 * A simple example of encapsulating SOS calls to make accessing SOS from many view controllers easier.
 */
@interface SOSApplication : NSObject

- (SOSOptions *)getSessionOptions;
@property (nonatomic, strong) NSString* email;
@property (nonatomic, strong) NSString* account;
@property (nonatomic, strong) NSString* app;

@property (nonatomic, strong) NSString* alertTitle;
@property (nonatomic, strong) NSString* connectMessage;
@property (nonatomic, strong) NSString* disconnectMessage;
@property (nonatomic, strong) NSString* agentDisconnectMessage;
@property (nonatomic, strong) NSString* retryMessage;
@property (nonatomic, strong) NSString* timeoutMessage;


@property int retrySeconds;
@property int expireSeconds;

/**
 *  Provides a singleton instance to the SOS Application
 */
+ (instancetype)sharedInstance;

- (void)setSessionOptions:(NSDictionary*)options;

/**
 *  Start a session
 */
- (void)startSession;

/**
 *  <#Description#>
 */
- (void)setup;
- (void)setupMessages;

@end
