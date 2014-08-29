/*
 * Copyright (c) 2014, GoInstant Inc., a salesforce.com company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of the {organization} nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Foundation/Foundation.h>
#import <GoInstant/GoInstant.h>
#import <UIKit/UIKit.h>

#import "SOSWebRTCProvider.h"

@class SOSScreenAnnotations;
@class SOSScreenSharing;
@class SOSSessionManager;
@class SOSUIComponents;
@class SOSAgentVideoView;
@class SOSOptions;
@class SOSMasking;

typedef void (^SOSCompletionHandler)(NSError *error, SOSSessionManager *sos);

/**
 * Full list of Session states the SOS framework can exhibit.
 */
typedef NS_ENUM(NSInteger, SOSSessionState) {
  /**
    *  No active session. There will be no outgoing/incoming SOS traffic.
    */
  SOSSessionStateInactive = 0,

  /**
   *  Session state is initializing and preparing to connect.
   */
  SOSSessionStateInitializing = 1,

  /**
    *  Session is attempting a connection to a live agent.
    */
  SOSSessionStateConnecting = 2,

  /**
    *  Live agent has connected and the session is fully active.
    */
  SOSSessionStateActive = 3
};

/**
 *  Delegate protocol for SOSSessionManager
 */
@protocol SOSDelegate<NSObject>
@optional
/**
 *  Delegate method invoked when the SOS session has connected.
 *
 *  @param sos SOSSessionManager instance which invoked the delegate method.
 */
- (void)sosDidConnect:(SOSSessionManager *)sos;

/**
 *  Delegate method invoked when the SOS session has disconnected.
 *
 *  @param sos SOSSessionManager instance which invoked the delegate method.
 */
- (void)sosDidDisconnect:(SOSSessionManager *)sos;

/**
 *  Delegate method invoked when first starting an SOS session.
 *
 *  This method will be executed once the SOS Session has begun to initialize a connection.
 *
 *  @param sos SOSSessionManager instance which invoked the delegate method.
 */
- (void)sosDidStart:(SOSSessionManager *)sos;

/**
 *  Delegate method invoked when first attempting to stop an SOS session.
 *
 *  This will be executed once the session has been completely stopped.
 *
 *  @param sos SOSSessionManager instance which invoked the delegate method.
 */
- (void)sosDidStop:(SOSSessionManager *)sos;

/**
 *  Delegate method invoked when an agent accepts an SOS session request.
 *
 *  @param sos SOSSessionManager instance which invoked the delegate method.
 */
- (void)sosAgentJoined:(SOSSessionManager *)sos;

/**
 *  Delegate method invoked if an error is raised during an active SOS session.
 *
 *  @param sos   SOSSessionManager instance which invoked the delegate method.
 *  @param error NSError instance describing the error.
 */
- (void)sos:(SOSSessionManager *)sos didError:(NSError*)error;

/**
 *  Delegate method invoked when the SOS state changes.
 *
 *  @param sos      SOSSessionManager instance which executed the delegate.
 *  @param current  The new <SOSSessionState> which has been set on the SOSSessionManager instance.
 *  @param previous The previous <SOSSessionState>.
 */
- (void)sos:(SOSSessionManager *)sos stateDidChange:(SOSSessionState)current previous:(SOSSessionState)previous;
@end

/**
 *  The SOSSessionManager object is main interface to the SOS framework.
 *
 *  The SOSSessionManager object is used to manage the flow of any number of SOS sessions throughout the lifetime of the app.
 *  Configuration and customization of the SOS framework is handled through the public properties on the SOSSessionManager instance.
 *
 *  The SOSSessionManager conforms to a Multi-cast delegate model for messaging. Any class which implements the <SOSSessionManagerDelegate> protocol
 *  can be added to a list of delages to receive messages asynchronously.
 */
@interface SOSSessionManager: NSObject<GIChannelObserver, GIKeyObserver, SOSWebRTCDelegate>

///---------------------------------
/// @name SOS Management Objects
///---------------------------------

/**
 *  Public reference to the <SOSScreenAnnotations> instance used by the SOS framework.
 */
@property (readonly) SOSScreenAnnotations *annotations;

/**
 *  Public reference to the <SOSScreenSharing> instance used by the SOS framework.
 */
@property (readonly) SOSScreenSharing *screenShare;

/**
 *  Public reference to the <SOSUIComponents> instance used by the SOS framework.
 */
@property (readonly) SOSUIComponents *uiComponents;

/**
 *  Public reference to the <SOSWebRTCProvider> instance used by the SOS framework.
 */
@property (readonly) id<SOSWebRTCProvider> provider;

///---------------------------------
/// @name Other Properties
///---------------------------------

/**
 *  The current SOSSessionState.
 */
@property (readonly) SOSSessionState state;

///---------------------------------
/// @name Initialization
///---------------------------------

/**
 *  Shared Singleton <SOSSessionManager> instance.
 *
 *  @return singleton <SOSSessionManager> instance.
 */
+ (instancetype)sharedInstance;

///---------------------------------
/// @name Session Management
///---------------------------------

/**
 *  Starts the process for creating an SOS session.
 *
 *  Equivalent to invoking <[SOSSessionManager startSessionWithOptions completion:]> and providing a `nil` block.
 *
 *  @param options <SOSOptions> object that determines the behavior of this session
 *
 *  @see [SOSSessionManager startSessionWithOptions completion:]
 */
- (void)startSessionWithOptions:(SOSOptions *)options;

/**
 *  Starts the process for creating an SOS session.
 *
 *  By default the user will be given a prompt asking if they would like to initiate an SOS session. This behavior
 *  as well as other default UI behavior can be configured via the <uiComponents> property.
 *
 *  #### Delegate Methods:
 *  - <[SOSDelegate sosDidConnect:]><br/>
 *    Invoked when all session handshakes and negotiations have completed. The session is fully connected now.
 *  - <[SOSDelegate sosAgentJoined:]><br/>
 *    Invoked when an agent has accepted the sos request. Final handshakes and web rtc initialization is started.
 *  - <[SOSDelegate sosDidStart:]><br/>
 *    Invoked when the session has begun negotiating with required services.
 *  - <[SOSDelegate sos:stateDidChange:previous:]><br/>
 *    Invoked at each state change.
 *  - <[SOSDelegate sos:didError:]></br>
 *    Invoked if there is an error at any point during the lifetime of a session.
 *
 *  #### Customizing UI Behavior:
 *  - <[SOSUIComponents setAlertsEnabled:]><br/>
 *    Set this to `NO` to disable UIAlerts and prompts.
 *  - <[SOSUIComponents setProgressHudEnabled:]><br/>
 *    Set this to `NO` to disable HUD progress tracking.
 *
 *  @see SOSDelegate
 *  @see SOSUIComponents
 *
 *  @param options <SOSOptions> object that determines the behavior of this session
 *  @param block Completion block which will be executed when the session has been fully connected to all services.</br>
 *                __NOTE:__ at this point the session is active and waiting for an agent to join.<br/>
 *                __NOTE:__ the NSError returned in the block will be `nil` on success.
 */
- (void)startSessionWithOptions:(SOSOptions *)options completion:(SOSCompletionHandler)block;

/**
 *  Begins a teardown of an SOS Session.
 *
 *  Equivalent to invoking <[SOSSessionManager stopSessionWithCompletion:]> and providing a `nil` block.
 *
 *  @see [SOSSessionManager stopSessionWithCompletion:]
 */
- (void)stopSession;

/**
 *  Begins a teardown of an SOS Session.
 *
 *  By default the user will be given a prompt asking if they would like to stop the SOS session. This behavior
 *  as well as other default UI behavior can be configured via the <uiComponents> property.
 *
 *  #### Delegate Methods:
 *  - <[SOSDelegate sosDidDisconnect:]></br>
 *    Invoked when the session has disconnected from all services. The SOS framework at this poing will cease all network activity.
 *  - <[SOSDelegate sosDidStop:]></br>
 *    Invoked when the session has been fully torn down.
 *  - <[SOSDelegate sos:stateDidChange:previous:]><br/>
 *    Invoked at each state change.
 *  - <[SOSDelegate sos:didError:]></br>
 *    Invoked if there is an error at any point during the lifetime of a session.
 *
 *  @see SOSDelegate
 *  @see SOSUIComponents
 *
 *  @param block Completion block wich will be executed when the session has fully stopped, and all connected services have been torn down.<br/>
 *                __NOTE:__ the NSError returned in the block will be `nil` on success.
 */
- (void)stopSessionWithCompletion:(SOSCompletionHandler)block;

///---------------------------------
/// @name Delegate Management
///---------------------------------

/**
 *  Add an instance of an NSObject implementing the <SOSDelegate> protocol to the list of delegates to notify.
 *
 *  @param delegate NSObject instance to add.
 */
- (void)addDelegate:(id<SOSDelegate>)delegate;

/**
 *  Remove an instance of an NSObject implementing the <SOSDelegate> protocol to the list of delegates to notify.
 *
 *  @param delegate NSObject instance to remove.
 */
- (void)removeDelegate:(id<SOSDelegate>)delegate;

/**
 *  Remove all delegates.
 */
- (void)removeAllDelegates;

@end
