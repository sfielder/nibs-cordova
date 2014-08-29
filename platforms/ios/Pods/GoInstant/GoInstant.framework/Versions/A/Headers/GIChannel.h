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

@class GIRoom;
@class GIChannel;
@class GIValue;
@class GIUser;
@class GIOptions;

/**
 *  Signature for the completion block used in GIChannel methods.
 *
 *  @param error NSError returned if there was a problem with the operation. error will be nil if the operation was successful.
 */
typedef void (^GIChannelHandler)(NSError *error);

/**
 *  Observer protocol for GIChannel events.
 */
@protocol GIChannelObserver<NSObject>
@optional

/**
 *  Observer for messages sent to this GIChannel.
 *
 *  @param channel GIChannel instance which received the message.
 *  @param message The message sent to the channel. Will be an NSString, NSDictionary, NSNumber, NSArray or nil
 *  @param userId  GIUser who sent the message.
 */
- (void)channel:(GIChannel *)channel didReceiveMessage:(id)message fromUser:(GIUser *)userId;
@end

/**
 *  A Channel is a full-duplex messaging interface for broadcasting to all users in a room that are listening to that channel.
 *  Unlike a Key, a Channel does not store state, so you cannot retrieve the previous messages from the channel.
 */
@interface GIChannel : NSObject

///---------------------------------
/// @name Initializing a GIChannel
///---------------------------------

/**
 *  Returns a GIChannel initialized with the channelName provided.
 *
 *  @param channelName The name of the channel.
 *  @param room The room the channel belongs to.
 *
 *  @return A GIChannel object which has been initialized with channelName.
 */
+ (instancetype)channelWithName:(NSString *)channelName room:(GIRoom *)room;

/**
 *  Returns a GIChannel initialized with the given channelName.
 *
 *  @param channelName The name of the channel.
 *  @param room The room the channel belongs to.
 *
 *  @return A GIChannel object which has been initialized with channelName.
 */
- (instancetype)initWithName:(NSString *)channelName room:(GIRoom *)room;

///---------------------------------
/// @name Properties
///---------------------------------

/**
 *  The name of the channel.
 */
@property (nonatomic, readonly) NSString *name;

/**
 *  Instance of the GIRoom this channel will send messages through.
 */
@property (nonatomic, readonly, weak) GIRoom *room;

///---------------------------------
/// @name Instance Methods
///---------------------------------

/**
 *  Send a message
 *
 *  @param message NSObject data type. (NSString, NSDictionary, NSNumber, or nil)
 */
- (void)sendMessage:(id)message;

/**
 *  Send a message
 *
 *  @param message NSObject data type. (NSString, NSDictionary, NSNumber, or nil)
 *  @param options GIOptions which describes channel behavior for this message.
 */
- (void)sendMessage:(id)message options:(GIOptions *)options;

/**
 *  Send a message
 *
 *  @param message NSObject data type. (NSString, NSDictionary, NSNumber, or nil)
 *  @param block GIChannelHandler completion block.
 */
- (void)sendMessage:(id)message completion:(GIChannelHandler)block;

/**
 *  Send a message
 *
 *  @param message NSObject data type. (NSString, NSDictionary, NSNumber, or nil)
 *  @param options GIOptions which describes channel behavior for this message.
 *  @param block GIChannelHandler completion block.
 */
- (void)sendMessage:(id)message options:(GIOptions *)options completion:(GIChannelHandler)block;

/**
 *  Subscribe an instance of GIChannelObserver to the channel.
 *  Observers will be held a s a weak reference to the given object.
 *
 *  @param observer NSObject implementing the GIChannelObserver protocol
 */
- (void)subscribe:(id<GIChannelObserver>)observer;

/**
 *  Remove a given object from the list of observers.
 *
 *  @param observer NSObject implementing the GIChannelObserver protocol.
 */
- (void)unsubscribe:(id<GIChannelObserver>)observer;

/**
 *  Remove all observers.
 */
- (void)unsubscribeAll;

/**
 *  Equality operation.
 *
 *  @param channel GIChannel to compare against.
 *
 *  @return whether or not the given channel is equivalent.
 */
- (BOOL)isEqualToChannel:(GIChannel *)channel;

@end
