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
@class GIRoom;

/**
 *  Signature for the completion block used in GIConnection connect methods.
 *
 *  @param error      NSError returned if there was a problem with the operation. error will be nil if the operation was successful.
 *  @param connection Instance of the GIConnection object which performed the operation.
 */
typedef void (^GIConnectionHandler)(NSError *error, GIConnection *connection);

/**
 *  Signature for the completion block used in GIConnection connectAndJoinRoom methods.
 *
 *  @param error      NSError returned if there was a problem with the operation. error will be nil if the operation was successful.
 *  @param connection Instance of the GIConnection object which performed the operation.
 *  @param room       Instance of the GIRoom.
 */
typedef void (^GIConnectionRoomHandler)(NSError *error, GIConnection *connection, GIRoom *room);

/**
 *  Signature for the completion block used in GIConnection rooms methods.
 *
 *  @param error NSError returned if there was a problem with the operation. error will be nil if the operation was successful.
 *  @param rooms NSArray containing instances of all connected rooms.
 */
typedef void (^GIConnectionRoomsHandler)(NSError *error, NSArray *rooms);

/**
 *  Observer protocol for GIConnection events.
 */
@protocol GIConnectionObserver<NSObject>
@optional
- (void)connectionDidConnect:(GIConnection *)connection;
- (void)connectionDidDisconnect:(GIConnection *)connection willReconnect:(BOOL)willReconnect;
- (void)connectionDidError:(NSError*)error connection:(GIConnection *)connection;
@end

/**
 *  Real-time connections to GoInstant servers are established via our Objective-C API.
 *  The Connection object is the root object you'll use for accessing and manipulating GoInstant.
 *
 *  To get started, all you need is an application URL.
 *  You will have received this URL after signing up and creating an application,
 *  e.g. https://goinstant.net/YOURACCOUNT/YOURAPP
 *
 *  In order to connect as a known user, however, you must generate a JWT (a.k.a. "token") for the current user.
 */
@interface GIConnection : NSObject

///---------------------------------
/// @name Initializing a GIConnection
///---------------------------------

+ (instancetype)connectionWithConnectUrl:(NSURL *)connectUrl;
- (instancetype)initWithConnectUrl:(NSURL *)connectUrl;

///---------------------------------
/// @name Properties
///---------------------------------

/**
 *  GoInstant server hostname.
 */
@property (nonatomic, readonly) NSString *host;

/**
 *  The account the connection is using.
 */
@property (nonatomic, readonly) NSString *account;

/**
 *  The application the connection is using.
 */
@property (nonatomic, readonly) NSString *app;

///---------------------------------
/// @name Dispatch Queues
///---------------------------------

/**
 *  Dispatch queue used for completion blocks. This queue is used for all GoInstant objects which run through GIConnection.
 *  If no queue is set, the main queue is used.
 *
 *  @see GIChannel
 *  @see GIKey
 *  @see GIRoom
 */
@property (nonatomic, strong) dispatch_queue_t completionQueue;

/**
 *  Dispatch group used for completion blocks. This queue is used for all GoInstant objects which run through GIConnection.
 *  If no group is set a private dispatch_group is used.
 *
 *  @see GIChannel
 *  @see GIKey
 *  @see GIRoom
 */
@property (nonatomic, strong) dispatch_group_t completionGroup;

///---------------------------------
/// @name Instance Methods
///---------------------------------

/**
 *  Establish a connection with GoInstant using the provided account and app.
 *
 *  Will call connectionDidConnect on subscribed observers if successful.
 *
 *  Will call connectionDidError subscribed observers if the connection was unsuccessful.
 *
 *  @see GIConnectionObserver
 */
- (void)connect;

/**
 *  Establish a connection with GoInstant using the provided account and app.
 *
 *  Will call connectionDidConnect on subscribed observers if successful.
 *
 *  Will call connectionDidError subscribed observers if the connection was unsuccessful.
 *
 *  @see GIConnectionObserver
 *  @param block GIConnectionHandler completion block.
 */
- (void)connectWithCompletion:(GIConnectionHandler)block;

/**
 *  Establish a connection with GoInstant using the provided account and app.
 *
 *  Will call connectionDidConnect on subscribed observers if successful.
 *
 *  Will call connectionDidError subscribed observers if the connection was unsuccessful.
 *
 *  @see GIConnectionObserver
 *  @param jwt JWT used for user authentication. Must be a valid base64 encoded string. Cannot be nil.
 */
- (void)connectWithJwt:(NSString *)jwt;

/**
 *  Establish a connection with GoInstant using the provided account and app.
 *
 *  Will call connectionDidConnect on subscribed observers if successful.
 *
 *  Will call connectionDidError subscribed observers if the connection was unsuccessful.
 *
 *  @see GIConnectionObserver
 *  @param jwt JWT used for user authentication. Must be a valid base64 encoded string. Cannot be nil.
 *  @param block GIConnectionHandler completion block.
 */
- (void)connectWithJwt:(NSString *)jwt completion:(GIConnectionHandler)block;


- (void)connectAndJoinRoom:(NSString *)room completion:(GIConnectionRoomHandler)block;
- (void)connectAndJoinRoom:(NSString *)room jwt:(NSString *)jwt completion:(GIConnectionRoomHandler)block;

- (void)disconnect;
- (void)disconnectWithCompletion:(void (^)(NSError *error))block;

- (GIRoom *)roomWithName:(NSString *)name;
- (void)roomsWithCompletion:(GIConnectionRoomsHandler)block;

- (void)subscribe:(id<GIConnectionObserver>)observer;
- (void)unsubscribe:(id<GIConnectionObserver>)observer;
- (void)unsubscribeAll;

- (BOOL)isEqualToConnection:(GIConnection *)connection;



@end
