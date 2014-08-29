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

@interface SOSScreenAnnotations: NSObject <GIChannelObserver, SOSWebRTCDelegate>

/**
 *  If enabled, will allow drawing on the current screen by the service agent.</br>
 *  Default: `YES`
 *
 *  __NOTE:__ if you set this to `NO` while screen sharing is active, it will execute <[SOSScreenAnnotations stop]>.
 */
@property BOOL enabled;

/**
 *  When enabled all touch events will clear the screen of annotations.</br>
 *  If you wish to handle clearing annotations yourself set this to `NO`.
 *
 *  Default: `YES`
 */
@property BOOL clearOnTouches;

/**
 *  Customizable color of the line drawing feature.
 *  Will not change the color of existing lines on the screen.
 *
 *  Default: [UIColor redColor]
 */
@property (nonatomic) UIColor *lineColor;

/**
 *  Customizable width of the line drawing feature.
 *  Will not change the width of existing lines on the screen.
 *
 *  Default: 5.0f
 */
@property (nonatomic) CGFloat lineWidth;

/**
 *  Clears the current annotation by reinitializing the drawer.
 */
- (void)clearDraw;

/**
 *  Initiates the drawing feature
 */
- (void)start;

/**
 *  Stops the drawing feature
 */
- (void)stop;

@end
