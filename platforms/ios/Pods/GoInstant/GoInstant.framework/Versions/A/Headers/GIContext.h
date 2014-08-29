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

@class GIKey;
@class GIRoom;
@class GIUser;
@class GIConnection;

/**
 *  Enum which describes all supported commands returned from the GoInstant server.
 */
typedef NS_ENUM(NSInteger, GIContextCommand) {
  /**
   *  Returned for notifications triggered by a Get command on GIKey.
   */
  GIContextCommandGet,

  /**
   *  Returned for notifications triggered by a Set command on GIKey.
   */
  GIContextCommandSet,

  /**
   *  Returned for notifications triggered by an Add command on GIKey.
   */
  GIContextCommandAdd,

  /**
   *  Returned for notifications triggered by a Remove command on GIKey.
   */
  GIContextCommandRemove,

  /**
   *  Returned when the server responds with an unsupported command.
   */
  GIContextCommandUnknown
};

/**
 *  Parent class for all GIContext types. Contains properties which are common to contexts returned from any command.
 */
@interface GIContext : NSObject<NSCopying>

/**
 The event that occured.
 */
@property (readonly) GIContextCommand command;

/**
 The key whose value has changed.
 */
@property (weak, readonly) GIKey *key;

/**
 The value of the key after the operation.
 */
@property (readonly) id value;

/**
 The room in which the key exists
 */
@property (weak, readonly) GIRoom *room;

/**
 The user who initiated the action. If the user has left the room this will be nil
 */
@property (weak, readonly) GIUser *user;

/**
 The The ID of the user who initiated the action.
 */
@property (readonly) NSString *userId;

/**
 Indicates whether or not a handler was triggered from a local or remote change.
 */
@property (readonly) Boolean local;

/**
 Indicates whether a handler was triggered from an action on this key or a child key.
 */
@property (readonly) Boolean bubble;

@end

/**
 *  Context returned for Set commands on GIKey.
 */
@interface GISetContext : GIContext

/**
 The set of keys that will cascade the operated on key.
 */
@property (readonly) NSArray *cascade;

@end


/**
 *  Context returned for Get commands on GIKey.
 */
@interface GIGetContext : GISetContext
/**
 Indicates whether or not the 'set' operation overwrote an existing value.
 */
@property (readonly) Boolean overwritten;

@end


/**
 *  Context returned for Add commands on GIKey.
 */
@interface GIAddContext : GIGetContext

/**
 Only appears in the context during 'add' events. This value is the path to the added child-key.
 */
@property (weak, readonly) GIKey *addedKey;

@end


/**
 *  Context returned for Remove commands on GIKey.
 */
@interface GIRemoveContext : GIContext
/**
 Indicates whether or not a key has been removed from cascading.
 */
@property (readonly) Boolean cascaded;

/**
 Indicates whether or not the key has expired
 */
@property (readonly) Boolean expired;

@end
