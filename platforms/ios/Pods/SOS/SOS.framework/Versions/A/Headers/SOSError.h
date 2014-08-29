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
 *  SOS ErrorCode definitions.
 *
 *  Errors fall into one of several groups (or series) of errors.
 *
 *  If there is an error thrown by a library dependency it will be included as metadata
 *  in the userInfo of the error which is returned to the application code.
 */
typedef NS_ENUM(NSInteger, SOSErrorCode) {
  ///--------------------------------
  /// @name General Errors (0-series)
  ///--------------------------------

  /**
    *  Unclassified error. This results from an unknown or unexpected error state.
    *
    *  Any other un-grouped errors will be added to the 0-99 series error group.
    */
  SOSGenericError = 0,

  ///--------------------------------
  /// @name Connection Errors (100-series)
  ///--------------------------------

  /**
    * Standard connection error. This can be thrown from any part of the SOS Session connection flow.
    *
    * All connection related errors will be found in the 100-199 series error group.
    */
  SOSConnectionError = 100,

  ///--------------------------------
  /// @name Server Errors (200-series)
  ///--------------------------------

  /**
   *  Standard server error. This can be returned from operations made to the SOS server.
   *
   *  All server related errors will be found in the 200-299 series error group.
   */
  SOSServerError = 200,

  ///--------------------------------
  /// @name Communication Errors (300-series)
  ///--------------------------------

  /**
    *  Standard communication error. This can be returned from operations dependent on communication
    *  between SOS or any other remote system.
    *
    *  All communication related errors will be found in the 300-399 series error group.
    */
  SOSCommunicationError = 300,
  
  /**
   *  Error returned if there is a problem creating an authentication token with the
   *  WebRTC provider.
   */
  SOSRTCProviderAuthenticationError = 301,

  ///--------------------------------
  /// @name Application Errors (400-series)
  ///--------------------------------

  /**
    *  Standard internal framework error. This can be returned from operations performed within the SOS framework.
    *
    *  All internal rrors will be found in the 400-499 series error group.
    */
  SOSInternalError = 400,

  /**
   *  Error returned when attempting an SOS session without first aving initialized the <SOSContainerViewController>.
   */
  SOSContainerViewControllerNotInitialized = 401,

  ///--------------------------------
  /// @name RTC Provider Errors (500-series)
  ///--------------------------------

  /**
    *  Standard RTC Provider error. This can be returned as a result of operations performed by the RTC provider.
    *
    *  Since the RTC provider is a separate library, error specifics will be wrapped and included in the userInfo of
    *  errors returned with this code.
    */
  SOSRTCProviderError = 500,
};