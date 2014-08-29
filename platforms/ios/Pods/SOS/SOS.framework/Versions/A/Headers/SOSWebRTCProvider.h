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
#import <UIKit/UIKit.h>
#import <GoInstant/GoInstant.h>

/**
 *  Full list of valid states for the WebRTC provider
 */
typedef NS_ENUM(NSInteger, SOSWebRTCState) {
  /**
   *  No active session. There should be no network traffic of any kind.
   */
  SOSWebRTCStateInactive = 0,

  /**
   *  Attempting a connection to WebRTC services.
   */
  SOSWebRTCStateConnecting = 1,

  /**
   *  Current connection is paused. Expeced behavior is that audio/video feeds are either disabled or stalled.
   *  The session needs to be in a state where 'unpausing' will resume audio/video feeds immediately.
   */
  SOSWebRTCStatePaused = 2,

  /**
   *  A full connection has been created to the WebRTC services.
   */
  SOSWebRTCStateActive = 3
};

/**
 *  Full list of valid settings used for SOS
 */
typedef NS_OPTIONS(NSUInteger, SOSWebRTCSetting) {
  /**
   *  When added, enables incoming video to be rendered on screen.
   */
  SOSWebRTCSettingIncomingVideoEnabled = 1 << 0
};

/**
 *  Delegate protocol for SOSWebRTCProvider
 */
@protocol SOSWebRTCDelegate<NSObject>
@optional

/**
 *  Delegate method invoked when the SOSWebRTCProvider state changes.
 *
 *  @param provider SOSWebRTCProvider instance which invoked the delegate method.
 *  @param current  The new <SOSWebRTCState> which has been set on the SOSWebRTCProvider instance.
 *  @param previous The previous <SOSWebRTCState>
 */
- (void)provider:(__weak id)provider stateDidChange:(SOSWebRTCState)current previous:(SOSWebRTCState)previous;

/**
 *  Delegate method invoked when the SOSWebRTCProvider has successfully connected.
 *
 *  @param provider    SOSWebRTCProvider instance which invoked the delegate method.
 *  @param sessionData NSDictionary returned which contains any relavant session specific data.
 */
- (void)provider:(__weak id)provider sessionDidConnect:(NSDictionary *)sessionData;

/**
 *  Delegate method invoked if the session received a channel message.
 *
 *  @param provider SOSWebRTCProvider instance which invoked the delegate method.
 *  @param type     The type of message received.
 *  @param data     The actual data received.
 */
- (void)provider:(__weak id)provider sessionDidReceiveMessageType:(NSString*)type WithData:(NSString*)data;

/**
 *  Delegate method invoked if an error is raised during an active SOSWebRTCProvider session.
 *
 *  @param provider SOSWebRTCProvider instance which invoked the delegate method.
 *  @param error    NSError instance describing the error.
 */
- (void)provider:(__weak id)provider didError:(NSError *)error;

@end

/**
 *  Standard protocol for WebRTC provider SDKs. All providers must strictly conform to this protocol to be valid in use with SOS.
 */
@protocol SOSWebRTCProvider <NSObject>

/**
 *  The UIView which will be treated as the superview for all SOSWebRTCProvider UI elements.
 *
 *  @warning You must ensure that this property is set to a valid UIView or nil __before__ releasing the attached view.
 */
@property (nonatomic, weak) UIView *view;

/**
 *  The UIView used to display the remote feed for the WebRTC session.
 */
@property (nonatomic, readonly, weak) UIView *remoteView;

/**
 *  The pixel dimensions of the video view
 */
@property (readonly) CGSize videoSize;

/**
 *  Screen coordinates of the center of the video view
 */
@property (nonatomic) CGPoint videoPosition;

/**
 *  Unique session ID.
 */
@property (nonatomic) NSString *sessionId;


/**
 *  A bit-flag to store WebRTC-specific settings used for sessions.
 */
@property SOSWebRTCSetting settings;


/**
 *  Add an <SOSWebRTCSetting>.
 *
 *  @param flag The <SOSWebRTCSetting> to be added/enabled.
 */
- (void)addSetting:(SOSWebRTCSetting)flag;

/**
 *  Check whether an <SOSWebRTCSetting> has been added.
 *
 *  @param flag The <SOSWebRTCSetting> being checked for.
 *
 *  @return Whether or not the <SOSWebRTCSetting> has been set.
 */
- (BOOL)containsSetting:(SOSWebRTCSetting)flag;

/**
 *  Remove an <SOSWebRTCSetting>.
 *
 *  @param flag The <SOSWebRTCSetting> being removed.
 */
- (void)removeSetting:(SOSWebRTCSetting)flag;

///---------------------------------
/// @name Initialization
///---------------------------------

- (instancetype)init;

///---------------------------------
/// @name Session Management
///---------------------------------

/**
 *  Starts a WebRTC session with the provider.
 *
 *  Expected implementation would call <[SOSWebRTCProvider startWithCompletion:]> nil.
 *
 *  @see [SOSWebRTCProvider startWithCompletion:]
 */
- (void)start;

/**
 *  Starts a WebRTC session with the provider.
 *
 *  A class implementing this method must handle the completion block appropriately. The error returned must be `nil` if and only if there were no errors.
 *  Additionally a `nil` block is valid, and must be handled gracefully.
 *
 *  #### Delegate Methods:
 *  A valid implementation will invoke all listed delegate methods in the described circumstances.
 *
 *  - <[SOSWebRTCDelegate provider:sessionStatusDidChange:previous:]><br/>
 *    Invoked at each state change.
 *  - <[SOSWebRTCDelegate provider:didError:]><br/>
 *    Invoked if there is an error at any point during the lifetime of a session.
 *
 *  @param block Completion block which will be called back after connecting to the WebRTC provider service.<br/>
 *                __NOTE:__ the NSError returned in the block will be `nil` on success.
 *                __NOTE:__ the NSDictionary returned will contain any relavant session specific data.
 */
- (void)startWithCompletion:(void (^)(NSError *error, NSDictionary *sessionData))block;

/**
 *  stops the current WebRTC session.
 *
 *  Expected implementation would call <[SOSWebRTCProvider stopWithCompletion:]> nil.
 *
 *  @see [SOSWebRTCProvider stopWithCompletion:]
 */
- (void)stop;

/**
 *  stops the current WebRTC session.
 *
 *  A class implementing this method must handle the completion block appropriately. The error returned must be `nil` if and only if there were no errors.
 *  Additionally a `nil` block is valid, and must be handled gracefully.
 *
 *  #### Delegate Methods:
 *  A valid implementation will invoke all listed delegate methods in the described circumstances.
 *
 *  - <[SOSWebRTCDelegate provider:sessionStatusDidChange:previous:]><br/>
 *    Invoked at each state change.
 *  - <[SOSWebRTCDelegate provider:didError:]><br/>
 *    Invoked if there is an error at any point during the lifetime of a session.
 *
 *  @param block Completion block which will be called back after fully tearing down the active session.<br/>
 *                __NOTE:__ the NSError returned in the block will be `nil` on success.
 */
- (void)stopWithCompletion:(void (^)(NSError *error))block;

/**
 *  Pauses a WebRTC session.
 *
 *  Expected implementation would call <[SOSWebRTCProvider pauseWithCompletion:]> nil.
 *
 *  @see [SOSWebRTCProvider pauseWithCompletion:]
 */
- (void)pause;

/**
 *  Pauses a WebRTC session.
 *
 *  A class implementing this method must handle the completion block appropriately. The error returned must be `nil` if and only if there were no errors.
 *  Additionally a `nil` block is valid, and must be handled gracefully.
 *
 *  #### Delegate Methods:
 *  A valid implementation will invoke all listed delegate methods in the described circumstances.
 *
 *  - <[SOSWebRTCDelegate provider:sessionStatusDidChange:previous:]><br/>
 *    Invoked at each state change.
 *  - <[SOSWebRTCDelegate provider:didError:]><br/>
 *    Invoked if there is an error at any point during the lifetime of a session.
 *
 *  @param block Completion block which will be called back after pausing to the WebRTC session.<br/>
 *                __NOTE:__ the NSError returned in the block will be `nil` on success.
 */
- (void)pauseWithCompletion:(void (^)(NSError *error))block;

/**
 *  Send a volatile message over the provider's data channel to the agent.
 *
 *  @param type The type of message.
 *  @param data The actual message data.
 */
- (void)sendChannelMessageType:(NSString*)type WithData:(NSString*)data;

///---------------------------------
/// @name Delegate Management
///---------------------------------

/**
 *  Add an instance of an NSObject implementing the <SOSWebRTCDelegate> protocol to the list of delegates to notify.
 *
 *  @param delegate NSObject instance to add.
 */
- (void)addDelegate:(id<SOSWebRTCDelegate>)delegate;

/**
 *  Remove an instance of an NSObject implementing the <SOSWebRTCDelegate> protocol to the list of delegates to notify.
 *
 *  @param delegate NSObject instance to remove.
 */
- (void)removeDelegate:(id<SOSWebRTCDelegate>)delegate;

/**
 *  Remove all delegates.
 */
- (void)removeAllDelegates;

@end

