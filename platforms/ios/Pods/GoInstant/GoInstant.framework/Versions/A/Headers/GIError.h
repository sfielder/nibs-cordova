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
 *  Enum which describes all known errors which an be trigged by GoInstant operations.
 */
typedef NS_ENUM(NSInteger, GIErrorCode) {

  ///--------------------------------
  /// @name General Errors (0-series)
  ///--------------------------------

  /**
   *  Value which is used for error fields when no error has occurred.
   */
  GINoError = -1,

  /**
   *  Generic error which does not fall into current error specifications.
   */
  GIGenericError = 0,

  /**
   *  The GoInstant server has sent an illegal or malformed message. This "should not happen", so
   *  any errors of this type should be escalated to support@goinstant.com immediately.
   */
  GIProtocolError = 10,

  ///-----------------------------------
  /// @name Expected Errors (100-series)
  ///-----------------------------------

  /**
   *  Key overwrite failure
   *  Occurs when [GIOptions optionsWithOverwrite:NO] is passed to an operation that would have overwritten an already-set key (e.g. [GIKey set]).
   */
  GICollisionError = 100,

  ///--------------------------------------------
  /// @name Connection Server Errors (200-series)
  ///--------------------------------------------

  /**
   *  Bad join/leave operation
   *  Occurs when an attempt to do one of the following is made:
   *
   *  - join a Room that has already been joined by this Connection object, or
   *  - leave a Room that has previously been left by this Connection object
   */
  GIRoomSessionStateError = 200,

  /**
   *  Too many users in a Room
   *  Occurs when a Room occupancy limit has been reached. Room limits are defined by your account plan with GoInstant.
   */
  GIRoomSizeError = 201,

  /**
   *  Network-level connection problems
   *  Occurs when an unrecoverable network-level error is encountered. Examples:
   *
   *  - During initial connection establishment, a network error occurs
   *  - Hostname resolution failure
   *  - A JWT is being used, but it is -- or becomes -- invalid.
   *  - When reconnecting after a network drop-out, a timeout or retry limit is reached
   *  - An operation was interrupted due to the client becoming permanently disconnected (after reaching a retry count/time limit)
   *
   *  Note that temporary network-level disconnections are handled automatically by GoInstant; only permanent connection errors will cause this error to be emitted.
   */
  GIConnectionError = 202,

  /**
   *  Unable to authenticate
   *  Occurs when the credentials for a user could not be validated. This can happen when an invalid JWT is passed to connection.
   */
  GIAuthenticationError = 203,

  /**
   *  Unable to authorize an action
   *  Occurs when an operation is denied based on who is attempting that operation. For example, an ACL can be written to deny some users the set operation on specific keys.
   */
  GIPermissionError = 204,

  /**
   *  Not joined to the Room to which a Key belongs
   *  Occurs when the GoInstant server does extra client-request validation and finds something wrong with the request itself, e.g., the value too large, the request is malformed, etc.
   */
  GINotMemberError = 205,

  /**
   *  Connection required
   *  Occurs when an operation is attempted that requires a live connection to GoInstant. For example, if a room join is attempted without connecting this error will be returned.
   */
  GINotConnectedError = 206,

  /**
   *  Attempt to set data on a user that does not exist
   *  Occurs when attempting to operate on a User, but the User does not exist.
   */
  GINoUserError = 207,

  /**
   *  XXX: Needs doccumentation
   */
  GISynchronizationError = 208,

  ///----------------------------------
  /// @name Storage Errors (300-series)
  ///----------------------------------

  /**
   *  Key name is not valide
   *  Occurs when an invalid name is passed to the Room#key or Room#channel constructors.
   */
  GIKeyNameError = 300,

  /**
   Server-side request validation failure
   */
  GIInvalidRequestError = 301,

  /**
   *  The arguments provided with the request is invalid. The most common cause is operating on a key with an invalid name.
   */
  GIArgumentError = 302,

  GINonLeafKeyError = 303,

  GIDuplicateCallError = 304,

  GICouldNotCompleteError = 305,

  GINotInitializedError = 306,

  ///--------------------------------
  /// @name Usage Errors (400-series)
  ///--------------------------------

  // Not relevant to iOS client

  ///--------------------------------------
  /// @name Auth Server Errors (500-series)
  ///--------------------------------------

  // Not relevant to iOS client

};
