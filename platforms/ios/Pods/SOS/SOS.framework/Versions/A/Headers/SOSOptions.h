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

/**
 *  The SOSOptions object allows the developer to configure the behavior of any <SOSSessionManager> session.
 *
 *  The options set on an object determines how the SOS session is routed.
 */
@interface SOSOptions : NSObject

///---------------------------------
/// @name Initialization
///---------------------------------

/**
 *  Instantiates an SOSOptions object for use with [SOSSessionManager startSessionWithOptions completion:]
 *
 *  @param account     The GoInstant Account which will be used for session orchestration with the support agents.
 *  @param application The GoInstant Application which will be used for session orchestration with the support agents.
 *  @param email       The email which will be used as a unique identifier for customer support cases.
 *
 *  @return SOSOptions instance
 */
+ (instancetype)optionsWithAccount:(NSString *)account application:(NSString *)application email:(NSString *)email;



///---------------------------------
/// @name GoInstant Information
///---------------------------------

/**
 *  The GoInstant Account which will be used for session orchestration with the support agents.
 */
@property NSString *account;

/**
 *  The GoInstant Application which will be used for session orchestration with the support agents.
 */
@property NSString *application;

///---------------------------------
/// @name User Information
///---------------------------------

/**
 *  The email which will be used as a unique identifier for customer support cases.
 */
@property NSString *email;

/**
 *  The length of time (ms) an SOS session will wait before an agent responds.
 *  If an agent hasn't responded in this time the session will terminate.
 */
@property NSTimeInterval sessionExpireTime;

/**
 *  The length of time (ms) before SOS will prompt the user to retry or cancel.
 */
@property NSTimeInterval sessionRetryTime;

@end
