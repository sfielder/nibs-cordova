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
#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKit.h>

/**
 *  Delegate protocol for SOSScreenSharing
 */
@protocol SOSScreenSharingDelegate <NSObject>

/**
 *  Delegate method invoked when a screen has been captured.
 *
 *  This will be invoked after a screen has been captured.
 *
 *  __NOTE__: This will NOT be executed on the main queue.
 *
 *  @param sos SOSSessionManager instance which invoked the delegate method.
 */
- (void)screenDidCapture:(__weak UIImage *)screen;

@end

/**
 *  Interface for configuring screen sharing behavior.
 */
@interface SOSScreenSharing: NSObject

/**
 *  If enabled, will allow sharing of the current screen context to a connected service agent.</br>
 *  Default: `YES`
 *
 *  __NOTE:__ if you set this to `NO` while screen sharing is active, it will execute <[SOSScreenSharing stop]>.
 */
@property BOOL enabled;

/**
 *  NSMutableArray of views that we exclude while capturing the screen.
 */
@property (nonatomic) NSMutableArray *excludeViews;

/**
 *  Length of time in milliseconds between screen updates
 */
@property (nonatomic, readonly) NSNumber *captureInterval;

/**
 *  Initiates screen capturing.
 *
 *  if <enabled> is `NO` then this function will do nothing.
 */
- (void)start;

/**
 *  Disables screen capturing.
 *
 *  Screen captures are handled asynchronously. If a capture is in progress it will continue. However no further activity will occur.
 */
- (void)stop;

///---------------------------------
/// @name Delegate Management
///---------------------------------

/**
 *  Add an instance of an NSObject implementing the <SOSScreenSharingDelegate> protocol to the list of delegates to notify.
 *
 *  @param delegate NSObject instance to add.
 */
- (void)addDelegate:(id<SOSScreenSharingDelegate>)delegate;

/**
 *  Remove an instance of an NSObject implementing the <SOSScreenSharingDelegate> protocol to the list of delegates to notify.
 *
 *  @param delegate NSObject instance to remove.
 */
- (void)removeDelegate:(id<SOSScreenSharingDelegate>)delegate;

/**
 *  Remove all delegates.
 */
- (void)removeAllDelegates;

@end