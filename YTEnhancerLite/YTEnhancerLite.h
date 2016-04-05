//
//  YTEnhancerLite.h
//  YTEnhancerLite
//
//  Created by iMokhles on 04/04/16.
//  Copyright © 2016 iMokhles. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>
#import "iMoMacros.h"
#import "ZKSwizzle.h"
#import "fakelogos.h"

@interface YTEnhancerLite : NSObject <NSURLConnectionDelegate, NSURLConnectionDataDelegate>

@end

#pragma mark - Youtube

@interface QTMColorGroup : NSObject <NSSecureCoding>
{
    unsigned long long _numTones;
    long long _groupID;
    UIColor *_bodyTextColor;
    UIColor *_bodyTextColorOnLightestColor;
    UIColor *_bodyTextColorOnLighterColor;
    UIColor *_bodyTextColorOnRegularColor;
    UIColor *_bodyTextColorOnDarkerColor;
    UIColor *_bodyTextColorOnAccentColor;
    UIColor *_bodyTextColorOnBrightAccentColor;
    UIColor *_lightBodyTextColor;
    UIColor *_buttonBackgroundColor;
    UIColor *_buttonDisabledBackgroundColorDark;
    UIColor *_buttonDisabledBackgroundColorLight;
    UIColor *_buttonActionTextColor;
    UIColor *_buttonTextColor;
    UIColor *_buttonInkColor;
}

+ (double)minContrastRatioForOptions:(unsigned long long)arg1;
+ (id)exceptionColorFromChoices:(id)arg1 onColor:(id)arg2 options:(unsigned long long)arg3;
+ (id)bodyTextColorOnBackgroundImage:(id)arg1 inRegion:(struct CGRect)arg2 withFont:(id)arg3;
+ (id)bodyTextColorOnBackgroundImage:(id)arg1 withFont:(id)arg2;
+ (id)bodyTextColorOnColor:(id)arg1 withFont:(id)arg2;
+ (_Bool)supportsSecureCoding;
+ (double)minAlphaOfColor:(id)arg1 onColor:(id)arg2 options:(unsigned long long)arg3;
+ (double)luminanceOfColor:(id)arg1;
+ (id)textColorOnColor:(id)arg1 textAlpha:(double)arg2 font:(id)arg3;
+ (id)textColorOnColor:(id)arg1 textAlpha:(double)arg2 options:(unsigned long long)arg3;
+ (id)textColorFromChoices:(id)arg1 onColor:(id)arg2 options:(unsigned long long)arg3;
+ (double)contrastRatioForColor:(id)arg1 onColor:(id)arg2;
+ (_Bool)colorToneIsAccent:(long long)arg1;
+ (_Bool)colorToneIsTint:(long long)arg1;
+ (id)colorGroupFromTargetColor:(id)arg1 checkStandardGroups:(_Bool)arg2;
+ (id)colorGroupFromTargetColor:(id)arg1;
+ (id)colorGroupWithName:(id)arg1;
+ (id)colorGroupWithID:(long long)arg1;
+ (id)clearColors;
+ (id)googleYellowColors;
+ (id)googleGreenColors;
+ (id)googleRedColors;
+ (id)googleBlueColors;
+ (id)greyColors;
+ (id)whiteColors;
+ (void)initialize;
@property(readonly, nonatomic) UIColor *buttonInkColor; // @synthesize buttonInkColor=_buttonInkColor;
@property(readonly, nonatomic) UIColor *buttonTextColor; // @synthesize buttonTextColor=_buttonTextColor;
@property(readonly, nonatomic) UIColor *buttonActionTextColor; // @synthesize buttonActionTextColor=_buttonActionTextColor;
@property(readonly, nonatomic) UIColor *buttonDisabledBackgroundColorLight; // @synthesize buttonDisabledBackgroundColorLight=_buttonDisabledBackgroundColorLight;
@property(readonly, nonatomic) UIColor *buttonDisabledBackgroundColorDark; // @synthesize buttonDisabledBackgroundColorDark=_buttonDisabledBackgroundColorDark;
@property(readonly, nonatomic) UIColor *buttonBackgroundColor; // @synthesize buttonBackgroundColor=_buttonBackgroundColor;
@property(readonly, nonatomic) UIColor *lightBodyTextColor; // @synthesize lightBodyTextColor=_lightBodyTextColor;
@property(readonly, nonatomic) UIColor *bodyTextColorOnBrightAccentColor; // @synthesize bodyTextColorOnBrightAccentColor=_bodyTextColorOnBrightAccentColor;
@property(readonly, nonatomic) UIColor *bodyTextColorOnAccentColor; // @synthesize bodyTextColorOnAccentColor=_bodyTextColorOnAccentColor;
@property(readonly, nonatomic) UIColor *bodyTextColorOnDarkerColor; // @synthesize bodyTextColorOnDarkerColor=_bodyTextColorOnDarkerColor;
@property(readonly, nonatomic) UIColor *bodyTextColorOnRegularColor; // @synthesize bodyTextColorOnRegularColor=_bodyTextColorOnRegularColor;
@property(readonly, nonatomic) UIColor *bodyTextColorOnLighterColor; // @synthesize bodyTextColorOnLighterColor=_bodyTextColorOnLighterColor;
@property(readonly, nonatomic) UIColor *bodyTextColorOnLightestColor; // @synthesize bodyTextColorOnLightestColor=_bodyTextColorOnLightestColor;
@property(readonly, nonatomic) UIColor *bodyTextColor; // @synthesize bodyTextColor=_bodyTextColor;
@property(readonly, nonatomic) long long groupID; // @synthesize groupID=_groupID;
- (void)initBodyTextColors;
- (void)initButtonColors;
- (_Bool)hasAccentColors;
- (id)colorWithTone:(long long)arg1;
- (id)lightBodyTextColorOnColor:(id)arg1 withFont:(id)arg2;
- (id)lightBodyTextColorOnTone:(long long)arg1 withFont:(id)arg2;
- (id)bodyTextColorOnTone:(long long)arg1 withFont:(id)arg2;
- (id)bodyTextColorOnDarkerColorWithFont:(id)arg1;
- (id)bodyTextColorOnRegularColorWithFont:(id)arg1;
- (id)bodyTextColorOnLighterColorWithFont:(id)arg1;
- (id)bodyTextColorOnLightestColorWithFont:(id)arg1;
- (void)encodeWithCoder:(id)arg1;
- (id)initWithCoder:(id)arg1;
@property(readonly, nonatomic) NSString *name;
@property(readonly, nonatomic) UIColor *statusBarColor;
@property(readonly, nonatomic) UIColor *brightAccentColor;
@property(readonly, nonatomic) UIColor *accentColor;
@property(readonly, nonatomic) UIColor *darkerColor;
@property(readonly, nonatomic) UIColor *regularColor;
@property(readonly, nonatomic) UIColor *lighterColor;
@property(readonly, nonatomic) UIColor *lightestColor;
- (_Bool)isEqual:(id)arg1;
- (id)description;
- (void)dealloc;
- (id)initWithName:(id)arg1;
- (id)initWithTargetColor:(id)arg1 checkStandardGroups:(_Bool)arg2;
- (id)initWithPredefinedColorGroupID:(long long)arg1;
- (id)init;

@end

@interface PBRootObject : NSObject
@end

@interface PBGeneratedMessage : PBRootObject
@end

@interface PBArray : NSObject
- (id)lastObject;
- (id)firstObject;
- (id)objectAtIndexedSubscript:(unsigned long long)arg1;
- (id)objectAtIndex:(unsigned long long)arg1;
- (id)valueForKey:(id)arg1;
- (id)initWithInt32:(int)arg1;
- (id)initWithObject:(id)arg1;
- (id)initWithArray:(id)arg1 valueType:(int)arg2;
- (id)initWithValues:(const void *)arg1 count:(unsigned long long)arg2 valueType:(int)arg3;
- (id)initWithValueType:(int)arg1;
- (id)arrayByAppendingArray:(id)arg1;
+ (id)arrayWithInt32s:(int)arg1;
+ (id)arrayWithInt32:(int)arg1;
+ (id)arrayWithObjects:(id)arg1;
+ (id)arrayWithObject:(id)arg1;
+ (id)arrayWithArray:(id)arg1 valueType:(int)arg2;
+ (id)arrayWithValues:(const void *)arg1 count:(unsigned long long)arg2 valueType:(int)arg3;
+ (id)arrayWithValueType:(int)arg1;
@end

@interface PBMutableArray : PBArray
+ (id)arrayWithValueType:(int)arg1 capacity:(unsigned long long)arg2;
- (void)appendValues:(const void *)arg1 valueType:(int)arg2 count:(unsigned long long)arg3;
- (void)removeAllValues;
- (void)setArray:(id)arg1;
- (void)replaceDoubleAtIndex:(unsigned long long)arg1 withDouble:(double)arg2;
- (void)replaceFloatAtIndex:(unsigned long long)arg1 withFloat:(float)arg2;
- (void)replaceUInt64AtIndex:(unsigned long long)arg1 withUInt64:(unsigned long long)arg2;
- (void)replaceInt64AtIndex:(unsigned long long)arg1 withInt64:(long long)arg2;
- (void)replaceUInt32AtIndex:(unsigned long long)arg1 withUInt32:(unsigned int)arg2;
- (void)replaceInt32AtIndex:(unsigned long long)arg1 withInt32:(int)arg2;
- (void)replaceBoolAtIndex:(unsigned long long)arg1 withBool:(_Bool)arg2;
- (void)setObject:(id)arg1 atIndexedSubscript:(unsigned long long)arg2;
- (void)replaceObjectAtIndex:(unsigned long long)arg1 withObject:(id)arg2;
- (void)addDouble:(double)arg1;
- (void)addFloat:(float)arg1;
- (void)addUInt64:(unsigned long long)arg1;
- (void)addInt64:(long long)arg1;
- (void)addUInt32:(unsigned int)arg1;
- (void)addInt32:(int)arg1;
- (void)addBool:(_Bool)arg1;
- (void)addObject:(id)arg1;

@end

@interface YTIThumbnailDetails : PBGeneratedMessage
@property(nonatomic) _Bool hasPlaceholderColor; // @dynamic hasPlaceholderColor;
@property(nonatomic) _Bool hasThumbnailsArray; // @dynamic hasThumbnailsArray;
@property(nonatomic) unsigned int placeholderColor; // @dynamic placeholderColor;
@property(retain, nonatomic) PBMutableArray *thumbnailsArray; // @dynamic thumbnailsArray;
@end

@interface YTIFormattedString : PBGeneratedMessage
@property(nonatomic) _Bool hasAccessibility; // @dynamic hasAccessibility;
@property(nonatomic) _Bool hasRtl; // @dynamic hasRtl;
@property(nonatomic) _Bool hasRunsArray; // @dynamic hasRunsArray;
@property(nonatomic) _Bool rtl; // @dynamic rtl;
@property(retain, nonatomic) PBMutableArray *runsArray; // @dynamic runsArray;
@end

@interface YTIVideoRenderer : PBGeneratedMessage
- (_Bool)isLive;
@property(retain, nonatomic) YTIFormattedString *title; // @dynamic title;
@property(retain, nonatomic) YTIThumbnailDetails *thumbnail; // @dynamic thumbnail;
@property(retain, nonatomic) NSString *videoId; // @dynamic videoId;
@end

@interface YTIGridVideoRenderer : PBGeneratedMessage
@property(retain, nonatomic) YTIFormattedString *title; // @dynamic title;
@property(retain, nonatomic) YTIThumbnailDetails *thumbnail; // @dynamic thumbnail;
@property(retain, nonatomic) NSString *videoId; // @dynamic videoId;
@end

@interface YTIVideoWithContextRenderer : PBGeneratedMessage
@property(retain, nonatomic) YTIThumbnailDetails *thumbnail; // @dynamic thumbnail;
@property(retain, nonatomic) NSString *videoId; // @dynamic videoId;
@property(retain, nonatomic) YTIFormattedString *headline; // @dynamic headline;
@end

@interface YTCollectionViewCell : UICollectionViewCell
@property(nonatomic, getter=isHighlightable) _Bool highlightable; // @synthesize highlightable=_highlightable;
@property(nonatomic, getter=isSelectable) _Bool selectable; // @synthesize selectable=_selectable;
@property(nonatomic) int cellSeparatorStyle; // @synthesize cellSeparatorStyle=_cellSeparatorStyle;
@property(nonatomic) int cellBackgroundStyle; // @synthesize cellBackgroundStyle=_cellBackgroundStyle;
@end

@interface YTButton : UIButton
//+ (id)buttonWithType:(long long)arg1;
@property(nonatomic) double buttonImageTitlePadding; // @synthesize buttonImageTitlePadding=_buttonImageTitlePadding;
@property(nonatomic) double verticalContentPadding; // @synthesize verticalContentPadding=_verticalContentPadding;
@property(nonatomic) double horizontalContentPadding; // @synthesize horizontalContentPadding=_horizontalContentPadding;
@property(nonatomic) double minHitTargetSize; // @synthesize minHitTargetSize=_minHitTargetSize;
- (void)applyTypeStyle;
- (void)traitCollectionDidChange:(id)arg1;
- (void)setTitleTypeKind:(long long)arg1 typeVariant:(long long)arg2;
- (void)setTitleTypeKind:(long long)arg1;
- (void)enableHitTargetDebugging;
- (void)setButtonLayoutStyle:(long long)arg1;
- (struct CGSize)sizeThatFits:(struct CGSize)arg1;
- (struct CGRect)accessibilityFrame;
- (_Bool)pointInside:(struct CGPoint)arg1 withEvent:(id)arg2;
- (id)initWithDefaultImageTitlePadding;
- (id)initWithFrame:(struct CGRect)arg1;
@end

@protocol YTGridItem
+ (double)preferredHeightForWidth:(double)arg1 entry:(id)arg2;
@property(retain, nonatomic) id entry;
- (void)setHighlighted:(_Bool)arg1;
@end

@interface YTGridBaseView : UIView <YTGridItem>
- (void)removeLongPressTarget;
- (void)setLongPressTarget:(id)arg1 action:(SEL)arg2;
- (void)removeActionTarget;
- (void)setActionTarget:(id)arg1 action:(SEL)arg2;
@end

@interface YTGridVideoView : YTGridBaseView {
    YTIGridVideoRenderer *_entry;
}
@end

@interface YTVideoView : UIView
- (void)removeLongPressTarget;
- (void)setLongPressTarget:(id)arg1 action:(SEL)arg2;
- (void)removeActionTarget;
- (void)setActionTarget:(id)arg1 action:(SEL)arg2;
@end

@interface YTVideoCell : YTCollectionViewCell {
    YTIVideoRenderer *_videoRenderer;
    YTVideoView *_videoView;
}
- (void)removeLongPressTarget;
- (void)setLongPressTarget:(id)arg1 action:(SEL)arg2;
- (void)removeActionTarget;
- (void)setActionTarget:(id)arg1 action:(SEL)arg2;
@end

@interface YTGridCell : UICollectionViewCell
@property(retain, nonatomic) UIView<YTGridItem> *gridView; // @synthesize gridView=_gridView;
- (void)setLongPressTarget:(id)arg1 action:(SEL)arg2;
- (void)removeActionTarget;
- (void)setActionTarget:(id)arg1 action:(SEL)arg2;
@end

@interface YTGridVideoCell : YTGridCell
- (void)setAccelerated:(_Bool)arg1;
@end

@interface YTCellController : NSObject
@property(readonly, nonatomic) id entry; // @synthesize entry=_entry;
- (void)imageLoadDidFailWithError:(id)arg1;
- (void)imageDidLoad;
- (_Bool)hasThumbnailMapping:(id)arg1;
- (void)updateThumbnailMapping;
- (void)setCellTargets;
- (void)handleLongPress:(id)arg1;
- (struct CGSize)cellSizeWithSize:(struct CGSize)arg1;
@end


@interface YTInnerTubeCellController : YTCellController
{
    _Bool _visibilityUpdated;
}

- (void)cellDidPressLinkedURL:(id)arg1;
- (void)cellDidPressLinkedNavigationEndpoint:(id)arg1 linkText:(id)arg2;
- (void)didSelectItem;
- (void)cellDidBecomeVisible;
- (void)setCell:(id)arg1;
@end

@interface YTVideoCellController : YTInnerTubeCellController
- (id)menuRenderer;
- (void)setAccelerated:(_Bool)arg1;
- (void)handleLongPressBegan:(id)arg1;
- (void)handleAction:(id)arg1;
@end

@interface QTMButton : UIButton
+ (id)buttonWithColorGroup:(id)arg1 shape:(long long)arg2;
+ (id)buttonWithColorGroup:(id)arg1;
//+ (id)buttonWithType:(long long)arg1;
@property(retain, nonatomic) UIColor *customTitleColor; // @synthesize customTitleColor=_customTitleColor;
@property(retain, nonatomic) UIColor *disabledBackgroundColorDark; // @synthesize disabledBackgroundColorDark=_disabledBackgroundColorDark;
@property(retain, nonatomic) UIColor *disabledBackgroundColorLight; // @synthesize disabledBackgroundColorLight=_disabledBackgroundColorLight;
@property(retain, nonatomic) UIColor *enabledBackgroundColor; // @synthesize
- (_Bool)isTransparentColor:(id)arg1;
- (_Bool)isDarkColor:(id)arg1;
- (double)cornerRadius;
@end


@interface GOODialogActionButton : QTMButton
@property(nonatomic) _Bool disableRTLTextAlignmentForTitle; // @synthesize disableRTLTextAlignmentForTitle=_disableRTLTextAlignmentForTitle;
@property(nonatomic) double minimumWidth; // @synthesize minimumWidth=_minimumWidth;
@property(nonatomic) double minimumContentHeight; // @synthesize minimumContentHeight=_minimumContentHeight;
@end

@interface GOOMultiLineView : UIView
@end

@interface GOODialogView : GOOMultiLineView
- (void)addButton:(id)arg1 style:(int)arg2 insets:(struct UIEdgeInsets)arg3 showHorizontalDivider:(_Bool)arg4 action:(id)arg5;
- (void)addButton:(id)arg1 style:(int)arg2 action:(id)arg3;
@end

@interface GOOAction : NSObject
+ (id)actionWithTitle:(id)arg1 iconImage:(id)arg2 style:(long long)arg3 handler:(id)arg4;
@end

@interface GOOActionSheetController : NSObject
+ (id)actionSheetControllerWithMessage:(id)arg1;
+ (id)actionSheetController;
@property(nonatomic) struct CGSize offset; // @synthesize offset=_offset;
@property(retain, nonatomic) UIView *sourceView; // @synthesize sourceView=_sourceView;
@property(nonatomic) unsigned long long anchorCorner; // @synthesize anchorCorner=_anchorCorner;
@property(nonatomic) unsigned long long permittedArrowDirections; // @synthesize
- (void)popoverViewControllerDidCancel:(id)arg1;
- (void)bottomSheetControllerDidCancel:(id)arg1;
- (void)dismissViewControllerAnimated:(_Bool)arg1 completion:(id)arg2;
- (void)dismissWithAction:(id)arg1 animated:(_Bool)arg2 completion:(id)arg3;
- (void)dismiss;
- (id)bestGuessWindow;
- (void)present;
- (void)presentFromViewController:(id)arg1 animated:(_Bool)arg2 completion:(id)arg3;
- (void)addAction:(id)arg1;
@property(readonly, nonatomic) NSArray *actions;
- (id)popoverViewController;
- (id)initWithMessage:(id)arg1;
- (id)init;
@end

@interface GOOModalView : UIView
- (id)initWithTarget:(id)arg1;
- (void)dismissDialog:(_Bool)arg1;
- (_Bool)shouldDimBackground;
- (void)reposition;
- (void)dismissDueToApplicationBackground;
- (void)dismissWithCancelAction:(_Bool)arg1;
- (void)dismiss;
@property(retain, nonatomic) UIColor *actionButtonIconColor;
@property(retain, nonatomic) UIColor *actionButtonTitleColor;
@property(retain, nonatomic) QTMColorGroup *actionButtonColorGroup;
- (void)didTapBackground;
- (void)sizeToFit;
@end

@interface GOOActionSheet : GOOModalView
- (void)addTitle:(id)arg1 iconImage:(id)arg2 withStyle:(int)arg3 automationIdentifier:(id)arg4 action:(id)arg5;
- (id)initWithTarget:(id)arg1;
- (void)dismissWithCancelAction:(_Bool)arg1;
- (void)dismiss;
- (void)showPointingAtView:(id)arg1 withRect:(struct CGRect)arg2 arrowDirections:(unsigned long long)arg3;
- (void)showPointingAtView:(id)arg1 withOffset:(struct CGSize)arg2 arrowDirections:(unsigned long long)arg3;
- (void)showPointingAtView:(id)arg1 arrowDirections:(unsigned long long)arg2;
- (id)cancelButtonIconImage;
- (void)showWithCancelButton:(_Bool)arg1 cancelAction:(id)arg2;
- (void)showWithCancelButton:(_Bool)arg1;
- (void)show;
- (void)addButton:(id)arg1 withAction:(id)arg2;
- (void)addMessage:(id)arg1;
@end

@interface GOOPopoverActionSheet : GOOActionSheet
@end

@interface YTISoftTabRenderer : PBGeneratedMessage
{
}

+ (id)descriptor;

// Remaining properties
//@property(retain, nonatomic) YTITabContentSupportedRenderers *content; // @dynamic content;
@property(nonatomic) _Bool hasContent; // @dynamic hasContent;
@property(nonatomic) _Bool hasIcon; // @dynamic hasIcon;
@property(nonatomic) _Bool hasSelected; // @dynamic hasSelected;
@property(nonatomic) _Bool hasTabIdentifier; // @dynamic hasTabIdentifier;
@property(nonatomic) _Bool hasTitle; // @dynamic hasTitle;
//@property(retain, nonatomic) YTIIcon *icon; // @dynamic icon;
@property(nonatomic) _Bool selected; // @dynamic selected;
@property(retain, nonatomic) NSString *tabIdentifier; // @dynamic tabIdentifier;
@property(retain, nonatomic) NSString *title; // @dynamic title;

@end

@interface YTIIcon : PBGeneratedMessage
{
}

+ (id)descriptor;

// Remaining properties
@property(nonatomic) _Bool hasIconType; // @dynamic hasIconType;
@property(nonatomic) int iconType; // @dynamic iconType;

@end

@interface YTIRenderers : PBGeneratedMessage
@end

@interface YTIBrowseEndpoint : PBGeneratedMessage
{
}

+ (id)descriptor;

// Remaining properties
//@property(retain, nonatomic) YTIBrowseEndpointContextSupportedConfigs *browseEndpointContextSupportedConfigs; // @dynamic browseEndpointContextSupportedConfigs;
@property(retain, nonatomic) NSString *browseId; // @dynamic browseId;
@property(retain, nonatomic) NSString *canonicalBaseUrl; // @dynamic canonicalBaseUrl;
@property(nonatomic) _Bool hasBrowseEndpointContextSupportedConfigs; // @dynamic hasBrowseEndpointContextSupportedConfigs;
@property(nonatomic) _Bool hasBrowseId; // @dynamic hasBrowseId;
@property(nonatomic) _Bool hasCanonicalBaseUrl; // @dynamic hasCanonicalBaseUrl;
@property(nonatomic) _Bool hasOffline; // @dynamic hasOffline;
@property(nonatomic) _Bool hasParams; // @dynamic hasParams;
@property(nonatomic) _Bool hasQuery; // @dynamic hasQuery;
@property(nonatomic) _Bool offline; // @dynamic offline;
@property(retain, nonatomic) NSString *params; // @dynamic params;
@property(retain, nonatomic) NSString *query; // @dynamic query;

@end

@interface YTINavigationEndpoint : PBGeneratedMessage
@property(retain, nonatomic) YTIBrowseEndpoint *browseEndpoint; // @dynamic browseEndpoint;

@end

@interface YTITabRenderer : PBGeneratedMessage
{
}

+ (id)descriptor;

// Remaining properties
//@property(retain, nonatomic) YTIAccessibilitySupportedDatas *accessibility; // @dynamic accessibility;
//@property(retain, nonatomic) YTITabContentSupportedRenderers *content; // @dynamic content;
@property(retain, nonatomic) YTINavigationEndpoint *endpoint; // @dynamic endpoint;
//@property(retain, nonatomic) YTITabFooterSupportedRenderers *footer; // @dynamic footer;
@property(nonatomic) _Bool hasAccessibility; // @dynamic hasAccessibility;
@property(nonatomic) _Bool hasContent; // @dynamic hasContent;
@property(nonatomic) _Bool hasEndpoint; // @dynamic hasEndpoint;
@property(nonatomic) _Bool hasFooter; // @dynamic hasFooter;
@property(nonatomic) _Bool hasHeader; // @dynamic hasHeader;
@property(nonatomic) _Bool hasIcon; // @dynamic hasIcon;
@property(nonatomic) _Bool hasIndicator; // @dynamic hasIndicator;
@property(nonatomic) _Bool hasPresentationStyle; // @dynamic hasPresentationStyle;
@property(nonatomic) _Bool hasSelected; // @dynamic hasSelected;
@property(nonatomic) _Bool hasSelectionStyle; // @dynamic hasSelectionStyle;
@property(nonatomic) _Bool hasTabIdentifier; // @dynamic hasTabIdentifier;
@property(nonatomic) _Bool hasTitle; // @dynamic hasTitle;
@property(nonatomic) _Bool hasTrackingParams; // @dynamic hasTrackingParams;
//@property(retain, nonatomic) YTITabHeaderSupportedRenderers *header; // @dynamic header;
@property(retain, nonatomic) YTIIcon *icon; // @dynamic icon;
//@property(retain, nonatomic) YTITabIndicatorSupportedRenderers *indicator; // @dynamic indicator;
//@property(retain, nonatomic) YTITabRendererPresentationStyle *presentationStyle; // @dynamic presentationStyle;
@property(nonatomic) _Bool selected; // @dynamic selected;
//@property(retain, nonatomic) YTITabRendererSelectionStyle *selectionStyle; // @dynamic selectionStyle;
@property(retain, nonatomic) NSString *tabIdentifier; // @dynamic tabIdentifier;
@property(retain, nonatomic) NSString *title; // @dynamic title;
@property(retain, nonatomic) NSData *trackingParams; // @dynamic trackingParams;

@end

@interface YTICompactVideoRenderer : PBGeneratedMessage
@property(retain, nonatomic) NSString *videoId; // @dynamic videoId;
@end

@interface YTCompactVideoView : UIView
@property(retain, nonatomic) YTICompactVideoRenderer *renderer; // @synthesize renderer=_renderer;
@end

@interface YTIExpandableTabRenderer : PBGeneratedMessage
{
}

+ (id)descriptor;

// Remaining properties
//@property(retain, nonatomic) YTITabContentSupportedRenderers *content; // @dynamic content;
@property(retain, nonatomic) YTINavigationEndpoint *endpoint; // @dynamic endpoint;
@property(retain, nonatomic) NSString *expandedText; // @dynamic expandedText;
@property(nonatomic) _Bool hasContent; // @dynamic hasContent;
@property(nonatomic) _Bool hasEndpoint; // @dynamic hasEndpoint;
@property(nonatomic) _Bool hasExpandedText; // @dynamic hasExpandedText;
@property(nonatomic) _Bool hasSelected; // @dynamic hasSelected;
@property(nonatomic) _Bool hasSelectionStyle; // @dynamic hasSelectionStyle;
@property(nonatomic) _Bool hasTitle; // @dynamic hasTitle;
@property(nonatomic) _Bool selected; // @dynamic selected;
//@property(retain, nonatomic) YTITabRendererSelectionStyle *selectionStyle; // @dynamic selectionStyle;
@property(retain, nonatomic) NSString *title; // @dynamic title;

@end

@interface YTIBrowseTabSupportedRenderers : PBGeneratedMessage
{
}

+ (id)descriptor;

// Remaining properties
@property(retain, nonatomic) YTIExpandableTabRenderer *expandableTabRenderer; // @dynamic expandableTabRenderer;
@property(nonatomic) _Bool hasExpandableTabRenderer; // @dynamic hasExpandableTabRenderer;
@property(nonatomic) _Bool hasSoftTabRenderer; // @dynamic hasSoftTabRenderer;
@property(nonatomic) _Bool hasTabRenderer; // @dynamic hasTabRenderer;
@property(retain, nonatomic) YTISoftTabRenderer *softTabRenderer; // @dynamic softTabRenderer;
@property(retain, nonatomic) YTITabRenderer *tabRenderer; // @dynamic tabRenderer;

@end

@interface YTVariableHeightHeaderViewController : UIViewController
@property(retain, nonatomic) UIViewController *contentViewController;
@end

@interface YTTabRendererViewController : YTVariableHeightHeaderViewController {
    UIViewController *_contentViewController;
    //    UIViewController<YTResponseViewController> *_headerViewController;
    //    UIViewController<YTController> *_footerViewController;
    YTITabRenderer *_model;
}
@property(readonly, nonatomic) __weak id  parentResponder;
- (id)initWithParentResponder:(id)arg1;
@end

@interface YTDownloadedViewController : NSObject

@end

@interface YTTabsRendererViewController : UIViewController
@property(nonatomic) _Bool navBarScrollEnabled; // @synthesize navBarScrollEnabled=_navBarScrollEnabled;
@property(readonly, nonatomic) unsigned long long selectedIndex; // @synthesize selectedIndex=_selectedIndex;
- (id)findLabelWithBrowseId:(id)arg1;
- (id)hintPresentationResponderProvider;
- (id)navEndpointProvider;
- (void)prepareSelectedTab;
- (void)switchToTab:(unsigned long long)arg1;
- (void)setupDefaultContentViewControllers;
- (void)removeAllContentViewControllers;
- (id)tabsRendererView;
@end

@interface YTTintableButtonsView : UIView
- (id)cacheKeyForButton:(id)arg1 state:(unsigned long long)arg2;
- (id)tintableImageForImage:(id)arg1 cacheKey:(id)arg2;
- (void)cacheOriginalImage:(id)arg1 cacheKey:(id)arg2;
- (void)tintButtons:(id)arg1 color:(id)arg2;
- (id)initWithFrame:(struct CGRect)arg1;
@end

@interface YTRightNavigationButtons : YTTintableButtonsView
@property(retain, nonatomic) UIButton *rightButton; // @synthesize rightButton=_rightButton;
@property(retain, nonatomic) UIButton *leftButton; // @synthesize leftButton=_leftButton;
- (id)visibleButtons;
- (void)tintAllButtons;
- (void)setTintColor:(id)arg1;
- (_Bool)pointInside:(struct CGPoint)arg1 withEvent:(id)arg2;
- (_Bool)isRightButtonVisible;
- (_Bool)isLeftButtonVisible;
- (void)layoutSubviews;
- (struct CGSize)sizeThatFits:(struct CGSize)arg1;
- (id)initWithLocator:(id)arg1;
@end

@interface YTNavigationTitleView : UIView
@property(retain, nonatomic) UIView *titleButton; // @synthesize titleButton=_titleButton;
- (void)layoutSubviews;
@end

@interface YTAppViewController : UIViewController
@property(readonly, nonatomic) UINavigationController *navigationController;
@end

@interface YTRootNavigationController : UINavigationController
@end

@interface YTBaseViewController : UIViewController
@end

@interface YTBaseNavigationViewController : YTBaseViewController
@end

@interface UINavigationItem (GOONavigationInternal)
+ (void)goo_swizzleSetterSel:(SEL)arg1;
+ (void)goo_swizzleBarButtonSettersForKVO;
- (void)goo_setRightBarButtonItems:(id)arg1 animated:(_Bool)arg2;
- (void)goo_setRightBarButtonItem:(id)arg1 animated:(_Bool)arg2;
- (void)goo_setLeftBarButtonItems:(id)arg1 animated:(_Bool)arg2;
- (void)goo_setLeftBarButtonItem:(id)arg1 animated:(_Bool)arg2;
- (void)goo_setRightBarButtonItems:(id)arg1;
- (void)goo_setRightBarButtonItem:(id)arg1;
- (void)goo_setLeftBarButtonItems:(id)arg1;
- (void)goo_setLeftBarButtonItem:(id)arg1;
@property(retain, nonatomic, setter=goo_setTitleView:) UIView *goo_titleView; // @dynamic goo_titleView;
@end

@interface YTAppDelegate : UIResponder <UIApplicationDelegate>
@end