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

@class GIConnection;
@class GIChannel;
@class GIKey;
@class GIRoom;
@class GIUser;

typedef void (^GIRoomHandler)(NSError *error);
typedef void (^GIUsersHandler)(NSError *error, NSSet *users);

@protocol GIRoomObserver<NSObject>
@optional
- (void)room:(GIRoom *)room joinedBy:(GIUser *)user;
- (void)room:(GIRoom *)room leftBy:(GIUser *)user;
@end

/**
 *  Rooms are instances of your application within GoInstant. Each room holds a number of users and keys.
 *  A user must be in a room to interact with other users or manipulate keys.
 *  A user can be in more than one room at a time using a single connection.
 *
 *  Before using a room, a user must first join it.
 *
 *  After joining the room, users can access keys, list the users in the room. When done with a room, leave it.
 *
 *  __Note:__ If a user's connection to GoInstant times out, they will automatically leave all joined rooms.
 *  The time out is set to one minute.
 */
@interface GIRoom : NSObject

+ (instancetype)roomWithName:(NSString *)name connection:(GIConnection *)connection;
- (instancetype)initWithName:(NSString *)name connection:(GIConnection *)connection;

- (void)join;
- (void)joinWithCompletion:(GIRoomHandler)block;

- (void)leave;
- (void)leaveWithCompletion:(GIRoomHandler)block;

- (GIChannel *)channelWithName:(NSString *)name;
- (GIKey *)keyWithPath:(NSString *)path;

- (void)subscribe:(id<GIRoomObserver>)observer;
- (void)unsubscribe:(id<GIRoomObserver>)observer;
- (void)unsubscribeAll;

- (BOOL)isEqualToRoom:(GIRoom *)room;

@property(nonatomic, readonly) NSString *name;
@property(nonatomic, readonly) GIConnection *connection;
@property(nonatomic, readonly) BOOL joined;
@property(nonatomic, readonly) NSDictionary *users;

@end
