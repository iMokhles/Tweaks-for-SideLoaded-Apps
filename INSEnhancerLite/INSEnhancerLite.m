//
//  INSEnhancerLite.m
//  INSEnhancerLite
//
//  Created by iMokhles on 04/04/16.
//  Copyright © 2016 iMokhles. All rights reserved.
//

#import "INSEnhancerLite.h"

static NSString *staticPath = nil;
static UIImage *staticImage = nil;
static BOOL isOldSave = NO;

@interface INSEnhancerLite () <QLPreviewControllerDataSource, QLPreviewControllerDelegate>
@end

@implementation INSEnhancerLite
+ (instancetype)shareFeatures {
    static INSEnhancerLite *sharedInstance = nil;
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        sharedInstance = [[INSEnhancerLite alloc] init];
    });
    
    return sharedInstance;
}

- (id)init {
    if (self == [super init]) {
        
    }
    return self;
}

+ (NSString *)insta_DocumentsPath {
    NSArray  *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString  *documentsDirectory = [paths objectAtIndex:0];
    return documentsDirectory;
}

+ (void)addNotificationFromObserver:(id)target withName:(NSString *)notiName andSelector:(SEL)aSelector {
    [[NSNotificationCenter defaultCenter] addObserver:target selector:aSelector name:notiName object:nil];
}
+ (void)postNotificationWithName:(NSString *)notiName andObject:(id)object {
    NSNotificationCenter* nc = [NSNotificationCenter defaultCenter];
    [nc postNotificationName:notiName object:object userInfo:nil];
}

+ (UIWindow *)mainINGEnhancerWindow {
    return [[UIApplication sharedApplication] windows][0];
}

+ (UIViewController *)mainINGEnhancerViewController {
    return self.mainINGEnhancerWindow.rootViewController;
}

+ (NSURL *)urlFromVersionArray:(NSArray *)versions {
    NSURL *url;
    CGFloat hightResolution = 0.0;
    for (NSDictionary *versionDict in versions) {
        CGFloat height = [versionDict[@"height"] floatValue];
        CGFloat width = [versionDict[@"width"] floatValue];
        CGFloat resolution = height * width;
        
        if (resolution > hightResolution) {
            hightResolution = resolution;
            url = [NSURL URLWithString:versionDict[@"url"]];
        }
    }
    return url;
}

+ (UIView *)mainView {
    UIView *view;
    if (!view) {
        UIWindow *keyWindow = [UIWindow keyWindow];
        if ([UIWindow respondsToSelector:@selector(rootViewController)])
            view = [[keyWindow rootViewController] view];
        if (!view)
            view = [keyWindow.subviews lastObject];
    }
    return view;
}

// INGEnhancer methods
+ (void)ingen_shareText:(NSString *)textToShare {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        UIActivityViewController *activityViewController = [[UIActivityViewController alloc] initWithActivityItems:@[textToShare] applicationActivities:@[]];
        if (IS_IPAD) {
            UIPopoverController *activityPopoverController = [[UIPopoverController alloc] initWithContentViewController:activityViewController];
            [activityPopoverController presentPopoverFromRect:CGRectMake([self mainView].bounds.size.width / 2.0, [self mainView].bounds.size.height / 2.0, 1.0, 1.0) inView:[self mainView] permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
        } else {
            dispatch_async(dispatch_get_main_queue(), ^{
                [[self mainINGEnhancerViewController] presentViewController:activityViewController animated:YES completion:NULL];
            });
        }
        
    });
}
+ (void)ingen_shareFile:(NSString *)fileToShare {
    staticPath = fileToShare;
    QLPreviewController *preview = [[QLPreviewController alloc] init];
    preview.dataSource = [INSEnhancerLite shareFeatures];
    
    [[self mainINGEnhancerViewController] presentViewController:preview animated:YES completion:^{
        
    }];
}

+ (void)ingen_shareImage:(UIImage *)image {
    staticImage = image;
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *filePath = [[paths objectAtIndex:0] stringByAppendingPathComponent:@"Image.png"];
    // Save image.
    [UIImagePNGRepresentation(staticImage) writeToFile:filePath atomically:YES];
    staticPath = filePath;
    QLPreviewController *preview = [[QLPreviewController alloc] init];
    preview.dataSource = [INSEnhancerLite shareFeatures];
    
    [[self mainINGEnhancerViewController] presentViewController:preview animated:YES completion:^{
        
    }];
}

#pragma mark - QuickLook

- (BOOL)previewController:(QLPreviewController *)controller shouldOpenURL:(NSURL *)url forPreviewItem:(id <QLPreviewItem>)item {
    
    return YES;
}
- (NSInteger) numberOfPreviewItemsInPreviewController: (QLPreviewController *) controller {
    return 1;
}
- (id <QLPreviewItem>) previewController: (QLPreviewController *) controller previewItemAtIndex: (NSInteger) index {
    
    return [NSURL fileURLWithPath:staticPath];
}

+ (NSBundle *)ingen_bundle {
    return [NSBundle mainBundle];
}
@end

hook(IGCoreTextView)
- (void)handleLongTap {
    // i don't like this feature so i replaced it easily :P
    [INSEnhancerLite ingen_shareText:[(IGCoreTextView *)self styledString].attributedString.string];
}
endhook

hook(IGFeedItemPhotoCell)
- (void)layoutSubviews {
    [INSEnhancerLite addNotificationFromObserver:self withName:@"INGShareImageNotification" andSelector:@selector(showShareImageSheet:)];
    _orig(void);
}

- (void)showShareImageSheet:(NSNotification *)notification {
    NSURL *imageURL = (NSURL *)[notification object];
    NSData *urlData = [NSData dataWithContentsOfURL:imageURL];
    UIImage *imageToShare = [UIImage imageWithData:urlData];
    NSData *pngData = UIImagePNGRepresentation(imageToShare);
    
    if (pngData) {
        NSString  *filePath = [NSString stringWithFormat:@"%@/%@", [INSEnhancerLite insta_DocumentsPath], @"image.png"];
        [pngData writeToFile:filePath atomically:YES];
        double delayInSeconds = 0.5;
        dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, delayInSeconds * NSEC_PER_SEC);
        dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
            [INSEnhancerLite ingen_shareImage:imageToShare];
        });
    }
    
}
endhook

hook(IGFeedItemVideoCell)
- (void)layoutSubviews {
    [INSEnhancerLite addNotificationFromObserver:self withName:@"INGShareVideoNotification" andSelector:@selector(showShareVideoSheet:)];
    _orig(void);
}

- (void)showShareVideoSheet:(NSNotification *)notification {
    NSURL *videoURL = (NSURL *)[notification object];
    NSData *videoData = [NSData dataWithContentsOfURL:videoURL];
    if (videoData) {
        NSString  *filePath = [NSString stringWithFormat:@"%@/%@", [INSEnhancerLite insta_DocumentsPath], @"video.mp4"];
        [videoData writeToFile:filePath atomically:YES];
        double delayInSeconds = 0.5;
        dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, delayInSeconds * NSEC_PER_SEC);
        dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
            [INSEnhancerLite ingen_shareFile:filePath];
        });
    }
    
}
endhook

hook(IGFeedItemHeader)
- (void)onChevronTapped:(id)arg1 {
    if (!isOldSave) {
        NSString *chooseTitle = [NSString translateToAR:@"إختار مشاركة لفتحها" toCA:nil toCS:nil toDA:nil toDE:nil toEL:nil toEN:@"Choose option" toEN_AU:nil toEN_GB:nil toES:nil toES_MX:nil toFI:nil toFR:nil toFR_CA:nil toHE:nil toHI:nil toHR:nil toHU:nil toID:nil toIT:nil toJA:nil toKO:nil toMS:nil toNL:nil toNO:nil toPL:nil toPT:nil toPT_PT:nil toRO:nil toRU:nil toSK:nil toSV:nil toTH:nil toTR:nil toUK:nil toVI:nil toZH_CN:nil toZH_HK:nil toZH_TW:nil];
        
        NSString *tweakSettings = [NSString translateToAR:@"مشاركة الاداة" toCA:nil toCS:nil toDA:nil toDE:nil toEL:nil toEN:@"Tweak Share" toEN_AU:nil toEN_GB:nil toES:nil toES_MX:nil toFI:nil toFR:nil toFR_CA:nil toHE:nil toHI:nil toHR:nil toHU:nil toID:nil toIT:nil toJA:nil toKO:nil toMS:nil toNL:nil toNO:nil toPL:nil toPT:nil toPT_PT:nil toRO:nil toRU:nil toSK:nil toSV:nil toTH:nil toTR:nil toUK:nil toVI:nil toZH_CN:nil toZH_HK:nil toZH_TW:nil];
        
        NSString *appSettings = [NSString translateToAR:@"مشاركة التطبيق" toCA:nil toCS:nil toDA:nil toDE:nil toEL:nil toEN:@"App Share" toEN_AU:nil toEN_GB:nil toES:nil toES_MX:nil toFI:nil toFR:nil toFR_CA:nil toHE:nil toHI:nil toHR:nil toHU:nil toID:nil toIT:nil toJA:nil toKO:nil toMS:nil toNL:nil toNO:nil toPL:nil toPT:nil toPT_PT:nil toRO:nil toRU:nil toSK:nil toSV:nil toTH:nil toTR:nil toUK:nil toVI:nil toZH_CN:nil toZH_HK:nil toZH_TW:nil];
        
        
        [UIAlertView showWithTitle:@"INSEnhancer" message:chooseTitle cancelButtonTitle:tweakSettings otherButtonTitles:@[appSettings] tapBlock:^(UIAlertView * _Nonnull alertView, NSInteger buttonIndex) {
            if ([[alertView buttonTitleAtIndex:buttonIndex] isEqualToString:appSettings]) {
                isOldSave = YES;
                [self onChevronTapped:nil];
            } else if ([[alertView buttonTitleAtIndex:buttonIndex] isEqualToString:tweakSettings]) {
                isOldSave = NO;
                [self shareButtonPressed];
            }
        }];
    } else {
        isOldSave = NO;
        _orig(void);
    }
}

- (void)shareButtonPressed {
    int mediaType = [[(IGFeedItemHeader *)self viewModel] feedItem].mediaType;
    if (mediaType == 1) {
        // Shre image
        NSURL *imageURL = [INSEnhancerLite urlFromVersionArray:[[(IGFeedItemHeader *)self viewModel] feedItem].photo.imageVersions];
        [INSEnhancerLite postNotificationWithName:@"INGShareImageNotification" andObject:imageURL];
    } else {
        if (mediaType == 2) {
            // Share Video
            NSURL *videoURL = [INSEnhancerLite urlFromVersionArray:[[(IGFeedItemHeader *)self viewModel] feedItem].video.videoVersions];
            [INSEnhancerLite postNotificationWithName:@"INGShareVideoNotification" andObject:videoURL];
        }
    }
}
endhook






