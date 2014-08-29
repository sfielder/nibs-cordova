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
@class GIKey;

@class GISetContext;
@class GIGetContext;
@class GIRemoveContext;
@class GIAddContext;

@class GIAddOptions;
@class GISetOptions;
@class GIRemoveOptions;

typedef void (^GIKeyGetHandler)(NSError* error, id value, GIGetContext *context);
typedef void (^GIKeySetHandler)(NSError* error, id value, GISetContext *context);
typedef void (^GIKeyAddHandler)(NSError* error, id value, GIAddContext *context);
typedef void (^GIKeyRemoveHandler)(NSError* error, id value, GIRemoveContext *context);

@protocol GIKeyObserver<NSObject>
@optional
- (void)key:(GIKey *)key valueSet:(id)value context:(GISetContext *)context;
- (void)key:(GIKey *)key valueAdded:(id)value context:(GIAddContext *)context;
- (void)key:(GIKey *)key valueRemoved:(id)value context:(GIRemoveContext *)context;
@end

/**
 *  The Key is the primary interface for accessing and manipulating data in GoInstant.
 *
 *  Key names look like the paths on a URL: /path/to/my/key.
 *
 *  Key is in reference to a key-value store.
 *  The Key object provides the interface for managing and monitoring a value in our server-side data store.
 *
 *  Key values are limited to 32KB in size.
 */
@interface GIKey : NSObject

///-----------------------------
/// @name Initialization methods
///-----------------------------

+ (instancetype)keyWithPath:(NSString *)path room:(GIRoom *)room;
- (instancetype)initWithPath:(NSString *)path room:(GIRoom *)room;

///------------------------------
/// @name Value retrieval methods
///------------------------------

- (void)getValueWithCompletion:(GIKeyGetHandler)block;

///---------------------------------
/// @name Value modification methods
///---------------------------------

- (void)removeValue;
- (void)removeValueWithOptions:(GIRemoveOptions *)options;
- (void)removeValueWithCompletion:(GIKeyRemoveHandler)block;
- (void)removeValueWithOptions:(GIRemoveOptions *)options completion:(GIKeyRemoveHandler)block;

- (void)setValue:(id)value;
- (void)setValue:(id)value options:(GISetOptions *)options;
- (void)setValue:(id)value completion:(GIKeySetHandler)block;
- (void)setValue:(id)value options:(GISetOptions *)options completion:(GIKeySetHandler)block;

- (void)addValue:(id)value;
- (void)addValue:(id)value options:(GIAddOptions *)options;
- (void)addValue:(id)value completion:(GIKeyAddHandler)block;
- (void)addValue:(id)value options:(GIAddOptions *)options completion:(GIKeyAddHandler)block;

///------------------------
/// @name Traversal methods
///------------------------

/**
 *  Returns a new GIKey instance by appending the supplied path onto this key's path.
 *
 *  @param path The relative path of the descendent key.
 *
 *  @return A new GIKey instance with the constructed path.
 *
 *  @see [GoInstant Data Structure](https://developers.goinstant.com/v1/overview/data_structure.html)
 */
- (GIKey *)descendentKeyWithPath:(NSString *)path;

/**
 *  Returns a new GIKey instance with a path that is equal to the parent key path in the GoInstant
 *  key hierarchy.
 *  Note that the returned GIKey is always a *new* instance. If called on the root key ("/"), a new 
 *  instance of the root key will be returned.
 *
 *  @return A new GIKey instance with this key's last path component stripped.
 *
 *  @see [GoInstant Data Structure](https://developers.goinstant.com/v1/overview/data_structure.html)
 */
- (GIKey *)parentKey;

///-----------------------------
/// @name Event handling methods
///-----------------------------

- (void)subscribe:(id<GIKeyObserver>)observer;
- (void)unsubscribe:(id<GIKeyObserver>)observer;
- (void)unsubscribeAll;

///-------------------------
/// @name Comparison methods
///-------------------------

- (BOOL)isEqualToKey:(GIKey *)key;

///-----------------
/// @name Properties
///-----------------

@property (nonatomic, readonly) GIRoom *room;
@property (nonatomic, readonly) NSString *path;
@property (nonatomic, readonly) NSString *name;

@end


