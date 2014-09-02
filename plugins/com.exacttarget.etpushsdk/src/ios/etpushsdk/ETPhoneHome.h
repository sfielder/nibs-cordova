//
//  ETPhoneHome.h
//  ET SDK Demo
//
//  Created by Eddie Roger on 7/18/13.
//  Copyright (c) 2013 ExactTarget, Inc. All rights reserved.
//
//  This object themed intentionally. 

#import <UIKit/UIKit.h>
#import "GenericUpdate.h"

#define BaseRequestURL @"https://consumer.exacttargetapis.com"
//#define BaseRequestURL @"http://postcatcher.10.25.244.142.xip.io"

/**
 ETPhoneHome is like a highway management system, governing the sending of data to and from ExactTarget, and caching that which can't get sent home. It works by marshalling around GenericUpdate object subclasses, which themselves create a common pattern for handling business. 
 
 Data should be sent back using phoneHome:, which will start the process of sending data to ET, and failing that, save it to the database. The behavior is all controlled by methods on the GenericUpdate object.
 
 */
@interface ETPhoneHome : NSObject <NSURLConnectionDataDelegate>


/**
  Singleton accessor. This isn't to be publicly used, so we can have a sense of humor about it. 
 */
+(ETPhoneHome *)magicBicycle;

/**
 Begins the process of sending data back to ExactTarget. 
 
 @param updateObject A subclass of GenericUpdate that wants to be send to ET.
 
 @return bool Whether or not it was able to send to ET. 
 */
-(BOOL)phoneHome:(GenericUpdate *)updateObject;

/**
 Saves the udpate object to the database in the event of a send failure. It is exposed in the header because some objects just need to be saved instead of sent. This method should not be used publicly. 
 
 @param updateObject The subclass of GenericUpdate to save to the database.
 
 @return bool Whether or not the save succeeded. Sometimes they don't. 
 */
-(BOOL)saveToDatabaseInstead:(GenericUpdate *)updateObject;


/**
 Checks the cache database for records that weren't successfully sent to ExactTarget, and tries to send them. No return value. 
 */
-(void)checkForAndSendBackCachedData;

@end
