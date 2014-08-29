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

@class SOSAgentVideoView;

/**
 *  Custom segue class requried to allow story board connections.
 */
@interface SOSSegue : UIStoryboardSegue
- (void) perform;
@end

/**
 *  A UIViewController which is used to manage screen sharing of all child view controllers.
 *
 *  This ViewController is designed to separate all UI elements that SOS will add to your application away from your application's view hierarchy.
 *  This is to ensure that including SOS will not have any unexpected side effects in your view hierarchy, and to ensure that your application is
 *  generally compatible with SOS.
 *
 *  It is __HIGHLY__ recommended that the SOSContainerViewController is the root view controller for your application window. This can be accomplished in two ways:
 *
 *  1. Programmatically.
 *  2. Via the storyboard as a UIView controller.
 *
 *  # Programmatically
 *  Refer to the following code snippet. The optimal place to add this code is in your AppDelegate didFinishLaunchingWithOptions:.
 *
 *
 *  ```
 *  #import <SOS/SOS.h>
 *
 *  @implementation AppDelegate
 *
 *  - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 *  {
 *    SOSContainerViewController *_root = [[SOSContainerViewController alloc] initWithViewController:[_window rootViewController]];
 *    [_window setRootViewController:_root];
 *
 *    return YES;
 *  }
 *
 *  @end
 *  ```
 *
 *  # Via the StoryBoard
 *
 *  - Add Create a new ViewController object in your scene.
 *  
 *  ![Step-1](../static/img/storyboard/step-1.png =1226x761)
 *
 *  - Ensure that this new storyboard is the `Initial View Controller`
 *
 *  ![Step-2](../static/img/storyboard/step-2.png =296x367)
 *
 *  - Select <SOSContainerViewController> from the custom class dropdown. If it's not listed you can enter it yourself.
 *
 *  ![Step-3](../static/img/storyboard/step-3.png =296x201)
 *
 *  - ctrl+click on your new view controller and drag a line to your application view controller. This will add a segue. Select `custom`.
 *
 *  ![Step-4](../static/img/storyboard/step-4.png =1226x761)
 *
 *  - Click on the new segue.
 *
 *  ![Step-5](../static/img/storyboard/step-5.png =611x554)
 *
 *  - Type `SOS` (case specific) as your `Identifier`, and choose `SOSSegue` as your custom class. Again if it's not present in the dropdown just enter it manually.
 *
 *  ![Step-6](../static/img/storyboard/step-6.png =297x208)
 *
 *  All of your application hierarchy can now be added to your view controller. (Titled `MyApp` in the example). It is __recommended__ that you do __not__ modify the
 *  SOSContainerViewController at all.
 */
@interface SOSContainerViewController : UIViewController

/**
 *  Initializes an SOSContainerViewController instance.
 *
 *  This initializer is intended to be used if you wish to manage your view hierarchy programmatically.
 *  It is recommended that the SOSContainerViewController is the rootViewController for your application UIWindow.
 *
 *  @warning the SOSContainerViewController is a strict singleton. Attempting to instantiate multiple instances
 *  or calling this method if the SOSContainerViewController has been added to your application storyboard will raise an error.
 *
 *  @return SOSContainerViewController instance.
 */
- (id)initWithViewController:(UIViewController *)viewController;

/**
 *  Return shared SOSContainerViewController instance.
 *
 *  @warning Since class is designed to be instantiated either programmatically or via the storyboard.
 *
 *  @return shared SOSContainerViewController instance.
 */
+ (id)sharedInstance;

/**
 *  UIView in which all SOS views are added.
 *
 *  This property is available for application introspection purposes.
 *  It is recommended that you do __not__ modify this window.
 */
@property (readonly) UIView *sosView;

/**
 *  SOSAgentVideoView is a subclass of a UIView, which contains the UI for the agent video widget, and it's buttons (mute microphone and end session).
 */
@property (readonly) SOSAgentVideoView *sosAgentVideoView;

@end
