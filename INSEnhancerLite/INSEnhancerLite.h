//
//  INSEnhancerLite.h
//  INSEnhancerLite
//
//  Created by iMokhles on 04/04/16.
//  Copyright © 2016 iMokhles. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuickLook/QuickLook.h>
#import "iMoMacros.h"
#import "UIImage+Additions.h"
#import "UIAlertView+Blocks.h"
#import "ZKSwizzle.h"
#import "fakelogos.h"
#import "Alert.h"
#import "TransNSString.h"

#pragma mark - Instagram

@interface UIDevice ()
- (id)_deviceInfoForKey:(NSString *)key;
@end

OBJC_EXTERN CFStringRef MGCopyAnswer(CFStringRef key) WEAK_IMPORT_ATTRIBUTE;

@interface UIWindow ()
+ (UIWindow *)keyWindow;
- (UIView *)contentView;
@end

@interface AppDelegate : NSObject <UIApplicationDelegate>
{
    BOOL _handledPushNoteInDidFinishLaunching;
    UIWindow *_window;
}

@property(nonatomic) BOOL handledPushNoteInDidFinishLaunching; // @synthesize handledPushNoteInDidFinishLaunching=_handledPushNoteInDidFinishLaunching;
@property(retain, nonatomic) UIWindow *window; // @synthesize window=_window;
- (void)registerForPush;
- (BOOL)application:(id)arg1 openURL:(id)arg2 sourceApplication:(id)arg3 annotation:(id)arg4;
- (BOOL)application:(id)arg1 handleOpenURL:(id)arg2;
- (void)userLogout:(id)arg1;
- (void)userLoginCompleted:(id)arg1;
- (void)startMainAppWithMainFeedSource:(id)arg1 animated:(BOOL)arg2;
- (void)setUpInstagramNotifications;
- (void)setUpDefaults;
- (void)applicationLifecycleChange:(id)arg1;
- (void)applicationWillTerminate:(id)arg1;
- (void)applicationDidEnterBackground:(id)arg1;
- (void)applicationDidBecomeActive:(id)arg1;
- (void)applicationWillEnterForeground:(id)arg1;
- (BOOL)application:(id)arg1 didFinishLaunchingWithOptions:(id)arg2;
@end

@interface IGStyledString : NSObject {
    NSMutableDictionary *_heightCache;
    NSMutableAttributedString *_attributedString;
}
+ (id)createWithCacheKey:(id)arg1 creationBlock:(id)arg2;
@property(retain, nonatomic) NSMutableAttributedString *attributedString; // @synthesize attributedString=_attributedString;
- (int)heightForWidth:(int)arg1;
- (void)applyBaseStyleToAttributedString:(id)arg1;
- (void)appendAnnotatedString:(id)arg1;
- (void)appendAttributedString:(id)arg1;
- (void)appendString:(id)arg1;
- (id)initWithBaseStyle:(id)arg1;
- (id)init;
- (void)appendLinkedTitleString:(id)arg1;
- (void)appendLinkedString:(id)arg1;

@end

@interface IGCoreTextView : UIView
{
    UIColor *_shadowColor;
    float _shadowOffset;
    BOOL _heightIsValid;
    struct CGPoint _touchPoint;
    BOOL _longTapHandled;
    IGStyledString *_styledString;
}

@property(retain, nonatomic) IGStyledString *styledString; // @synthesize styledString=_styledString;
- (void)drawRect:(struct CGRect)arg1;
- (BOOL)handleTapAtIndex:(int)arg1 forTouchEvent:(unsigned int)arg2 fromLongTap:(BOOL)arg3;
- (BOOL)handleTapAtIndex:(int)arg1 forTouchEvent:(unsigned int)arg2;
- (BOOL)handleTapAtPoint:(struct CGPoint)arg1 forTouchEvent:(unsigned int)arg2 fromLongTap:(BOOL)arg3;
- (BOOL)handleTapAtPoint:(struct CGPoint)arg1 forTouchEvent:(unsigned int)arg2;
- (void)handleLongTap;
- (void)touchesEnded:(id)arg1 withEvent:(id)arg2;
- (void)touchesCancelled:(id)arg1 withEvent:(id)arg2;
- (void)touchesBegan:(id)arg1 withEvent:(id)arg2;
- (float)height;
- (void)setFrame:(struct CGRect)arg1;
- (id)initWithWidth:(float)arg1;
@end

@interface IGCoreTextView (everything_tweak) <UIPopoverPresentationControllerDelegate>
@end

@interface IGVideo : NSObject

+ (int)videoVersionForCurrentNetworkConditions;
@property(retain, nonatomic) NSArray *videoVersions; // @synthesize videoVersions=_videoVersions;
@property(readonly, nonatomic) int videoLength; // @synthesize videoLength=_videoLength;
- (id)allVideoURLs;
- (id)videoURLForVideoVersion:(int)arg1;
- (id)videoInfoDictionaryForVideoVersion:(int)arg1;
- (void)encodeWithCoder:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (id)initWithVideoVersions:(id)arg1 videoLength:(int)arg2 audioDetected:(id)arg3;
- (id)initWithFeedItemDictionary:(id)arg1;
- (id)videoURLForCurrentNetworkConditions;

@end

@interface IGPhoto : NSObject
+ (id)arrayForImageVersions:(id)arg1;
@property(retain, nonatomic) NSArray *imageVersions; // @synthesize imageVersions=_imageVersions;
@property(readonly, copy, nonatomic) NSString *mediaID; // @synthesize mediaID=_mediaID;
@end


@interface IGPost : NSObject
{
    BOOL _hasLiked;
    BOOL _moreCommentsAvailable;
    BOOL _collapseComments;
    BOOL _needsFetch;
    int _mediaType;
    NSNumber *_deviceTimestamp;
    NSDictionary *_imageVersions;
    NSDictionary *_videoVersions;
    int _videoLength;
    NSMutableOrderedSet *_likers;
    int _likeCount;
    NSMutableArray *_pendingComments;
    NSArray *_activeComments;
    NSMutableArray *_allComments;
    NSNumber *_commentCursor;
    int _commentCount;
    NSString *_rankToken;
    NSString *_exploreContext;
}

@property(readonly) IGVideo *video;
@property(readonly) IGPhoto *photo;

+ (int)fullSizeImageVersionForDevice;
+ (int)videoVersionForCurrentNetworkConditions;
@property(nonatomic) BOOL needsFetch; // @synthesize needsFetch=_needsFetch;
@property(readonly, copy) NSString *exploreContext; // @synthesize exploreContext=_exploreContext;
@property(readonly) NSString *rankToken; // @synthesize rankToken=_rankToken;
- (id)urlToFlagComment:(id)arg1;
- (id)urlToDeleteComment:(id)arg1;
- (id)urlToPostComment;
- (void)schedulePostUpdatedNotification;
- (void)postPostUpdatedNotification;
- (void)commentRemoveRequestFailed:(id)arg1;
- (void)commentRemoveRequestFinished:(id)arg1;
- (void)commentRemoveRequestStarted:(id)arg1;
- (void)commentPostRequestFailedSpam:(id)arg1;
- (void)commentPostRequestFailed:(id)arg1;
- (void)commentPostRequestFinished:(id)arg1;
- (void)commentPostRequestStarted:(id)arg1;
- (void)fetchMoreCommentsWithCompletionHandler:(id)arg1;
- (void)invalidateActiveComments;
@property(readonly) NSArray *activeCaptionAndComments;
@property(readonly) NSArray *activeComments; // @synthesize activeComments=_activeComments;
- (void)removeCommentWithPK:(id)arg1;
- (void)addComment:(id)arg1;
- (void)setCommentInfoFromDictionary:(id)arg1 append:(BOOL)arg2;
@property(retain) NSMutableArray *pendingComments; // @synthesize pendingComments=_pendingComments;
@property(readonly) NSMutableArray *allComments; // @synthesize allComments=_allComments;
- (void)performLike:(BOOL)arg1 userDidDoubleTap:(BOOL)arg2 completion:(id)arg3;
- (void)updateLocalLikeStatus:(BOOL)arg1;
- (void)setLikeInfoFromDictionary:(id)arg1;
- (void)removeLocalLocationInformation;
- (void)setLocationInfoFromDictionary:(id)arg1;
- (void)fetchAdditionalInfo;
- (void)setMediaType:(int)arg1;
- (BOOL)updateWithDictionary:(id)arg1;
- (void)encodeWithCoder:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (id)init;
@property(readonly) BOOL collapseComments; // @synthesize collapseComments=_collapseComments;
- (void)setCollapseComments:(BOOL)arg1;
@property(readonly) BOOL moreCommentsAvailable; // @synthesize moreCommentsAvailable=_moreCommentsAvailable;
- (void)setMoreCommentsAvailable:(BOOL)arg1;
@property(readonly) int commentCount; // @synthesize commentCount=_commentCount;
- (void)setCommentCount:(int)arg1;
@property(readonly) NSNumber *commentCursor; // @synthesize commentCursor=_commentCursor;
//- (void)setCommentCursor:(id)arg1;
- (void)setCaption:(id)arg1;
//- (void)setAllComments:(id)arg1;
//- (void)setActiveComments:(id)arg1;
@property(readonly) BOOL hasLiked; // @synthesize hasLiked=_hasLiked;
- (void)setHasLiked:(BOOL)arg1;
@property(readonly) int likeCount; // @synthesize likeCount=_likeCount;
- (void)setLikeCount:(int)arg1;
@property(readonly) NSMutableOrderedSet *likers; // @synthesize likers=_likers;
//- (void)setLikers:(id)arg1;
- (void)setMediaCoord:(id)arg1;
- (void)setLocation:(id)arg1;
@property(readonly) int videoLength; // @synthesize videoLength=_videoLength;
- (void)setVideoLength:(int)arg1;
@property(readonly) NSDictionary *videoVersions; // @synthesize videoVersions=_videoVersions;
//- (void)setVideoVersions:(id)arg1;
@property(readonly) NSDictionary *imageVersions; // @synthesize imageVersions=_imageVersions;
//- (void)setImageVersions:(id)arg1;
@property(readonly) NSNumber *deviceTimestamp; // @synthesize deviceTimestamp=_deviceTimestamp;
//- (void)setDeviceTimestamp:(id)arg1;
- (void)setTakenAt:(id)arg1;
- (void)setUser:(id)arg1;
@property(readonly) int mediaType; // @synthesize mediaType=_mediaType;
- (id)imageURLForImageVersion:(int)arg1;
- (id)imageURLForFullSizeImage;
- (void)reportInappropriateWithCompletionHandler:(id)arg1;
- (id)allVideoURLs;
- (id)videoURLForVideoVersion:(int)arg1;

@end

@class IGFeedItemPhotoView;
@interface IGFeedItemPhotoCell : UITableViewCell

@property(retain, nonatomic) IGPost *post;
@property(retain, nonatomic) IGFeedItemPhotoView *photoView;
- (id)accessibleElements;
- (int)indexOfAccessibilityElement:(id)arg1;
- (id)accessibilityElementAtIndex:(int)arg1;
- (int)accessibilityElementCount;
- (void)layoutSubviews;
- (id)initWithReuseIdentifier:(id)arg1;
- (id)initWithFrame:(id)arg1;
@end

@interface IGImageView : UIImageView
@property(retain, nonatomic) NSURL *imageURL;
@end

@interface IGImageProgressView : UIView
@property(readonly, nonatomic) IGImageView *photoImageView;
@end

@interface IGFeedItemPhotoView : UIView <UIGestureRecognizerDelegate>
{
    UIImageView *_inTagIndicatorView;
    BOOL _isShowingUsertagsIndicator;
    UITapGestureRecognizer *_doubleTapRecognizer;
    UITapGestureRecognizer *_singleTapRecognizer;
    BOOL _isShowingUsertags;
    BOOL _enableDoubleTapRecognizer;
    IGPost *_post;
}

+ (float)height;
@property(nonatomic) BOOL enableDoubleTapRecognizer; // @synthesize enableDoubleTapRecognizer=_enableDoubleTapRecognizer;
@property(nonatomic) __weak IGFeedItemPhotoCell *parentCellView; // @synthesize parentCellView=_parentCellView;
@property(readonly, nonatomic) BOOL isShowingUsertags; // @synthesize isShowingUsertags=_isShowingUsertags;
@property(retain, nonatomic) IGPost *post; // @synthesize post=_post;
@property(readonly, nonatomic) IGImageProgressView *photoImageView;
- (void)onUsertagGroupWasEdited;
- (void)progressImageView:(id)arg1 didFailLoadWithError:(id)arg2;
- (void)progressImageViewDidLoadImage:(id)arg1;
- (void)showUsertags:(BOOL)arg1 animated:(BOOL)arg2;
- (void)animationDidStop:(id)arg1 finished:(BOOL)arg2;
- (void)showUsertagsIndicator:(BOOL)arg1 animated:(BOOL)arg2;
- (id)usertags;
- (BOOL)hasUsertags;
- (void)updateSingleTapRecognizer;
- (BOOL)gestureRecognizer:(id)arg1 shouldReceiveTouch:(id)arg2;
- (void)onDoubleTap:(id)arg1;
- (void)onTap:(id)arg1;
- (void)prepareForReuse;
- (void)onTagIndicatorTapped;
- (id)initWithFrame:(struct CGRect)arg1;

@end
@interface IGFeedItemPhotoCell (everything_tweak) <UIDocumentInteractionControllerDelegate>
@end

@interface IGFeedVideoPlayer : NSObject
@property(retain, nonatomic) NSURL *URL; // @synthesize URL=_URL;
- (id)init;
@end

@interface IGProxyFeedVideoPlayer : IGFeedVideoPlayer
{
    NSURL *_proxyURL;
    NSURL *_videoURL;
}

- (id)URL;
- (void)resetPlayer;
- (void)reset;
- (void)stop;
- (void)loadVideoForURL:(id)arg1;

@end

@interface IGFeedItemVideoView : UIView <UIGestureRecognizerDelegate>
{
    UITapGestureRecognizer *_doubleTapRecognizer;
    UITapGestureRecognizer *_singleTapRecognizer;
    UIView *_videoView;
    BOOL _indicatorHidden;
    BOOL _posterImageHidden;
    BOOL _forceAudio;
    BOOL _displayUnmuteButton;
    NSDate *_lastVideoStartTime;
    int _currentVideoVersion;
    BOOL _videoLoadError;
    BOOL _enableDoubleTapRecognizer;
    BOOL _hasStartedPlayback;
    BOOL _userDidTap;
    IGPost *_post;
    NSNumber *_lastPlaybackTime;
    int _originalPlaybackReason;
}

+ (float)height;
@property int originalPlaybackReason; // @synthesize originalPlaybackReason=_originalPlaybackReason;
@property(retain) NSNumber *lastPlaybackTime; // @synthesize lastPlaybackTime=_lastPlaybackTime;
@property BOOL userDidTap; // @synthesize userDidTap=_userDidTap;
@property BOOL hasStartedPlayback; // @synthesize hasStartedPlayback=_hasStartedPlayback;
@property(nonatomic) BOOL enableDoubleTapRecognizer; // @synthesize enableDoubleTapRecognizer=_enableDoubleTapRecognizer;
@property(nonatomic) BOOL videoLoadError; // @synthesize videoLoadError=_videoLoadError;
@property(retain, nonatomic) IGPost *post; // @synthesize post=_post;
//@property(retain, nonatomic) IGFeedVideoPlayer *player;
@property(retain, nonatomic) IGProxyFeedVideoPlayer *player;
- (BOOL)gestureRecognizer:(id)arg1 shouldRecognizeSimultaneouslyWithGestureRecognizer:(id)arg2;
- (BOOL)gestureRecognizer:(id)arg1 shouldReceiveTouch:(id)arg2;
- (BOOL)gestureRecognizerShouldBegin:(id)arg1;
- (void)onDoubleTap:(id)arg1;
- (void)onTap:(id)arg1;
- (void)videoPlayerStateDidChange:(id)arg1 previous:(int)arg2 current:(int)arg3;
- (void)videoPlayer:(id)arg1 didUpdatePlaybackProgress:(float)arg2;
- (void)videoPlayer:(id)arg1 didUpdateLoadingProgress:(float)arg2;
- (void)videoPlayerReadyToPlay:(id)arg1;
- (void)videoPlayerWillReset:(id)arg1;
- (void)progressImageViewDidLoadImage:(id)arg1;
- (void)userDidTapOnAudioButton;
- (void)updateAudioSettings;
- (void)didUnplugHeadphones:(id)arg1;
- (void)muteSwitchStateChanged:(id)arg1;
- (void)logVideoStoppedForPlayer:(id)arg1 reason:(int)arg2;
- (id)playbackTimesForPlayer:(id)arg1;
- (id)playbackAudioSettingsForPlayer:(id)arg1;
- (void)startPlayer:(id)arg1;
- (void)loadAndPlay;
- (BOOL)posterFrameLoaded;
- (void)prepareForAutoPlay:(BOOL)arg1;
- (void)stop;
- (void)play;
- (void)showVideo:(BOOL)arg1 animated:(BOOL)arg2 completion:(id)arg3;
- (void)showVideoIndication:(BOOL)arg1 animated:(BOOL)arg2 duration:(float)arg3;
- (void)showVideoIndication:(BOOL)arg1 animated:(BOOL)arg2;
- (void)showAudioAvailable:(BOOL)arg1 animated:(BOOL)arg2;
- (void)showError:(BOOL)arg1 animated:(BOOL)arg2;
- (void)showPause:(BOOL)arg1 animated:(BOOL)arg2;
- (void)showIdle:(BOOL)arg1 animated:(BOOL)arg2 duration:(float)arg3;
- (void)showIdle:(BOOL)arg1 animated:(BOOL)arg2;
- (void)showAutoPlayIdle:(BOOL)arg1 animated:(BOOL)arg2;
- (void)showBufferingProgress:(BOOL)arg1 animated:(BOOL)arg2;
- (id)initWithFrame:(struct CGRect)arg1;

@end

@interface IGFeedItemVideoCell : UITableViewCell
@property(retain, nonatomic) IGFeedItemVideoView *videoView;
@property(retain, nonatomic) IGPost *post;
- (id)accessibleElements;
- (int)indexOfAccessibilityElement:(id)arg1;
- (id)accessibilityElementAtIndex:(int)arg1;
- (int)accessibilityElementCount;
- (void)setNavigationController:(id)arg1;
- (void)layoutSubviews;
- (id)initWithReuseIdentifier:(id)arg1;

@end

@interface IGFeedItemVideoCell (everything_tweak) <UIDocumentInteractionControllerDelegate>
@end

@interface IGFeedItem : IGPost
@end

@interface IGFeedItemActionCell : UICollectionViewCell
@property(retain, nonatomic) IGFeedItem *feedItem; // @synthesize feedItem=_feedItem;
@property(retain, nonatomic) UIButton *sendButton; // @synthesize sendButton=_sendButton;
@property(retain, nonatomic) UIButton *moreButton; // @synthesize moreButton=_moreButton;
@property(retain, nonatomic) UIButton *commentButton; // @synthesize commentButton=_commentButton;
@property(retain, nonatomic) UIButton *likeButton; // @synthesize likeButton=_likeButton;

// my new button
- (UIButton *)ing_shareButton;
@end

@interface IGFeedItemHeaderViewModel : NSObject
@property (retain, nonatomic) NSDate *takenAt;
@property(retain, nonatomic) IGFeedItem *feedItem; // @synthesize feedItem=_feedItem;
@end

@interface IGFeedItemHeader : UIView
@property (readonly, nonatomic) IGFeedItemHeaderViewModel *viewModel;
@end


@interface UIImage (Tinted)
+ (id)IGTintedImageWithName:(id)arg1 tintColor:(id)arg2;
@end

@interface INSEnhancerLite : NSObject
// Instagram Stuffs
+ (NSString *)insta_DocumentsPath;
+ (void)addNotificationFromObserver:(id)target withName:(NSString *)notiName andSelector:(SEL)aSelector;
+ (void)postNotificationWithName:(NSString *)notiName andObject:(id)object ;
+ (NSURL *)urlFromVersionArray:(NSArray *)versions;

// INGEnhancer methods
+ (void)ingen_shareText:(NSString *)textToShare;
+ (void)ingen_shareFile:(NSString *)fileToShare;
+ (NSBundle *)ingen_bundle;
@end
