//
//  SCFeaturesLite.m
//  SCFeaturesLite
//
//  Created by iMokhles on 04/04/16.
//  Copyright © 2016 iMokhles. All rights reserved.
//

#import "SCFeaturesLite.h"

static UIButton *saveSnapButton;
static AVPlayer *videoPlayer = nil;
static BOOL isImageMedia = NO;

static AVCameraViewController *middleViewController() {
    UINavigationController *viewController = (UINavigationController *)[[UIApplication sharedApplication] windows][0].rootViewController;
    MainViewController *mainVC = (MainViewController *)viewController.topViewController;
    
    if (![mainVC respondsToSelector:@selector(middleVC)]) {
        return (AVCameraViewController *)mainVC;
    }
    return mainVC.middleVC;
}

static MainViewController *mainViewC() {
    UINavigationController *viewController = (UINavigationController *)[[UIApplication sharedApplication] windows][0].rootViewController;
    MainViewController *mainVC = (MainViewController *)viewController.topViewController;
    
    return mainVC;
}

@implementation SCFeaturesLite
+ (instancetype)shareFeatures {
    static SCFeaturesLite *sharedInstance = nil;
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        sharedInstance = [[SCFeaturesLite alloc] init];
    });
    
    return sharedInstance;
}

- (id)init {
    if (self == [super init]) {
        
    }
    return self;
}

-(void)shake: (UIView*)theView {
    CAKeyframeAnimation * anim = [ CAKeyframeAnimation animationWithKeyPath:@"transform" ] ;
    anim.values = @[ [ NSValue valueWithCATransform3D:CATransform3DMakeTranslation(-5.0f, 0.0f, 0.0f) ], [ NSValue valueWithCATransform3D:CATransform3DMakeTranslation(5.0f, 0.0f, 0.0f) ] ] ;
    anim.autoreverses = YES ;
    anim.repeatCount = 2.0f ;
    anim.duration = 0.07f ;
    
    [ theView.layer addAnimation:anim forKey:nil ] ;
}

@end

hook(SCChatViewController)
-(void)tapToSkip:(UIGestureRecognizer *)tap {
    CGPoint coords = [tap locationInView:tap.view];
    
    if (coords.x < [UIScreen mainScreen].bounds.size.width - 100 || coords.y < [UIScreen mainScreen].bounds.size.height - 100 ) {
        
    }
    _orig(void, tap);
}
endhook


hook(SCFeedViewController)
-(void)tapToSkip:(UIGestureRecognizer *)tap {
    CGPoint coords = [tap locationInView:tap.view];
    
    if (coords.x < [UIScreen mainScreen].bounds.size.width - 100 || coords.y < [UIScreen mainScreen].bounds.size.height - 100 ) {
        
    }
    _orig(void, tap);
}
endhook


hook(SCViewingStoryViewController)
-(void)tapToSkip:(UIGestureRecognizer *)tap {
    CGPoint coords = [tap locationInView:tap.view];
    
    if (coords.x < [UIScreen mainScreen].bounds.size.width - 100 || coords.y < [UIScreen mainScreen].bounds.size.height - 100 ) {
        
    }
    
    _orig(void, tap);
}
endhook

hook(SCMediaView)
- (void)playPlayer:(AVPlayer *)arg1 {
    videoPlayer = arg1;
    isImageMedia = NO;
    [self addSaveVideoAction];
    _orig(void, arg1);
}
- (void)addSaveVideoAction {
    isImageMedia = NO;
    [saveSnapButton removeTarget:nil action:NULL forControlEvents:UIControlEventTouchUpInside];
    [saveSnapButton addTarget:videoPlayer action:@selector(saveVideoSnapButtonPress:) forControlEvents:UIControlEventTouchUpInside];
}
- (void)finishedPlayingMedia:(id)arg1 {
    [saveSnapButton removeFromSuperview];
    _orig(void, arg1);
    if ([(SCMediaView *)self superview] != nil) {
        [[(SCMediaView *)self window] addSubview:saveSnapButton];
        [[(SCMediaView *)self window] bringSubviewToFront:saveSnapButton];
    }
}
- (void)hideMedia {
    [saveSnapButton removeFromSuperview];
    _orig(void);
}
- (void)didMoveToWindow {
    _orig(void);
    if (![saveSnapButton.superview isEqual:[(SCMediaView *)self window]]) {
        saveSnapButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [saveSnapButton setFrame:CGRectMake([UIScreen mainScreen].bounds.size.width - 100, [UIScreen mainScreen].bounds.size.height - 100, 60, 60)];
        [saveSnapButton setImage:[UIImage imageNamed:@"save_button"] forState:UIControlStateNormal];
        [saveSnapButton setImageEdgeInsets:UIEdgeInsetsMake(19, 0, 19, 0)];
        saveSnapButton.layer.cornerRadius = 60/2.0f;
        saveSnapButton.layer.borderColor=[UIColor whiteColor].CGColor;
        saveSnapButton.layer.borderWidth=2.0f;
        if ([(SCMediaView *)self superview] != nil) {
            [[(SCMediaView *)self window] addSubview:saveSnapButton];
            [[(SCMediaView *)self window] bringSubviewToFront:saveSnapButton];
        }
        
        for (int i = 0; i < [(SCMediaView *)self playerViews].count; i++) {
            SCPlayerView *player1 = [[(SCMediaView *)self playerViews] objectAtIndex:0];
            SCPlayerView *player2 = [[(SCMediaView *)self playerViews] objectAtIndex:1];
            if ([player1 isHidden] && [player2 isHidden]) {
                isImageMedia = YES;
            } else if (![player1 isHidden] && [player2 isHidden]) {
                isImageMedia = NO;
            } else if ([player1 isHidden] && ![player2 isHidden]) {
                isImageMedia = NO;
            }
            
        }
        if (isImageMedia){
            // image
            [saveSnapButton removeTarget:nil action:NULL forControlEvents:UIControlEventTouchUpInside];
            [saveSnapButton addTarget:self action:@selector(saveImageSnapButtonPress:) forControlEvents:UIControlEventTouchUpInside];
        } else {
            [self addSaveVideoAction];
        }
    }
    [(SCMediaView *)self setUserInteractionEnabled:YES];
    
}
-(void) saveImageSnapButtonPress:(id)sender
{
    [[SCFeaturesLite shareFeatures] shake:sender];
    isImageMedia = NO;
    // Save the snap.
    if ([[(SCMediaView *)self imageView] image] != nil) {
        void (^fillerBlock)(void) = ^{
            Alert *alert = [[Alert alloc] initWithTitle:@"Saved" duration:0.3 completion:^{
                //Custom code here after Alert disappears
            }];
            alert.alertType = AlertTypeSuccess;
            [alert showAlert];
        };
        
        [[objc_getClass("SCSnapSaver") shared] saveSnapImageToSnapAlbum:[[(SCMediaView *)self imageView] image] completionBlock:fillerBlock];
        
    }
    
}
endhook

hook(AVPlayer)
-(void) saveVideoSnapButtonPress:(id)sender {
    [[SCFeaturesLite shareFeatures] shake:sender];
    NSLog(@"\n\n\n\n Save Video");
    AVAsset *currentPlayerAsset = [(AVPlayer *)self currentItem].asset;
    NSURL *videoURL = [(AVURLAsset *)currentPlayerAsset URL];
    NSLog(@"%@", videoURL);
    if(UIVideoAtPathIsCompatibleWithSavedPhotosAlbum(videoURL.path)) {
        UISaveVideoAtPathToSavedPhotosAlbum(videoURL.path, self, @selector(video:didFinishSavingWithError:contextInfo:), nil);
        
    }
}
- (void)video:(NSString *)videoPath didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo {
    if (error == nil) {
        Alert *alert = [[Alert alloc] initWithTitle:@"Saved" duration:0.3 completion:^{
            //Custom code here after Alert disappears
        }];
        alert.alertType = AlertTypeSuccess;
        [alert showAlert];
    } else {
        Alert *alert = [[Alert alloc] initWithTitle:@"Failed" duration:0.3 completion:^{
            //Custom code here after Alert disappears
        }];
        alert.alertType = AlertTypeError;
        [alert showAlert];
    }
    videoPlayer = nil;
}
endhook


















