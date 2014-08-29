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

#import <UIKit/UIKit.h>
#import <OpenTok/OpenTok.h>
#import "SOSSessionManager.h"

typedef NS_ENUM(NSInteger, SOSAction) {
  /**
   *  Mute local microphone.
   */
  SOSActionMuteMicrophone = 0,
  
  /**
   *  Toggle remote video stream.
   */
  SOSActionToggleRemoteVideo = 1,
  
  /**
   *  End the session.
   */
  SOSActionEndSession = 2
};

@class SOSUILabel;

@protocol SOSAgentVideoViewDelegate <NSObject>
@optional

/**
 *  Delegate method invoked when an action has ben initiated by the iOS user.
 *
 *  @param view   SOSAgentVideoView instance which invoked the delegate metod.
 *  @param action The SOSAction initiated by the user.
 */
- (void)sosAgentVideoView:(__weak id)view triggeredAction:(SOSAction)action;

/**
 *  Delegate method invoked when the video view position has been changed.
 *
 *  @param view SOSAgentVideoView instance which invoked the delegate method.
 *  @param position the new center position of the agent view in screen relative coordinates.
 */
- (void)sosAgentVideoView:(__weak id)view videoPositionDidChange:(CGPoint)position;

@end

@interface SOSAgentVideoView : UIView<UIGestureRecognizerDelegate, SOSDelegate, SOSWebRTCDelegate>

/**
 *  UIButton for muting the microphone.
 */
@property (strong, nonatomic) IBOutlet UIButton *btnAudio;

/**
 *  UIButton for toggling the remote video stream.
 */
@property (strong, nonatomic) IBOutlet UIButton *btnVideo;

/**
 *  UIButton for ending the SOS session.
 */
@property (strong, nonatomic) IBOutlet UIButton *btnClose;

/**
 *  UILabel for displaying the Agent name.
 */
@property (strong, nonatomic) IBOutlet SOSUILabel *lblName;

/**
 *  UIView subview positioned for displaying the agent video feed.
 */
@property (strong, nonatomic) IBOutlet UIImageView *viewVideo;

/**
 *  Set position of the video feed.
 */
@property (nonatomic) CGPoint videoPosition;

/**
 *  Set starting position of the center of the video widget.
 *  Default: 67,65 (half the size of the widget)
 */
@property (nonatomic) CGPoint startingVideoPosition;

///---------------------------------
/// @name Delegate Management
///---------------------------------

/**
 *  Add an instance of an NSObject implementing the <SOSAgentVideoViewDelegate> protocol to the list of delegates to notify.
 *
 *  @param delegate NSObject instance to add.
 */
- (void)addDelegate:(id<SOSAgentVideoViewDelegate>)delegate;

/**
 *  Remove an instance of an NSObject implementing the <SOSAgentVideoViewDelegate> protocol to the list of delegates to notify.
 *
 *  @param delegate NSObject instance to remove.
 */
- (void)removeDelegate:(id<SOSAgentVideoViewDelegate>)delegate;

/**
 *  Remove all delegates.
 */
- (void)removeAllDelegates;
@end
