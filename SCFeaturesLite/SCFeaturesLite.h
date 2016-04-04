//
//  SCFeaturesLite.h
//  SCFeaturesLite
//
//  Created by iMokhles on 04/04/16.
//  Copyright © 2016 iMokhles. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "iMoMacros.h"
#import "UIImage+Additions.h"
#import "UIAlertView+Blocks.h"
#import "ZKSwizzle.h"
#import "fakelogos.h"
#import "Alert.h"

#pragma mark - Snapchat

@interface UIActivityViewController ()
@property (nonatomic, retain) UIAlertController *activityAlertController;
@end

@interface UIDevice ()
- (id)_deviceInfoForKey:(NSString *)key;
@end

OBJC_EXTERN CFStringRef MGCopyAnswer(CFStringRef key) WEAK_IMPORT_ATTRIBUTE;

@interface UIWindow ()
+ (UIWindow *)keyWindow;
- (UIView *)contentView;
@end

@interface SCReplyToStoryViewController : UIViewController
@end

@interface SCTextView : UIView
@property(retain, nonatomic) UITextField *textField; // @synthesize textField=_textField;
@end

@interface SCGrowingButton : UIView
@property(nonatomic) SEL action;
- (id)initWithFrame:(struct CGRect)arg1;
- (void)addTarget:(id)arg1 action:(SEL)arg2;
@property(nonatomic, getter=isEnabled) _Bool enabled;
@property(retain, nonatomic) UIImageView *imageView;
@property(retain, nonatomic) NSString *imageName;
@property(retain, nonatomic) UIImage *image;
@property(nonatomic) struct CGSize imageInset;
- (void)press:(id)arg1;
- (CGPoint)imageCenter;
@end

@interface FriendButton : SCGrowingButton
@end

@interface SCCameraOverlayView : UIView
@property(retain, nonatomic) SCGrowingButton *galleryButton;
@property(retain, nonatomic) FriendButton *storiesButton;
@end


@interface SCCounterLabel : UILabel
@end

@interface Media : NSObject
@property(retain, nonatomic) AVPlayerItem *playerItem;
@end

@interface SCActiveVideoMedia : NSObject
@property(copy, nonatomic) NSString *mediaId;
@property(retain, nonatomic) Media *media;
@end

@interface SCMediaView : UIImageView
@property(retain, nonatomic) NSArray *playerViews;
@property(retain, nonatomic) NSMutableDictionary *activeVideos;
@property(nonatomic) _Bool playerAPlaying;
@property(nonatomic) _Bool playerBPlaying;
@property(retain, nonatomic) NSArray *overlayImageViews;
@property(retain, nonatomic) UIImageView *imageView;
@property(retain, nonatomic) SCCounterLabel *counter;
@end

@interface SCCaptionModeButton : SCGrowingButton
{
    _Bool _selected;
}

@property(nonatomic) _Bool selected; // @synthesize selected=_selected;
- (void)loadImage;
- (id)initWithFrame:(struct CGRect)arg1;

@end

@interface SCSwipeFilterView : UIView
@end

@interface SCImageSwipeFilterView : SCSwipeFilterView
- (id)newMediaFilterViewForName:(id)arg1;
- (id)filteredImage;
- (id)mediaFilterScrollView;
@property(retain, nonatomic) UIImage *image;
@end

@interface PreviewViewController : UIViewController 
@property(retain, nonatomic) SCGrowingButton *audioButton;
@property(retain, nonatomic) UIImageView *imageView;
@property(retain, nonatomic) UIView *containerView;
@property(retain, nonatomic) SCSwipeFilterView *swipeFilterView;
@property(nonatomic) _Bool videoSwipeFilterSetupCompleted;
- (void)setupVideoFilterViewWithOverlayViews;
- (void)setupImageFilterViewWithDrawingView;
@property(retain, nonatomic) SCCaptionModeButton *captionModeButton;
@end

@interface SendViewController : UIViewController
@end

@interface AVCameraViewController : UIViewController
- (void)presentPreviewForVideoWithURL:(id)arg1 frontFacingCamera:(_Bool)arg2 fromGallery:(_Bool)arg3;
- (unsigned long long)suitableVideoPlaybackQuality;
- (void)presentPreviewForImage:(id)arg1 metadata:(id)arg2 frontFacingCamera:(_Bool)arg3;
- (void)presentPreviewForVideoWithURL:(id)arg1 frontFacingCamera:(_Bool)arg2;
- (void)presentPreviewForImage:(id)arg1 metadata:(id)arg2 frontFacingCamera:(_Bool)arg3 fromGallery:(_Bool)arg4;
@end

@interface SCStoriesViewController : UIViewController
@end

@interface SCFeedViewController : UIViewController
@end

@interface SCDiscoverViewController : UIViewController
@end

@interface MainViewController : UIViewController
@property(retain, nonatomic) UIViewController *farLeftVC;
@property(retain, nonatomic) UIViewController *partiallyVisibleVC;
@property(retain, nonatomic) SCDiscoverViewController *farRightVC; // @synthesize farRightVC=_farRightVC;
@property(retain, nonatomic) SCStoriesViewController *rightVC;
@property(retain, nonatomic) SCFeedViewController *leftVC;
@property(retain, nonatomic) AVCameraViewController *middleVC; // @synthesize middleVC=_middleVC;
@end



@interface SCPlayerView : UIView
{
}

+ (Class)layerClass;
@property(retain, nonatomic) AVPlayer *player;
@property(readonly, nonatomic) AVPlayerLayer *playerLayer;

@end

@interface SCDiscoverFullStackViewController : UIViewController
@property(retain, nonatomic) SCPlayerView *backgroundVideoView;
@end

@interface Snap : NSObject
- (void)setFailed;
- (_Bool)hasFailedAtLeastOnce;
- (long long)getGroupId;
- (id)clearedDictionary;
- (_Bool)sending;
- (_Bool)failedToSend;
- (_Bool)sentByUser;
- (_Bool)isInvalidAfterUnarchiving;
- (_Bool)isUnread;
- (_Bool)shouldDisplayBelowFoldInChat;
- (id)messageRecipient;
- (id)messageSender;
- (id)feedSortTimestamp;
- (id)feedDisplayTimestamp;
- (id)messageTimestamp;
- (void)imageProcessingDidSucceedForMedia:(id)arg1;
- (void)mediaUploadDidFailForMedia:(id)arg1;
- (void)mediaUploadDidSucceedForMedia:(id)arg1;
- (long long)uploadMediaTypeForMedia:(id)arg1;
- (id)uploadMediaIdForMedia:(id)arg1;
- (void)fetchMediaDidSucceedForMedia:(id)arg1;
- (void)fetchMediaIsGoneForMedia:(id)arg1;
- (void)fetchMediaDidFailForMedia:(id)arg1;
- (void)fetchMediaIsLoadingForMedia:(id)arg1;
- (_Bool)isBroadcastForMedia:(id)arg1;
- (id)requestContexts;
- (long long)requestFallbackPriority;
- (long long)requestPriorityUserInitiated:(_Bool)arg1;
- (_Bool)needsAuthToFetch;
- (_Bool)encrypt;
- (_Bool)persist;
- (id)encryptionDictionaryForMedia:(id)arg1;
- (id)decryptData:(id)arg1 forMedia:(id)arg2;
- (id)mediaIdForMedia:(id)arg1;
- (id)endpointParamsForMedia:(id)arg1;
- (id)endpointForMedia:(id)arg1;
- (id)secretReceivedSnapParameters;
- (id)receivedSnapParameters;
- (id)secretSentSnapParameters;
- (id)sentSnapParameters;
- (void)logSendEvent;
- (id)consistentId;
- (_Bool)veryRecentlyOpen;
- (id)username;
- (_Bool)isExpired;
- (_Bool)canBeRemoved;
- (_Bool)isGroupSend;
- (id)nameForView;
- (id)recipientUsernames;
- (id)initWithCoder:(id)arg1;
- (void)encodeWithCoder:(id)arg1;
- (void)replaceWithSnap:(id)arg1;
- (_Bool)shouldReplaceWithSnap:(id)arg1;
- (_Bool)updateWithSnap:(id)arg1;
- (_Bool)isPreparedToReplayOrReplaying;
- (_Bool)isSentSnap;
- (_Bool)isReceivedAndUnopened;
- (_Bool)isReceivedAndOpened;
- (_Bool)isViewing;
- (_Bool)isLoading;
- (_Bool)isLoaded;
- (_Bool)isNotLoaded;
- (_Bool)isScreenshotted;
- (_Bool)isSentAndOpened;
- (_Bool)isDelivered;
- (_Bool)isSentDeliveredOrOpened;
- (_Bool)isSent;
- (_Bool)isSendingOrHasFailed;
- (_Bool)isMediaProcessingOrFailedToProcess;
- (_Bool)isMediaProcessing;
- (_Bool)hasMediaProcessingFailed;
- (_Bool)hasFailed;
- (_Bool)isSending;
- (id)uploadParametersWithData:(_Bool)arg1;
- (void)retrySending:(_Bool)arg1;
- (_Bool)autoRetrySendingIfNetworkReachable;
- (void)doSend;
- (void)postSend;
- (void)send;
- (void)preSend;
- (void)uploadAndSend;
- (_Bool)shouldClearSentSnap;
- (void)incNumTimesReloaded;
- (_Bool)isSentButNotYetReturned;
- (void)clearNumTimesReloaded;
- (void)markAsViewed;
- (void)replay;
@end

@interface SCSnapSaver : NSObject
{
}

+ (id)shared;
- (id)_fetchSnapchatAlbums;
- (void)logSnapSaveEventWithError:(id)arg1 context:(id)arg2 isVideo:(_Bool)arg3 isVideoFiltered:(_Bool)arg4 videoDuration:(double)arg5;
- (void)logSnapSaveEventStart:(id)arg1;
- (void)logAlbumPhotoCount:(unsigned long long)arg1 videoCount:(unsigned long long)arg2 albumCounts:(id)arg3;
- (void)fetchAndLogAlbumSize;
- (void)finishedSavingToAlbumWithError:(id)arg1 completionBlock:(id)arg2;
- (void)saveAsset:(id)arg1 toALAssetsGroup:(id)arg2 completionBlock:(id)arg3;
- (void)saveToAlbumUsingALAssetsLibraryWithAssetURL:(id)arg1 completionBlock:(id)arg2;
- (void)saveAsset:(id)arg1 toPHAssetCollection:(id)arg2 completionBlock:(id)arg3;
- (void)saveToAlbumUsingPHPhotoLibraryWithAssetURL:(id)arg1 completionBlock:(id)arg2;
- (void)finishedWritingWithAssetURL:(id)arg1 error:(id)arg2 completionBlock:(id)arg3;
- (void)saveSnapVideoAtURLToSnapAlbum:(id)arg1 completionBlock:(id)arg2 deleteAfterSaving:(_Bool)arg3;
- (void)saveSnapImageToSnapAlbum:(id)arg1 completionBlock:(id)arg2;

@end


@interface User
+ (void)performLoginWithUsernameOrEmail:(NSString *)username password:(NSString *)password;
+ (void)performLoginWithUsernameOrEmail:(id)arg1 password:(id)arg2 isTwoFA:(_Bool)arg3 preAuthToken:(id)arg4 onComplete:(id)arg5; // new
@end

@interface Manager : NSObject
+ (void)clearUnusedVideoURLsExcludingURLsFromSnaps:(id)arg1 andStories:(id)arg2;
+ (id)inspectJsonValidity:(id)arg1;
+ (id)shared;
+ (_Bool)isInitialized;
- (void)postServerChallenge;
- (void)logConversationsResponse:(id)arg1;
- (void)clearViewedStories;
- (void)clearExpiredStories;
- (void)clearExpiredAndViewedStories;
- (void)didAppStartupComplete;
- (_Bool)userHasValidRequest;
- (void)willEnterForegroundFromRemoteNotification:(_Bool)arg1;
- (void)didEnterBackground;
- (void)prepareForBecomeActiveFromRemoteNotification:(_Bool)arg1;
- (void)prepareForResignActive;
- (void)startTimer:(id)arg1 source:(long long)arg2;
- (void)startTimerIfNecessary;
- (void)markSnapAsViewed:(id)arg1;
- (void)tick:(id)arg1;
- (_Bool)hasUnviewedChats;
- (_Bool)hasUnviewedCash;
- (int)hasUnviewedSnaps;
- (long long)unreadCount;
- (void)registerDeviceToken:(id)arg1;
- (void)checkMobile;
- (void)verifyMobile:(id)arg1 shouldSkipConfirmation:(_Bool)arg2 type:(long long)arg3;
- (void)verifyMobile:(id)arg1 shouldSkipConfirmation:(_Bool)arg2;
- (void)verifyMobile:(id)arg1 type:(long long)arg2;
- (void)verifyMobile:(id)arg1;
@end


@interface SCSnapPlayController : NSObject
@property(retain, nonatomic) Snap *visibleSnap;
+ (id)shared;
- (_Bool)showingMediaView;
- (_Bool)isPlayingSnap;
- (id)visibleSnapUsername;
- (id)mediaView;
@end

@interface SCFeaturesLite : NSObject
+ (instancetype)shareFeatures;
@end
