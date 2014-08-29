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

@interface GIOptions : NSObject
+ (instancetype)optionsWithDefaults;
+ (instancetype)optionsWithLocal:(BOOL)local;

/**
 Boolean where, if true, the event produced from this action will trigger the listeners that have opted-in to local events.
 [default: YES]
 */
@property(atomic, readwrite) BOOL local;

@end

@interface GIAddOptions : GIOptions

+ (instancetype)optionsWithLocal:(BOOL)local bubble:(BOOL)bubble expire:(NSNumber *)expire cascade:(GIKey *)cascade;
+ (instancetype)optionsWithBubble:(BOOL)bubble;
+ (instancetype)optionsWithExpire:(NSNumber *)expire;
+ (instancetype)optionsWithCascade:(GIKey *)cascade;

/**
 Boolean where, if true, the event produced from this action will bubble to all of the parent key listeners.
 [default: YES]
 */
@property(atomic, readwrite) BOOL bubble;

/**
 Time to live on the key, in milliseconds. Once the key expires, a Remove event is triggered.
 [default: nil]
 */
@property(atomic, readwrite) NSNumber *expire;

/**
 Reference to a key that will cause the set key to be removed whenever the referenced key is removed.
 [default: nil]
 */
@property(atomic, readwrite) GIKey *cascade;

@end

@interface GISetOptions : GIAddOptions

+ (instancetype)optionsWithLocal:(BOOL)local bubble:(BOOL)bubble overwrite:(BOOL)overwrite
                          expire:(NSNumber *)expire cascade:(GIKey *)cascade;
+ (instancetype)optionsWithOverwrite:(BOOL)overwrite;

/**
 Boolean where, if true, the set command will overwrite any existing value. If false, the set command will produce an error if the key already has a value.
 [default: YES]
 */
@property(atomic, readwrite) BOOL overwrite;

@end

@interface GIRemoveOptions : GIOptions

+ (instancetype)optionsWithLocal:(BOOL)local bubble:(BOOL)bubble lastValue:(BOOL)lastValue;
+ (instancetype)optionsWithBubble:(BOOL)bubble;
+ (instancetype)optionsWithLastValue:(BOOL)lastValue;

/**
 Boolean where, if true, the event produced from this action will bubble to all of the parent key listeners.
 [default: YES]
 */
@property(atomic, readwrite) BOOL bubble;

/**
 Boolean where, if true, the value of the key at the time of deletion will be returned in the callback.
 [default: YES]
 */
@property(atomic, readwrite) BOOL lastValue;

@end