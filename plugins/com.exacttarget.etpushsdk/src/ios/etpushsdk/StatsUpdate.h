//
//  StatsUpdate.h
//  ET SDK Demo
//
//  Created by Eddie Roger on 8/2/13.
//  Copyright (c) 2013 ExactTarget, Inc. All rights reserved.
//

#import "GenericUpdate.h"
#import "Message.h"

@interface StatsUpdate : GenericUpdate <NSCopying>

@property (nonatomic) NSInteger secondsInApp; /* time in app, in seconds */
@property (nonatomic, strong) NSString *messageID; /* from ET, the message identifier. */
@property (nonatomic, strong) NSString *fenceID; /* which fence got broken */
@property (nonatomic, strong) NSDate *displayDate; /* for local notifications, this is shown when they fire. ie, firedate */
@property (nonatomic, strong) NSDate *openDate; /* generic open date, maybe null usually, since no one opens our apps */
@property (nonatomic) MobilePushMessageType messageType;

@end
