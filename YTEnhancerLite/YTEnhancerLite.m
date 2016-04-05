//
//  YTEnhancerLite.m
//  YTEnhancerLite
//
//  Created by iMokhles on 04/04/16.
//  Copyright © 2016 iMokhles. All rights reserved.
//

#import "YTEnhancerLite.h"
#import "XCDYouTubeKit.h"
#import "YTProcessor.h"
#import "TWRDownloadManager.h"
#import "TotoaShopHelper.h"
#import "DownloadsTVC.h"
#import "UIAlertView+Blocks.h"
#import "MBProgressHUD.h"
#import "TransNSString.h"


static UIWindow *currentWindow() {
    
    UIWindow *currentWindow = [UIApplication sharedApplication].keyWindow;
    
    if (!currentWindow) {
        NSEnumerator *frontToBackWindows = [[[UIApplication sharedApplication] windows] reverseObjectEnumerator];
        
        for (UIWindow *window in frontToBackWindows) {
            if (window.windowLevel == UIWindowLevelNormal) {
                currentWindow = window;
                break;
            }
        }
    }
    
    return currentWindow;
}
BOOL isAudioFile = NO;
NSTimeInterval videoDuration;
id currentCellView = nil;
static GOODialogActionButton *downloadButton = nil;
static NSString *videoTitle = nil;
static NSString *videoStaticID = nil;
static _Bool isDownloadsVC = NO;
static UIButton *downloadPage = nil;
static NSUserDefaults *userDefaults;
@implementation YTEnhancerLite

+ (instancetype)shareFeatures {
    static YTEnhancerLite *sharedInstance = nil;
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        sharedInstance = [[YTEnhancerLite alloc] init];
    });
    
    return sharedInstance;
}

- (id)init {
    if (self == [super init]) {
        
    }
    return self;
}

- (NSString *)timeFormatted:(int)totalSeconds{
    
    int seconds = totalSeconds % 60;
    int minutes = (totalSeconds / 60) % 60;
    int hours = totalSeconds / 3600;
    
    return [NSString stringWithFormat:@"%02d:%02d:%02d",hours, minutes, seconds];
}

- (NSArray *) preferredVideoQualities
{
    return @[ XCDYouTubeVideoQualityHTTPLiveStreaming, @(XCDYouTubeVideoQualityHD1080), @(XCDYouTubeVideoQualityHD720), @(XCDYouTubeVideoQualityMedium360), @(XCDYouTubeVideoQualitySmall240) ];
}

- (void)saveVideoToPlist:(XCDYouTubeVideo *)video {
    
    NSMutableArray *fileInfoArray = [userDefaults objectForKey:@"fileInfoArray"];
    NSMutableDictionary *newMutableDict = [NSMutableDictionary new];
    NSDictionary *newDict = nil;
    NSMutableArray *fileInfoArrayNEW = nil;
    if (!fileInfoArray) {
        fileInfoArray = [[NSMutableArray alloc] init];
        if (isAudioFile) {
            [newMutableDict setObject:[NSNumber numberWithBool:YES] forKey:@"isAudio"];
        } else {
            [newMutableDict setObject:[NSNumber numberWithBool:NO] forKey:@"isAudio"];
        }
        [newMutableDict setObject:[NSString stringWithFormat:@"%@", video.identifier] forKey:@"videoID"];
        [newMutableDict setObject:[NSString stringWithFormat:@"%@", video.mediumThumbnailURL] forKey:@"mediumThumbnailURL"];
        [newMutableDict setObject:[NSString stringWithFormat:@"%@", video.title] forKey:@"videoTitle"];
        [newMutableDict setObject:[NSString stringWithFormat:@"%@", [self timeFormatted:video.duration]] forKey:@"videoDuration"];
        newDict = [newMutableDict copy];
        [fileInfoArray addObject:newDict];
        [userDefaults setObject:fileInfoArray forKey:@"fileInfoArray"];
        [userDefaults synchronize];
    } else {
        fileInfoArrayNEW = [[NSMutableArray alloc] initWithArray:fileInfoArray];
        if (isAudioFile) {
            [newMutableDict setObject:[NSNumber numberWithBool:YES] forKey:@"isAudio"];
        } else {
            [newMutableDict setObject:[NSNumber numberWithBool:NO] forKey:@"isAudio"];
        }
        [newMutableDict setObject:[NSString stringWithFormat:@"%@", video.identifier] forKey:@"videoID"];
        [newMutableDict setObject:[NSString stringWithFormat:@"%@", video.mediumThumbnailURL] forKey:@"mediumThumbnailURL"];
        [newMutableDict setObject:[NSString stringWithFormat:@"%@", video.title] forKey:@"videoTitle"];
        [newMutableDict setObject:[NSString stringWithFormat:@"%@", [self timeFormatted:video.duration]] forKey:@"videoDuration"];
        newDict = [newMutableDict copy];
        for (NSDictionary *dictCheck in fileInfoArray) {
            NSString *curHex = dictCheck[@"videoID"];
            NSNumber *audioNM = dictCheck[@"isAudio"];
            BOOL isAudio = [audioNM boolValue];
            
            NSNumber *audioNewNM = newDict[@"isAudio"];
            BOOL isNewAudio = [audioNewNM boolValue];
            
            if ([curHex isEqualToString:newDict[@"videoID"]] && isAudio == isNewAudio) {
                return;
            }
        }
        [fileInfoArrayNEW addObject:newDict];
        [userDefaults setObject:fileInfoArrayNEW forKey:@"fileInfoArray"];
        [userDefaults synchronize];
    }
}
- (void)getVideoInformationFromID:(NSString *)videoID forINT:(NSInteger)intger {
    [[XCDYouTubeClient defaultClient] getVideoWithIdentifier:videoID completionHandler:^(XCDYouTubeVideo * _Nullable video, NSError * _Nullable error) {
        if (video) {
            dispatch_async(dispatch_get_main_queue(), ^{
                MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:currentWindow() animated:YES];
                hud.labelText = @"Preparing";
            });
            videoTitle = video.title;
            videoStaticID = video.identifier;
            videoDuration = video.duration;
            NSURL *streamVideoURL = nil;
            NSURL *streamAudioURL = nil;
            if (intger == 0) {
                isAudioFile = NO;
                streamVideoURL = video.streamURLs[[NSNumber numberWithInt:XCDYouTubeVideoQualityHD720]];
            } else if (intger == 1) {
                isAudioFile = NO;
                streamVideoURL = video.streamURLs[[NSNumber numberWithInt:XCDYouTubeVideoQualityMedium360]];
            } else if (intger == 2) {
                isAudioFile = YES;
                streamVideoURL = video.streamURLs[[NSNumber numberWithInt:XCDYouTubeAudioOnly140]];
            }
            streamAudioURL = video.streamURLs[[NSNumber numberWithInt:XCDYouTubeAudioOnly140]];
            NSURL *midURL = streamVideoURL;
            if(midURL == nil){
                midURL = [[video.streamURLs objectEnumerator] nextObject];
            }
            NSString *filePath;
            
            if (intger == 0 || intger == 1) {
                filePath = [[TotoaShopHelper getDownloadsPath] stringByAppendingPathComponent:[NSString stringWithFormat:@"mp4/%@-%@.mp4", video.title, video.identifier]];
            } else {
                filePath = [[TotoaShopHelper getDownloadsPath] stringByAppendingPathComponent:[NSString stringWithFormat:@"m4a/%@-%@.m4a", video.title, video.identifier]];
            }
            if (![[NSFileManager defaultManager] fileExistsAtPath:filePath]) {
                [self saveVideoToPlist:video];
                NSURLRequest    *req  = [NSURLRequest requestWithURL:midURL];//[NSURL URLWithString:]];
                NSURLConnection *conn = [NSURLConnection connectionWithRequest:req delegate:self];
                [conn start];
            } else {
                [UIAlertView showWithTitle:@"YTEnhancer (WARNING)" message:@"Video downloaded already !!" cancelButtonTitle:@"Ok" otherButtonTitles:nil tapBlock:^(UIAlertView * _Nonnull alertView, NSInteger buttonIndex) {
                    dispatch_async(dispatch_get_main_queue(), ^{
                        MBProgressHUD *hud = [MBProgressHUD HUDForView:currentWindow()];
                        hud.labelText = @"Failed";
                        [hud hide:YES afterDelay:3.f];
                    });
                }];
                
            }
            NSLog(@"*********** \n%@\n\n%@\nDuration: %@\n", streamAudioURL, streamVideoURL, [self timeFormatted:video.duration]);
            
        }
        
    }];
}
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
    NSString *mime = [response MIMEType];
    NSString *urlToDOwnload = response.URL.absoluteString;
    CFStringRef uti = UTTypeCreatePreferredIdentifierForTag(kUTTagClassMIMEType, (__bridge CFStringRef)(mime), NULL);
    CFStringRef extension = UTTypeCopyPreferredTagWithClass(uti, kUTTagClassFilenameExtension);
    NSString *fileExtension = (NSString *)CFBridgingRelease(extension);
    
    NSString *savedPath;
    if (isAudioFile == NO) {
        savedPath = [NSString stringWithFormat:@"%@-%@.%@",videoTitle, videoStaticID, [NSString stringWithFormat:@"%@",fileExtension]];
    } else {
        savedPath = [NSString stringWithFormat:@"%@-%@.m4a",videoTitle, videoStaticID];
    }
    
    TWRDownloadManager *downloadManager = [TWRDownloadManager sharedManager];
    [downloadManager downloadFileForURL:urlToDOwnload withName:savedPath inDirectoryNamed:nil progressBlock:^(CGFloat progress) {
        //
        dispatch_async(dispatch_get_main_queue(), ^{
            MBProgressHUD *hud = [MBProgressHUD HUDForView:currentWindow()];
            hud.labelText = @"Downloading...";
            hud.mode = MBProgressHUDModeDeterminate;
            hud.progress = progress;
        });
    } completionBlock:^(BOOL completed) {
        //
        dispatch_async(dispatch_get_main_queue(), ^{
            MBProgressHUD *hud = [MBProgressHUD HUDForView:currentWindow()];
            hud.labelText = @"Completed...";
            hud.mode = MBProgressHUDModeIndeterminate;
            [hud hide:YES afterDelay:3.f];
        });
        videoTitle = nil;
    } enableBackgroundMode:YES];
    
}
- (void)handleAction:(SEL)selector fromTarget:(id)target {
    [target performSelector:selector];
}

- (void)openDownloadsPage {
    
    DownloadsTVC *dwnsVC = [[DownloadsTVC alloc] initWithStyle:UITableViewStylePlain];
    UINavigationController *dwnsNVC = [[UINavigationController alloc] initWithRootViewController:dwnsVC];
    dwnsNVC.modalPresentationStyle = UIModalPresentationFormSheet;
    [[[UIApplication sharedApplication] windows][0].rootViewController presentViewController:dwnsNVC animated:YES completion:^{
        
    }];
}

@end

hook(GOOActionSheetController)
- (void)popoverViewControllerDidCancel:(id)arg1 {
    NSLog(@"********* popoverViewControllerDidCancel");
    downloadButton = nil;
    _orig(void, arg1);
}
- (void)dismiss {
    NSLog(@"********* dismiss");
    downloadButton = nil;
    _orig(void);
}
- (void)addAction:(id)arg1 {
    NSLog(@"********* addAction");
    _orig(void, arg1);
}
- (void)present {
    NSLog(@"********* addAction");
    _orig(void);
    id btnSuperView = [[(GOOActionSheetController *)self sourceView] superview];
    if ([btnSuperView isKindOfClass:NSClassFromString(@"YTVideoView")] || [[btnSuperView superview] isKindOfClass:objc_getClass("YTVideoCell")] || [[btnSuperView superview] isKindOfClass:objc_getClass("YTGridVideoCell")] || [btnSuperView isKindOfClass:NSClassFromString(@"YTGridVideoView")] || [btnSuperView isKindOfClass:NSClassFromString(@"YTCompactVideoView")]) {
        
        UIImage *downloadImage = [UIImage imageNamed:@"downbutton"]; // won't appear ;)
        UIImage *downloadResized = [downloadImage imageByScalingToSize:CGSizeMake(24, 24)];
        [self addAction:[objc_getClass("GOOAction") actionWithTitle:[NSString translateToAR:@"صفحة التحميلات" toCA:nil toCS:nil toDA:nil toDE:nil toEL:nil toEN:@"Downloads Page" toEN_AU:nil toEN_GB:nil toES:nil toES_MX:nil toFI:nil toFR:nil toFR_CA:nil toHE:nil toHI:nil toHR:nil toHU:nil toID:nil toIT:nil toJA:nil toKO:nil toMS:nil toNL:nil toNO:nil toPL:nil toPT:nil toPT_PT:nil toRO:nil toRU:nil toSK:nil toSV:nil toTH:nil toTR:nil toUK:nil toVI:nil toZH_CN:nil toZH_HK:nil toZH_TW:nil] iconImage:downloadResized style:1 handler:^{
            [[YTEnhancerLite shareFeatures] openDownloadsPage];
            
        }]];
        
        [self addAction:[objc_getClass("GOOAction") actionWithTitle:[NSString translateToAR:@"HD720 تحميل جودة" toCA:nil toCS:nil toDA:nil toDE:nil toEL:nil toEN:@"Download 720HD" toEN_AU:nil toEN_GB:nil toES:nil toES_MX:nil toFI:nil toFR:nil toFR_CA:nil toHE:nil toHI:nil toHR:nil toHU:nil toID:nil toIT:nil toJA:nil toKO:nil toMS:nil toNL:nil toNO:nil toPL:nil toPT:nil toPT_PT:nil toRO:nil toRU:nil toSK:nil toSV:nil toTH:nil toTR:nil toUK:nil toVI:nil toZH_CN:nil toZH_HK:nil toZH_TW:nil] iconImage:downloadResized style:1 handler:^{
            NSString *videoPreID = nil;
            if ([[(GOOActionSheetController *)self sourceView] isKindOfClass:objc_getClass("YTButton")]) {
                if ([btnSuperView isKindOfClass:NSClassFromString(@"YTVideoView")]) {
                    YTVideoCell *videoCell = (YTVideoCell *)[(YTVideoView *)btnSuperView superview].superview;
                    YTIVideoRenderer *videoRenderer = [videoCell valueForKey:@"_videoRenderer"];
                    videoPreID = videoRenderer.videoId;
                    NSLog(@"FOUND1: %@\nVideID: %@", NSStringFromClass([videoCell class]), videoRenderer.videoId);
                } else if ([btnSuperView isKindOfClass:NSClassFromString(@"YTGridVideoView")]) {
                    YTGridVideoView *videoGridView = btnSuperView;
                    YTIGridVideoRenderer *videoGridRenderer = [videoGridView valueForKey:@"_entry"];
                    videoPreID = videoGridRenderer.videoId;
                    //                YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[(YTGridVideoView *)btnSuperView superview];
                    NSLog(@"FOUND2: %@\nVideID: %@", NSStringFromClass([videoGridView class]), videoGridRenderer.videoId);
                } else if ([btnSuperView isKindOfClass:NSClassFromString(@"YTCompactVideoView")]) {
                    YTCompactVideoView *videoCompactView = btnSuperView;
                    YTICompactVideoRenderer *videoCompactRenderer = [videoCompactView valueForKey:@"_renderer"];
                    videoPreID = videoCompactRenderer.videoId;
                    //                YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[(YTGridVideoView *)btnSuperView superview];
                    NSLog(@"FOUND2: %@\nVideID: %@", NSStringFromClass([videoCompactView class]), videoCompactRenderer.videoId);
                }
            } else {
                NSLog(@"FOUND3: %@", NSStringFromClass([btnSuperView class])); // UIView
                NSLog(@"FOUND4: %@", NSStringFromClass([[btnSuperView superview] class])); // YTGridVideoCell || YTVideoCell
                
                if ([[btnSuperView superview] isKindOfClass:objc_getClass("YTVideoCell")]) {
                    YTVideoCell *videoCell = (YTVideoCell *)[btnSuperView superview];
                    YTIVideoRenderer *videoRenderer = [videoCell valueForKey:@"_videoRenderer"];
                    videoPreID = videoRenderer.videoId;
                } else if ([[btnSuperView superview] isKindOfClass:objc_getClass("YTGridVideoCell")]) {
                    YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[btnSuperView superview];
                    YTGridVideoView *videoGridView = (YTGridVideoView *)videoGridCell.gridView;
                    YTIGridVideoRenderer *videoGridRenderer = [videoGridView valueForKey:@"_entry"];
                    videoPreID = videoGridRenderer.videoId;
                } else if ([btnSuperView isKindOfClass:NSClassFromString(@"YTCompactVideoCell")]) {
                    YTCompactVideoView *videoCompactView = [btnSuperView valueForKey:@"_videoView"];
                    YTICompactVideoRenderer *videoCompactRenderer = [videoCompactView valueForKey:@"_renderer"];
                    videoPreID = videoCompactRenderer.videoId;
                    //                YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[(YTGridVideoView *)btnSuperView superview];
                    NSLog(@"FOUND2: %@\nVideID: %@", NSStringFromClass([videoCompactView class]), videoCompactRenderer.videoId);
                }
            }
            [[YTEnhancerLite shareFeatures] getVideoInformationFromID:videoPreID forINT:0];
            
        }]];
        
        [self addAction:[objc_getClass("GOOAction") actionWithTitle:[NSString translateToAR:@"تحميل جودة 360" toCA:nil toCS:nil toDA:nil toDE:nil toEL:nil toEN:@"Download 360" toEN_AU:nil toEN_GB:nil toES:nil toES_MX:nil toFI:nil toFR:nil toFR_CA:nil toHE:nil toHI:nil toHR:nil toHU:nil toID:nil toIT:nil toJA:nil toKO:nil toMS:nil toNL:nil toNO:nil toPL:nil toPT:nil toPT_PT:nil toRO:nil toRU:nil toSK:nil toSV:nil toTH:nil toTR:nil toUK:nil toVI:nil toZH_CN:nil toZH_HK:nil toZH_TW:nil] iconImage:downloadResized style:1 handler:^{
            NSString *videoPreID = nil;
            if ([[(GOOActionSheetController *)self sourceView] isKindOfClass:objc_getClass("YTButton")]) {
                if ([btnSuperView isKindOfClass:NSClassFromString(@"YTVideoView")]) {
                    YTVideoCell *videoCell = (YTVideoCell *)[(YTVideoView *)btnSuperView superview].superview;
                    YTIVideoRenderer *videoRenderer = [videoCell valueForKey:@"_videoRenderer"];
                    videoPreID = videoRenderer.videoId;
                    NSLog(@"FOUND1: %@\nVideID: %@", NSStringFromClass([videoCell class]), videoRenderer.videoId);
                } else if ([btnSuperView isKindOfClass:NSClassFromString(@"YTGridVideoView")]) {
                    YTGridVideoView *videoGridView = btnSuperView;
                    YTIGridVideoRenderer *videoGridRenderer = [videoGridView valueForKey:@"_entry"];
                    videoPreID = videoGridRenderer.videoId;
                    //                YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[(YTGridVideoView *)btnSuperView superview];
                    NSLog(@"FOUND2: %@\nVideID: %@", NSStringFromClass([videoGridView class]), videoGridRenderer.videoId);
                } else if ([btnSuperView isKindOfClass:NSClassFromString(@"YTCompactVideoView")]) {
                    YTCompactVideoView *videoCompactView = btnSuperView;
                    YTICompactVideoRenderer *videoCompactRenderer = [videoCompactView valueForKey:@"_renderer"];
                    videoPreID = videoCompactRenderer.videoId;
                    //                YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[(YTGridVideoView *)btnSuperView superview];
                    NSLog(@"FOUND2: %@\nVideID: %@", NSStringFromClass([videoCompactView class]), videoCompactRenderer.videoId);
                }
            } else {
                NSLog(@"FOUND3: %@", NSStringFromClass([btnSuperView class])); // UIView
                NSLog(@"FOUND4: %@", NSStringFromClass([[btnSuperView superview] class])); // YTGridVideoCell || YTVideoCell
                
                if ([[btnSuperView superview] isKindOfClass:objc_getClass("YTVideoCell")]) {
                    YTVideoCell *videoCell = (YTVideoCell *)[btnSuperView superview];
                    YTIVideoRenderer *videoRenderer = [videoCell valueForKey:@"_videoRenderer"];
                    videoPreID = videoRenderer.videoId;
                } else if ([[btnSuperView superview] isKindOfClass:objc_getClass("YTGridVideoCell")]) {
                    YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[btnSuperView superview];
                    YTGridVideoView *videoGridView = (YTGridVideoView *)videoGridCell.gridView;
                    YTIGridVideoRenderer *videoGridRenderer = [videoGridView valueForKey:@"_entry"];
                    videoPreID = videoGridRenderer.videoId;
                } else if ([btnSuperView isKindOfClass:NSClassFromString(@"YTCompactVideoCell")]) {
                    YTCompactVideoView *videoCompactView = [btnSuperView valueForKey:@"_videoView"];
                    YTICompactVideoRenderer *videoCompactRenderer = [videoCompactView valueForKey:@"_renderer"];
                    videoPreID = videoCompactRenderer.videoId;
                    //                YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[(YTGridVideoView *)btnSuperView superview];
                    NSLog(@"FOUND2: %@\nVideID: %@", NSStringFromClass([videoCompactView class]), videoCompactRenderer.videoId);
                }
            }
            [[YTEnhancerLite shareFeatures] getVideoInformationFromID:videoPreID forINT:1];
            
        }]];
        [self addAction:[objc_getClass("GOOAction") actionWithTitle:[NSString translateToAR:@"تحميل صوت" toCA:nil toCS:nil toDA:nil toDE:nil toEL:nil toEN:@"Download Audio" toEN_AU:nil toEN_GB:nil toES:nil toES_MX:nil toFI:nil toFR:nil toFR_CA:nil toHE:nil toHI:nil toHR:nil toHU:nil toID:nil toIT:nil toJA:nil toKO:nil toMS:nil toNL:nil toNO:nil toPL:nil toPT:nil toPT_PT:nil toRO:nil toRU:nil toSK:nil toSV:nil toTH:nil toTR:nil toUK:nil toVI:nil toZH_CN:nil toZH_HK:nil toZH_TW:nil] iconImage:downloadResized style:1 handler:^{
            NSString *videoPreID = nil;
            if ([[(GOOActionSheetController *)self sourceView] isKindOfClass:objc_getClass("YTButton")]) {
                if ([btnSuperView isKindOfClass:NSClassFromString(@"YTVideoView")]) {
                    YTVideoCell *videoCell = (YTVideoCell *)[(YTVideoView *)btnSuperView superview].superview;
                    YTIVideoRenderer *videoRenderer = [videoCell valueForKey:@"_videoRenderer"];
                    videoPreID = videoRenderer.videoId;
                    NSLog(@"FOUND1: %@\nVideID: %@", NSStringFromClass([videoCell class]), videoRenderer.videoId);
                } else if ([btnSuperView isKindOfClass:NSClassFromString(@"YTGridVideoView")]) {
                    YTGridVideoView *videoGridView = btnSuperView;
                    YTIGridVideoRenderer *videoGridRenderer = [videoGridView valueForKey:@"_entry"];
                    videoPreID = videoGridRenderer.videoId;
                    //                YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[(YTGridVideoView *)btnSuperView superview];
                    NSLog(@"FOUND2: %@\nVideID: %@", NSStringFromClass([videoGridView class]), videoGridRenderer.videoId);
                } else if ([btnSuperView isKindOfClass:NSClassFromString(@"YTCompactVideoView")]) {
                    YTCompactVideoView *videoCompactView = btnSuperView;
                    YTICompactVideoRenderer *videoCompactRenderer = [videoCompactView valueForKey:@"_renderer"];
                    videoPreID = videoCompactRenderer.videoId;
                    //                YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[(YTGridVideoView *)btnSuperView superview];
                    NSLog(@"FOUND2: %@\nVideID: %@", NSStringFromClass([videoCompactView class]), videoCompactRenderer.videoId);
                }
            } else {
                NSLog(@"FOUND3: %@", NSStringFromClass([btnSuperView class])); // UIView
                NSLog(@"FOUND4: %@", NSStringFromClass([[btnSuperView superview] class])); // YTGridVideoCell || YTVideoCell
                
                if ([[btnSuperView superview] isKindOfClass:objc_getClass("YTVideoCell")]) {
                    YTVideoCell *videoCell = (YTVideoCell *)[btnSuperView superview];
                    YTIVideoRenderer *videoRenderer = [videoCell valueForKey:@"_videoRenderer"];
                    videoPreID = videoRenderer.videoId;
                } else if ([[btnSuperView superview] isKindOfClass:objc_getClass("YTGridVideoCell")]) {
                    YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[btnSuperView superview];
                    YTGridVideoView *videoGridView = (YTGridVideoView *)videoGridCell.gridView;
                    YTIGridVideoRenderer *videoGridRenderer = [videoGridView valueForKey:@"_entry"];
                    videoPreID = videoGridRenderer.videoId;
                } else if ([btnSuperView isKindOfClass:NSClassFromString(@"YTCompactVideoCell")]) {
                    YTCompactVideoView *videoCompactView = [btnSuperView valueForKey:@"_videoView"];
                    YTICompactVideoRenderer *videoCompactRenderer = [videoCompactView valueForKey:@"_renderer"];
                    videoPreID = videoCompactRenderer.videoId;
                    //                YTGridVideoCell *videoGridCell = (YTGridVideoCell *)[(YTGridVideoView *)btnSuperView superview];
                    NSLog(@"FOUND2: %@\nVideID: %@", NSStringFromClass([videoCompactView class]), videoCompactRenderer.videoId);
                }
            }
            [[YTEnhancerLite shareFeatures] getVideoInformationFromID:videoPreID forINT:2];
            
        }]];
    }
}
endhook

hook(YTIPlayabilityStatus)
- (_Bool)playableInBackground {
    return YES;
}
- (_Bool)playableOffline {
    return YES;
}
- (_Bool)hasOfflineability {
    return YES;
}
- (_Bool)hasPlayableInBackground {
    return YES;
}
- (_Bool)isPlayableInBackground {
    return YES;
}
endhook

hook(MLAVPlayer)
- (_Bool)backgroundPlaybackAllowed {
    return YES;
}
endhook

hook(MLEXOPlayer)
- (_Bool)backgroundPlaybackAllowed {
    return YES;
}
endhook

ctor {
    userDefaults = [NSUserDefaults standardUserDefaults];
}

