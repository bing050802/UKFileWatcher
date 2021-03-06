//
//  UKFileWatcher.h
//  Filie
//
//  Created by Uli Kusterer on 2005-02-25.
//  Copyright 2005 Uli Kusterer.
//
//	This software is provided 'as-is', without any express or implied
//	warranty. In no event will the authors be held liable for any damages
//	arising from the use of this software.
//
//	Permission is granted to anyone to use this software for any purpose,
//	including commercial applications, and to alter it and redistribute it
//	freely, subject to the following restrictions:
//
//	   1. The origin of this software must not be misrepresented; you must not
//	   claim that you wrote the original software. If you use this software
//	   in a product, an acknowledgment in the product documentation would be
//	   appreciated but is not required.
//
//	   2. Altered source versions must be plainly marked as such, and must not be
//	   misrepresented as being the original software.
//
//	   3. This notice may not be removed or altered from any source
//	   distribution.
//

/*
    This is a protocol that file change notification classes should adopt.
    That way, no matter whether you use Carbon's FNNotify/FNSubscribe, BSD's
    kqueue or whatever, the object being notified can react to change
    notifications the same way, and you can easily swap one out for the other
    to cater to different OS versions, target volumes etc.
*/

// -----------------------------------------------------------------------------
//  Preprocessor flags:
// -----------------------------------------------------------------------------

// For historical reasons (I was young and stupid) UKKQueue etc. send their
//	notifications to NSWorkspace's notificationCenter. This is not available on
//	 iOS or in Foundation tools, so we're switching to NSNotificationCenter.
//	For backwards compatibility, we currently *also* send notifications to
//	the workspace's notification center. Define this flag to 0 in your prefix
//	header to remove this behaviour. This is recommended for new code. This
//	behaviour will be removed in a future version.
#ifndef UKKQ_NOTIFY_NSWORKSPACE_CENTER
#define UKKQ_NOTIFY_NSWORKSPACE_CENTER		(!TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR)
#endif


// -----------------------------------------------------------------------------
//  Protocol:
// -----------------------------------------------------------------------------

@protocol UKFileWatcherDelegate;

@protocol UKFileWatcher <NSObject>

// +(id) sharedFileWatcher;			// Singleton accessor. Not officially part of the protocol, but use this name if you provide a singleton.

-(void) addPath: (NSString*)path;
-(void) removePath: (NSString*)path;
-(void)	removeAllPaths;

-(id)   delegate;
-(void) setDelegate: (id<UKFileWatcherDelegate>)newDelegate;

@end

// -----------------------------------------------------------------------------
//  Methods delegates need to provide:
// -----------------------------------------------------------------------------

@protocol UKFileWatcherDelegate <NSObject>

-(void) watcher: (id<UKFileWatcher>)kq receivedNotification: (NSString*)nm forPath: (NSString*)fpath;

@end


// Notifications this sends:
/*  object			= the file watcher object
	userInfo.path	= file path watched
	These notifications are sent via the NSWorkspace notification center */
extern NSString* UKFileWatcherRenameNotification;
extern NSString* UKFileWatcherWriteNotification;
extern NSString* UKFileWatcherDeleteNotification;
extern NSString* UKFileWatcherAttributeChangeNotification;
extern NSString* UKFileWatcherSizeIncreaseNotification;
extern NSString* UKFileWatcherLinkCountChangeNotification;
extern NSString* UKFileWatcherAccessRevocationNotification;

